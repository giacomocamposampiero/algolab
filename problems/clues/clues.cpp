#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Triangulation_vertex_base_with_info_2.h>
#include <CGAL/Triangulation_face_base_2.h>
#include <boost/pending/disjoint_sets.hpp>
#include <vector>
#include <tuple>
#include <algorithm>
#include <iostream>
#include <stack>

#define WHITE -1
#define BLACK 0
#define RED 1

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef K::Point_2 P;

typedef std::size_t                                            Index;
typedef CGAL::Triangulation_vertex_base_with_info_2<Index,K>   Vb;
typedef CGAL::Triangulation_face_base_2<K>                     Fb;
typedef CGAL::Triangulation_data_structure_2<Vb,Fb>            Tds;
typedef CGAL::Delaunay_triangulation_2<K,Tds>                  Delaunay;
typedef Delaunay::Vertex_handle Vertex_handle;

typedef std::tuple<Index,Index,K::FT> Edge;
typedef std::vector<Edge> EdgeV;
typedef std::pair<K::Point_2,Index> IPoint;

bool interference(Delaunay &t, long r){
  for(auto e: t.finite_edges()){
    Vertex_handle v1 = e.first->vertex((e.second + 1) % 3);
    Vertex_handle v2 = e.first->vertex((e.second + 2) % 3);
    if(CGAL::squared_distance(v1->point(), v2->point()) <= r*r)
      return true;
  }
  return false;
}

bool color(Delaunay &t, long r, int n){
  
  std::vector<int> visited(n, WHITE);
  std::vector<P> pR, pB;
  
  for(auto v: t.finite_vertex_handles()){
    if(visited[v->info()] == WHITE){
      visited[v->info()] = BLACK;
      std::stack<Vertex_handle> st;
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
  
  Delaunay tR, tB;
  tR.insert(pR.begin(), pR.end());
  tB.insert(pB.begin(), pB.end());
  return !interference(tR, r) && !interference(tB, r);
}

void testcase() {

  int n, m; long r;
  std::cin >> n >> m >> r;
  
  K::FT squared_r = r*r;
  
  std::vector<IPoint> points;
  points.reserve(n);
  for (int i = 0; i < n; ++i) {
    int x, y; std::cin >> x >> y;
    points.emplace_back(K::Point_2(x, y), i);
  }

  Delaunay t;
  t.insert(points.begin(), points.end());

  std::vector<std::pair<K::Point_2, K::Point_2>> clues;
  for(int i=0; i<m; i++) {
    int ax, ay, bx, by; std::cin >> ax >> ay >> bx >> by;
    clues.emplace_back(K::Point_2(ax,ay), K::Point_2(bx,by));
  }
  
  if(!color(t, r, n)) {
    std::cout << std::string(m, 'n') << std::endl;
    return;
  }
  
  EdgeV edges;
  edges.reserve(3*n);
  std::vector<int> S(n, -1);
  
  for (auto e = t.finite_edges_begin(); e != t.finite_edges_end(); ++e) {
    
    Index v1 = e->first->vertex((e->second+1)%3)->info();
    Index v2 = e->first->vertex((e->second+2)%3)->info();

    if (v1 > v2) std::swap(v1, v2);
    edges.emplace_back(v1, v2, t.segment(e).squared_length());
  }
  
  std::sort(edges.begin(), edges.end(), [](const Edge& e1, const Edge& e2) -> bool {
    return std::get<2>(e1) < std::get<2>(e2);
  });

  boost::disjoint_sets_with_storage<> uf(n);
  Index n_components = n;

  for (EdgeV::const_iterator e = edges.begin(); e != edges.end(); ++e) {

    Index c1 = uf.find_set(std::get<0>(*e));
    Index c2 = uf.find_set(std::get<1>(*e));
    
    if(std::get<2>(*e) > squared_r) break;
    
    if (c1 != c2) {
      uf.link(c1, c2);
      if (--n_components == 1) break;
    }
  }
  
  for(size_t i=0; i<clues.size(); i++) {
    auto nna = t.nearest_vertex(clues[i].first);
    auto nnb = t.nearest_vertex(clues[i].second);
    if(CGAL::squared_distance(clues[i].second, clues[i].first) <= squared_r) {
      // a and b are close enough to communicate without station support
      std::cout << 'y';
      continue;
    } else if(CGAL::squared_distance(nna ->point(), clues[i].first) > squared_r || CGAL::squared_distance(nnb ->point(), clues[i].second) > squared_r) {
      // a or b are not close enough to a station
      std::cout << 'n';
      continue;
    }
    if(uf.find_set(nna -> info()) == uf.find_set(nnb -> info())) std::cout << 'y';
    else std::cout << 'n';
  }
  std::cout << std::endl;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  int t; std::cin >> t;
  while(t--) testcase();
}
