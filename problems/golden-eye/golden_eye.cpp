///3
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Triangulation_vertex_base_with_info_2.h>
#include <CGAL/Triangulation_face_base_2.h>
#include <boost/pending/disjoint_sets.hpp>
#include <vector>
#include <tuple>
#include <algorithm>
#include <iostream>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;

typedef std::size_t                                            Index;
typedef CGAL::Triangulation_vertex_base_with_info_2<Index,K>   Vb;
typedef CGAL::Triangulation_face_base_2<K>                     Fb;
typedef CGAL::Triangulation_data_structure_2<Vb,Fb>            Tds;
typedef CGAL::Delaunay_triangulation_2<K,Tds>                  Delaunay;

typedef std::tuple<Index,Index,K::FT> Edge;
typedef std::vector<Edge> EdgeV;

struct mission {
  Index source;
  Index target;
  K::FT d_source;
  K::FT d_target;
};

void testcase() {
  
  int n, m; std::cin >> n >> m;
  K::FT p; std::cin >> p;

  typedef std::pair<K::Point_2,Index> IPoint;
  std::vector<IPoint> points;
  points.reserve(n);
  for (int i = 0; i < n; ++i) {
    int x, y; std::cin >> x >> y;
    points.emplace_back(K::Point_2(x, y), i);
  }
  
  Delaunay t;
  t.insert(points.begin(), points.end());

  std::vector<mission> ms;
  K::FT max_d = 0;
  for(int i=0; i<m; i++) {
    int x0, y0, x1, y1; std::cin >> x0 >> y0 >> x1 >> y1;
    K::Point_2 source(x0, y0);
    K::Point_2 target(x1, y1);
    auto nns = t.nearest_vertex(source);
    auto nnt = t.nearest_vertex(target);
    K::FT d_source = CGAL::squared_distance(source, nns -> point());
    K::FT d_target = CGAL::squared_distance(target, nnt -> point());
    ms.push_back({nns -> info(), nnt -> info(), d_source, d_target});
    max_d = CGAL::max(max_d, d_target);
    max_d = CGAL::max(max_d, d_source);
  }
  
  EdgeV edges;
  edges.reserve(3*n);
  for (auto e = t.finite_edges_begin(); e != t.finite_edges_end(); ++e) {
    Index i1 = e->first->vertex((e->second+1)%3)->info();
    Index i2 = e->first->vertex((e->second+2)%3)->info();
    if (i1 > i2) std::swap(i1, i2);
    edges.emplace_back(i1, i2, t.segment(e).squared_length());
  }
  std::sort(edges.begin(), edges.end(), [](const Edge& e1, const Edge& e2) -> bool {
    return std::get<2>(e1) < std::get<2>(e2);
  });

  boost::disjoint_sets_with_storage<> uf(n);
  Index n_components = n;
  
  for (EdgeV::const_iterator e = edges.begin(); e != edges.end(); ++e) {
    if(std::get<2>(*e) > p) break;
    Index c1 = uf.find_set(std::get<0>(*e));
    Index c2 = uf.find_set(std::get<1>(*e));
    if (c1 != c2) {
      uf.link(c1, c2);
      if (--n_components == 1) break;
    }
  }
  
  K::FT max_with_p = 0;
  std::vector<bool> state(m, false);

  for(int i=0; i<m; i++) {
    if(uf.find_set(ms[i].source) == uf.find_set(ms[i].target) && ms[i].d_source <= p/4 && ms[i].d_target <= p/4) {
      std::cout << 'y';
      state[i] = true;
      max_with_p = CGAL::max(max_with_p, ms[i].d_target);
      max_with_p = CGAL::max(max_with_p, ms[i].d_source);
    } else std::cout << 'n';
  }
  
  K::FT a = max_d*4, b = max_with_p*4, last = 0;
  boost::disjoint_sets_with_storage<> uf_2(n);
  n_components = n;
  bool check_a = true, check_b = true;
  
  for (EdgeV::const_iterator e = edges.begin(); e != edges.end() && (check_a || check_b); ++e) {
    
    bool same_state = true;
    bool all_reached = true;
    for(int i=0; i<m && (same_state || all_reached); i++) {
      if(check_b && state[i] && (uf_2.find_set(ms[i].source) != uf_2.find_set(ms[i].target)))
        same_state = false;
      if(check_a && uf_2.find_set(ms[i].source) != uf_2.find_set(ms[i].target))
        all_reached = false;
    }
      
    if(check_a && all_reached) { a = CGAL::max(last, max_d*4); check_a = false; }
    if(check_b && same_state) { b = CGAL::max(last, max_with_p*4); check_b = false; }
  
    Index c1 = uf_2.find_set(std::get<0>(*e));
    Index c2 = uf_2.find_set(std::get<1>(*e));
    
    if (c1 != c2) {
      uf_2.link(c1, c2);
      last = std::get<2>(*e);
      if (--n_components == 1) break;
    }
    
  }
  
  if(check_a || check_b) {
    bool same_state = true;
    bool all_reached = true;
    for(int i=0; i<m && (same_state || all_reached); i++) {
      if(state[i] && (uf_2.find_set(ms[i].source) != uf_2.find_set(ms[i].target)))
        same_state = false;
      if(uf_2.find_set(ms[i].source) != uf_2.find_set(ms[i].target))
        all_reached = false;
    }
    if(check_a && all_reached) a = CGAL::max(last, max_d*4); 
    if(check_b && same_state) b = CGAL::max(last, max_with_p*4); 
  }
  std::cout << std::endl << std::ceil(CGAL::to_double(a)) << std::endl;
  std::cout << std::ceil(CGAL::to_double(b)) << std::endl; 
  
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cout << std::setiosflags(std::ios::fixed) << std::setprecision(0);
  int t; std::cin >> t;
  while(t--) testcase();
}
