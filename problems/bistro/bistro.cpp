#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Delaunay_triangulation_2<K>  Triangulation;
typedef Triangulation::Edge_iterator  Edge_iterator;
typedef Triangulation::Vertex_handle  Vertex_handle;

int main() {
  
  std::ios_base::sync_with_stdio(false);
  
  while(true) {
    
    std::size_t n; std::cin >> n;
    if(n == 0) return 0;
    // read points
    std::vector<K::Point_2> pts;
    pts.reserve(n);
    for (std::size_t i = 0; i < n; ++i) {
      int x, y; std::cin >> x >> y;
      pts.push_back(K::Point_2(x, y));
    }
    // construct triangulation
    Triangulation t;
    t.insert(pts.begin(), pts.end());
    
    int m; std::cin >> m;
    for(int i=0; i<m; i++) {
      int x, y; std::cin >> x >> y;
      K::Point_2 pos(x, y);
      Vertex_handle v = t.nearest_vertex(pos);
      std::cout << (long) CGAL::squared_distance(v->point(), pos) << std::endl;
    }
  }
  
}
