#include <bits/stdc++.h>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Triangulation_face_base_with_info_2.h>

using namespace std;

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Triangulation_vertex_base_2<K> Vb;
typedef CGAL::Triangulation_face_base_with_info_2<long,K> Fb;
typedef CGAL::Triangulation_data_structure_2<Vb,Fb> Tds;
typedef CGAL::Delaunay_triangulation_2<K,Tds> Triangulation;
typedef Triangulation::Face_handle Face_handle;
typedef K::Point_2 P;
typedef pair<long,Face_handle> PLF;

bool testcase(){
  int n; cin >> n;
  if(n == 0)  return true;
  
  vector<P> points;
  int x, y;
  for(int i = 0; i < n; i++){
    cin >> x >> y;
    points.push_back(P(x,y));
  }
  
  Triangulation t;
  t.insert(points.begin(), points.end());
  
  priority_queue<PLF> pq;
  for(auto f: t.all_face_handles()){
    if(t.is_infinite(f)){
      f->info() = numeric_limits<long>::max();
      pq.push(PLF(numeric_limits<long>::max(), f));
    }
    else
      f->info() = -1;
  }

  while(!pq.empty()){
    Face_handle curr = pq.top().second;
    pq.pop();
    
    for(int i = 0; i < 3; i++){
      Face_handle neigh = curr->neighbor(i);
      if(!t.is_infinite(neigh)){
        P v1 = curr->vertex((i+1)%3)->point();
        P v2 = curr->vertex((i+2)%3)->point();
        long tmp = min(curr->info(), (long)CGAL::squared_distance(v1, v2));
        if(tmp > neigh->info()){
          neigh->info() = tmp;
          pq.push(PLF(tmp, neigh));
        }
      }
    }
  }
  
  int m; cin >> m;
  
  long d;
  for(int i = 0; i < m; i++){
    cin >> x >> y >> d;
    P curr(x,y);
    //first check if nearest has at least squared distance d
    P nearest = t.nearest_vertex(curr)->point();
    if(CGAL::squared_distance(curr, nearest) < d)
      cout << "n";
    else{
      Face_handle f = t.locate(curr);
      if(f->info() < 4*d)
        cout << "n";
      else
        cout << "y";
    }
  }
  
  cout << endl;
  
  return false;
}

int main(){
  ios_base::sync_with_stdio(false);
  bool end = false;
  while(!end)
    end = testcase();
  
  return 0;
}