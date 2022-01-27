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
typedef std::pair<K::Point_2,Index> IPoint;

Index valid_clusters(std::vector<Index> &counts, int k) {
  switch(k) {
    case 4: {
      const int match3with1 = std::min(counts[3], counts[1]);
      const int remaining3 = counts[3] - match3with1;
      const int remaining1 = counts[1] - match3with1;
      const int tents_of_2 = (counts[2] + remaining3);
      return counts[4] + match3with1 + tents_of_2/2 + (((tents_of_2 & 1) * 2) + remaining1)/4;
    }
    case 3: {
      const int matched2with1 = std::min(counts[2], counts[1]);
      const int tents_using2 = (counts[2]-matched2with1)/2;
      const int tents_using1 = (counts[1]-matched2with1)/3;
      return counts[4] + counts[3] + matched2with1 + tents_using2 + tents_using1;
    }
    case 2: {
      return counts[4] + counts[3] + counts[2] + counts[1]/2;
    }
    default: {
      return counts[4] + counts[3] + counts[2] + counts[1];
    }
  }
}

void testcase() {
  
  Index n, k, f0, s0; std::cin >> n >> k >> f0 >> s0;

  std::vector<IPoint> points;
  points.reserve(n);
  for (Index i = 0; i < n; ++i) {
    int x, y; std::cin >> x >> y;
    points.emplace_back(K::Point_2(x, y), i);
  }

  Delaunay t;
  t.insert(points.begin(), points.end());

  EdgeV edges;
  edges.reserve(3*n); // there can be no more in a planar graph
  for (auto e = t.finite_edges_begin(); e != t.finite_edges_end(); ++e) {
    Index i1 = e->first->vertex((e->second+1)%3)->info();
    Index i2 = e->first->vertex((e->second+2)%3)->info();
    // ensure smaller index comes first
    if (i1 > i2) std::swap(i1, i2);
    edges.emplace_back(i1, i2, t.segment(e).squared_length());
  }
  std::sort(edges.begin(), edges.end(), [](const Edge& e1, const Edge& e2) -> bool {
    return std::get<2>(e1) < std::get<2>(e2);
  });

  boost::disjoint_sets_with_storage<> uf(n);
  Index n_components = n;
  
  std::vector<int> components(n, 1);
  
  long f = n_components, s = 0;
  std::vector<Index> clust_size(5, 0);
  clust_size[1] = n;
  
  for (EdgeV::const_iterator e = edges.begin(); e != edges.end(); ++e) {
    
    Index c1 = uf.find_set(std::get<0>(*e));
    Index c2 = uf.find_set(std::get<1>(*e));
    
    if(valid_clusters(clust_size, k) == f0) s = std::get<2>(*e);
    
    if (c1 != c2) {
      
      int size_c1 = components[c1];
      int size_c2 = components[c2];
      int size_cn = std::min(4, size_c1+size_c2);
      
      clust_size[size_c1]--; 
      clust_size[size_c2]--; 
      clust_size[size_cn]++; 
      
      uf.link(c1, c2);
      
      components[c1] = components[c2] = size_cn;
      n_components--;
      
      if(std::get<2>(*e) < s0) 
        f = valid_clusters(clust_size, k);
      
      if (n_components == 1) break;
    }
  }
  
  std::cout << s << ' ' << f << std::endl;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  int t; std::cin >> t;
  while(t--) testcase();
}
