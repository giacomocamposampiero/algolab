#include <bits/stdc++.h>
#include <CGAL/Exact_predicates_exact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Triangulation_face_base_with_info_2.h>

using namespace std;

typedef CGAL::Exact_predicates_exact_constructions_kernel K;
typedef CGAL::Triangulation_vertex_base_2<K> Vb;
typedef CGAL::Triangulation_face_base_with_info_2<K::FT,K> Fb;
typedef CGAL::Triangulation_data_structure_2<Vb,Fb> Tds;
typedef CGAL::Delaunay_triangulation_2<K,Tds> Triangulation;
typedef Triangulation::Face_handle Face_handle;
typedef K::Point_2 P;
typedef pair<K::FT, Face_handle> PKF;

void testcase(){
  int n; cin >> n;
  int m; cin >> m;
  long r; cin >> r;
  
  vector<P> trees;
  long x, y;
  for(int i = 0; i < n; i++){
    cin >> x >> y;
    trees.push_back(P(x,y));
  }
  
  Triangulation t;
  t.insert(trees.begin(), trees.end());
  
  priority_queue<PKF> pq;
  for(auto f: t.all_face_handles()){
    if(t.is_infinite(f))
      f->info() = (K::FT)(numeric_limits<long>::max())*(K::FT)(numeric_limits<long>::max());
    else{
      P vv = t.dual(f);
      P vertex = f->vertex(0)->point();
      f->info() = CGAL::squared_distance(vertex, vv);
    }
    pq.push(PKF(f->info(), f));
  }
  
  while(!pq.empty()){
    Face_handle curr = pq.top().second;
    pq.pop();
    
    for(int i = 0; i < 3; i++){
      Face_handle neigh = curr->neighbor(i);
      if(!t.is_infinite(neigh)){
        P v1 = curr->vertex((i+1)%3)->point();
        P v2 = curr->vertex((i+2)%3)->point();
        K::FT tmp = min(curr->info(), CGAL::squared_distance(v1, v2));
        if(tmp > neigh->info()){
          neigh->info() = tmp;
          pq.push(PKF(neigh->info(), neigh));
        }
      }
    }
  }
  
  long s;
  for(int i = 0; i < m; i++){
    cin >> x >> y >> s;
    P curr(x,y);
    P nearest = t.nearest_vertex(curr)->point();
    if(CGAL::squared_distance(curr, nearest) >= (K::FT)(2*s+2*r)*(K::FT)(2*s+2*r))
      cout << "y";
    else if(CGAL::squared_distance(curr, nearest) < (K::FT)(s+r)*(K::FT)(s+r))
      cout << "n";
    else{
      Face_handle curr_face = t.locate(curr);
      if(curr_face->info() >= (K::FT)(2*s+2*r)*(K::FT)(2*s+2*r))
        cout << "y";
      else
        cout << "n";
    }
  }
  
  cout << endl;
}

int main(){
  ios_base::sync_with_stdio(false);
  int t; cin >> t;
  for(int i = 0; i < t; i++)
    testcase();
  
  return 0;
}