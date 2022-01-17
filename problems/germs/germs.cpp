#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/nearest_neighbor_delaunay_2.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Delaunay_triangulation_2<K>  Triangulation;
typedef Triangulation::Vertex_iterator  Vertex_iterator;
typedef Triangulation::Edge_circulator  Edge_circulator;


int main() {

  std::ios_base::sync_with_stdio(false);
  
  while(true) {

    int n; std::cin >> n;
    if(n==0) return 0;
    
    int l, b, r, t; std::cin >> l >> b >> r >> t;
  
    std::vector<K::Point_2> pts;
    pts.reserve(n);
    for (int i = 0; i < n; ++i) {
      int x, y; std::cin >> x >> y;
      pts.push_back(K::Point_2(x, y));
    }
    Triangulation tr;
    tr.insert(pts.begin(), pts.end());
    
    std::vector< K::FT> times;
    for(auto v = tr.finite_vertices_begin(); v != tr.finite_vertices_end(); ++v){
      K::FT dx = CGAL::min(CGAL::abs(l - v -> point().x()), CGAL::abs(r - v -> point().x()));
      K::FT dy = CGAL::min(CGAL::abs(b - v -> point().y()), CGAL::abs(t - v -> point().y()));

      K::FT d = 2*CGAL::min(dx, dy);
      d *= d;

      auto neighbor = CGAL::nearest_neighbor(tr, v);
      if(neighbor != NULL) d = CGAL::min(CGAL::squared_distance(neighbor -> point(), v -> point()), d);

      times.push_back(d);
    }
    
    std::sort(times.begin(), times.end());
    
    K::FT first = times[0];
    K::FT half = times[n / 2];
    K::FT last = times[n - 1];
    
    std::cout << std::fixed << std::setprecision(0) << ceil(CGAL::to_double(CGAL::sqrt((CGAL::sqrt(first) - 1) / 2))) << " ";
    std::cout << std::fixed << std::setprecision(0) << ceil(CGAL::to_double(CGAL::sqrt((CGAL::sqrt(half) - 1) / 2))) << " ";
    std::cout << std::fixed << std::setprecision(0) << ceil(CGAL::to_double(CGAL::sqrt((CGAL::sqrt(last) - 1) / 2))) << "\n";
  }
}
