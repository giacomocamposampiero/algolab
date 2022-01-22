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
  
  std::vector<std::vector<long>> oak_bones(n);
  for(int i=0; i<m; i++) {
    int x, y; std::cin >> x >> y;
    K::Point_2 bone(x,y);
    auto nv = t.nearest_vertex(bone);
    oak_bones[nv -> info()].push_back(CGAL::squared_distance(bone, nv -> point()));
  }

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
  int a = 0, max_b = 0;
  std::vector<int> tot(n, 0);
  
  for(int i=0; i<n; i++) {
    std::sort(oak_bones[i].begin(), oak_bones[i].end());
    auto it = std::upper_bound(oak_bones[i].begin(), oak_bones[i].end(), s/4);
    tot[i] = std::distance(oak_bones[i].begin(), it);
    max_b = std::max(max_b, tot[i]);
  }
  
  for (EdgeV::const_iterator e = edges.begin(); e != edges.end() && a ==0; ++e) {
    Index c1 = uf.find_set(std::get<0>(*e));
    Index c2 = uf.find_set(std::get<1>(*e));
    
    if(a == 0 && std::get<2>(*e) > s) a = max_b;
    
    if (c1 != c2) {
      int new_tot = tot[c1] + tot[c2];
      if(new_tot > max_b) max_b = new_tot;
      
      uf.link(c1, c2);
      
      int new_class = uf.find_set(std::get<0>(*e));
      tot[new_class] = new_tot;
      --n_components;
    }
    if(n_components == 1) break;
  }
  
  std::cout << a << ' ' << 4*s << std::endl;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  int t; std::cin >> t;
  while(t--) testcase();
}
