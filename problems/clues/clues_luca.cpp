#include <bits/stdc++.h>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Triangulation_vertex_base_with_info_2.h>
#include <boost/pending/disjoint_sets.hpp>

using namespace std;

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Triangulation_vertex_base_with_info_2<int,K> Vb;
typedef CGAL::Triangulation_face_base_2<K> Fb;
typedef CGAL::Triangulation_data_structure_2<Vb,Fb> Tds;
typedef CGAL::Delaunay_triangulation_2<K,Tds> Triangulation;
typedef Triangulation::Vertex_handle Vertex_handle;
typedef K::Point_2 P;
typedef boost::disjoint_sets_with_storage<> Uf;

#define WHITE -1
#define BLACK 0
#define RED 1

bool interference(Triangulation &t, long r){
  for(auto e: t.finite_edges()){
    Vertex_handle v1 = e.first->vertex((e.second + 1) % 3);
    Vertex_handle v2 = e.first->vertex((e.second + 2) % 3);
    if(CGAL::squared_distance(v1->point(), v2->point()) <= r*r)
      return true;
  }
  
  return false;
}

bool color(Triangulation &t, long r, int n){
  vector<int> visited(n, WHITE);
  
  vector<P> pR, pB;
  
  for(auto v: t.finite_vertex_handles()){
    if(visited[v->info()] == WHITE){
      visited[v->info()] = BLACK;
      stack<Vertex_handle> st;
      st.push(v);
      do{
        Vertex_handle u = st.top();
        st.pop();
        auto circ = t.incident_vertices(u);
        do{
          if(!t.is_infinite(circ) && visited[circ->info()] == WHITE && CGAL::squared_distance(circ->point(), u->point()) <= r*r){
            visited[circ->info()] = 1 - visited[u->info()];
            st.push(circ);
          }
        } while(++circ != t.incident_vertices(u));
      } while(!st.empty());
    }
    
    if(visited[v->info()] == BLACK) pB.push_back(v->point());
    else  pR.push_back(v->point());
  }
  
  Triangulation tR, tB;
  tR.insert(pR.begin(), pR.end());
  tB.insert(pB.begin(), pB.end());
  
  return !interference(tR, r) && !interference(tB, r);
}

void testcase(){
  int n, m;
  long r;
  cin >> n >> m >> r;
  
  vector<pair<P,int>> stations;
  int x, y;
  for(int i = 0; i < n; i++){
    cin >> x >> y;
    stations.push_back(make_pair(P(x,y), i));
  }
  
  Triangulation t;
  t.insert(stations.begin(), stations.end());
  
  Uf sets(n);
  for(auto e: t.finite_edges()){
    Vertex_handle v1 = e.first->vertex((e.second + 1) % 3);
    Vertex_handle v2 = e.first->vertex((e.second + 2) % 3);
    if(sets.find_set(v1->info()) != sets.find_set(v2->info()) && CGAL::squared_distance(v1->point(), v2->point()) <= r*r)
      sets.union_set(sets.find_set(v1->info()), sets.find_set(v2->info()));
  }
  
  bool feasible = color(t, r, n);
  
  int xa, ya, xb, yb;
  for(int i = 0; i < m; i++){
    cin >> xa >> ya >> xb >> yb;
    P a(xa,ya), b(xb,yb);
    Vertex_handle na = t.nearest_vertex(a);
    Vertex_handle nb = t.nearest_vertex(b);
    if(!feasible)
      cout << "n";
    else if(CGAL::squared_distance(a, b) <= r*r)
      cout << "y";
    else if(CGAL::squared_distance(a, na->point()) > r*r || CGAL::squared_distance(b, nb->point()) > r*r)
      cout << "n";
    else if(sets.find_set(na->info()) == sets.find_set(nb->info()))
      cout << "y";
    else
      cout << "n";
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