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

void testcase() {
  
  std::size_t n, k, f0, s0; std::cin >> n >> k >> f0 >> s0;

  // Read points associated with an integer ID
  typedef std::pair<K::Point_2,Index> IPoint;
  std::vector<IPoint> points;
  points.reserve(n);
  for (Index i = 0; i < n; ++i) {
    int x, y; std::cin >> x >> y;
    points.emplace_back(K::Point_2(x, y), i);
  }

  // Build Delauny triangulation with the given points
  // This step takes O(n log n) time (for constructing the triangulation).
  Delaunay t;
  t.insert(points.begin(), points.end());

  // Sort the triangulation edges on their squared length
  // This step takes O(n log n) time (for the sorting).
  EdgeV edges;
  edges.reserve(3*n); 
  for (auto e = t.finite_edges_begin(); e != t.finite_edges_end(); ++e) {
    Index i1 = e->first->vertex((e->second+1)%3)->info();
    Index i2 = e->first->vertex((e->second+2)%3)->info();
    edges.emplace_back(i1, i2, t.segment(e).squared_length());
  }
  std::sort(edges.begin(), edges.end(), [](const Edge& e1, const Edge& e2) -> bool {
    return std::get<2>(e1) < std::get<2>(e2);
  });

  // Initialize union-find data structure
  boost::disjoint_sets_with_storage<> uf(n);
  std::size_t cl = n, f, s;
  bool up = true;
  // For every edge, if the length of the edge is lower than s0 merge the two
  // components in order to get a cluster, otherwise we have found all the clusters
  for (EdgeV::const_iterator e = edges.begin(); e != edges.end(); ++e) {
    // If the number of clusters equals to f0, the current edge length corresponds to
    // the minimum distance edge connecting two clusters (=s)
    if(cl == f0) s = std::get<2>(*e); 
    // If the current edge length is the first one to be greater than s0, the current
    // number of cluster equals to the largest number of families that can be hosted
    if(std::get<2>(*e) >= s0 && up) {f = cl; up = false;}
    Index c1 = uf.find_set(std::get<0>(*e));
    Index c2 = uf.find_set(std::get<1>(*e));
    if (c1 != c2) {uf.link(c1, c2); --cl;}
  }
  
  std::cout << s << ' ' << f <<  std::endl;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  int t; std::cin >> t;
  for(int i=0; i<t; i++) testcase();
}
