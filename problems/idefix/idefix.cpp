///1
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

typedef size_t                                                 Index;
typedef CGAL::Triangulation_vertex_base_with_info_2<Index,K>   Vb;
typedef CGAL::Triangulation_face_base_2<K>                     Fb;
typedef CGAL::Triangulation_data_structure_2<Vb,Fb>            Tds;
typedef CGAL::Delaunay_triangulation_2<K,Tds>                  Delaunay;

typedef std::tuple<Index,Index,K::FT> Edge;
typedef std::vector<Edge> EdgeV;
typedef Delaunay::Vertex_iterator  Vertex_iterator;

typedef std::pair<K::Point_2,Index> IPoint;

void testcase() {
  
  long s; int n, m, k; std::cin >> n >> m >> s >> k;

  std::vector<IPoint> pts;

  for(int i = 0; i < n; ++i) {
    int x, y; std::cin >> x >> y;
    pts.emplace_back(K::Point_2(x, y), i);
  }
  Delaunay t;
  t.insert(pts.begin(), pts.end());

  EdgeV edges;
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
    if(std::get<2>(*e) > s) break;
    Index c1 = uf.find_set(std::get<0>(*e));
    Index c2 = uf.find_set(std::get<1>(*e));
    if (c1 != c2) {
      uf.link(c1, c2);
      --n_components;
    }
    if(n_components == 1) break;
  }
  
  std::vector<int> bones(n, 0);
  std::vector<int> cbones(n+m, 0);
  for(int i=0; i<m; i++) {
    
    int x, y; std::cin >> x >> y;
    K::Point_2 bone(x,y);
    
    auto nv = t.nearest_vertex(bone);
    K::FT distance = 4*CGAL::squared_distance(bone, nv -> point());
    if(distance <= s) bones[uf.find_set(nv -> info())]++;
    
    edges.emplace_back(nv -> info(), n+i, distance);
    cbones[n+i]++;
  }

  int a = 0;
  for(int i=0; i<n; i++) a = std::max(a, bones[i]);
  
  std::sort(edges.begin(), edges.end(), [](const Edge& e1, const Edge& e2) -> bool {
    return std::get<2>(e1) < std::get<2>(e2);
  });
  
  boost::disjoint_sets_with_storage<> uf2(n+m);
  n_components = n+m;
  
  long b = 4*s;
  for (EdgeV::const_iterator e = edges.begin(); e != edges.end(); ++e) {
    Index c1 = uf2.find_set(std::get<0>(*e));
    Index c2 = uf2.find_set(std::get<1>(*e));
    if (c1 != c2) {
      uf2.link(c1, c2);
      int comp = uf2.find_set(std::get<0>(*e));
      cbones[comp] = cbones[c2] + cbones[c1];
      if(cbones[comp] >= k) { b=std::get<2>(*e); break; }
      --n_components;
    }
    if(n_components == 1) break;
  }
  
  std::cout << a << ' ' << b << std::endl;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  int t; std::cin >> t;
  while(t--) testcase();
}
