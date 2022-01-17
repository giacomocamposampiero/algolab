#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Triangulation_face_base_with_info_2.h>
#include <queue>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Triangulation_vertex_base_2<K> Vb;
typedef CGAL::Triangulation_face_base_with_info_2<K::FT,K> Fb;
typedef CGAL::Triangulation_data_structure_2<Vb,Fb> Tds;
typedef CGAL::Delaunay_triangulation_2<K,Tds>  Triangulation;
typedef Triangulation::Face_handle  Face_handle;

void precomputation(Triangulation &t) {
  
  std::priority_queue<std::pair<double, Face_handle>> queue;
  
  for (auto f = t.all_faces_begin(); f != t.all_faces_end(); ++f) {
    if(t.is_infinite(f)) queue.push(std::make_pair(std::numeric_limits<long>::max(), f));
    f->info() = 0;
  }
  
  while(!queue.empty()) {
    
    auto curr = queue.top(); queue.pop();
    double ccost = curr.first;
    auto cface = curr.second;
  
    if(cface -> info() >= ccost) continue;
    cface -> info() = ccost;
    
    for(int i=0; i<3; i++) {
      
      auto neighbor = cface->neighbor(i);
      if (t.is_infinite(neighbor) || neighbor->info() != 0) continue;
      
      Triangulation::Vertex_handle v1 = cface->vertex((i + 1) % 3);
      Triangulation::Vertex_handle v2 = cface->vertex((i + 2) % 3);
      double min = CGAL::min(CGAL::squared_distance(v1->point(), v2->point()), ccost);
      
      queue.push(std::make_pair(min, neighbor));
    }
    
  }
}


int main() {
  
  std::ios_base::sync_with_stdio(false);
  
  while(true) {

    std::size_t n; std::cin >> n;
    if(n == 0) return 0;
    
    std::vector<K::Point_2> pts;
    pts.reserve(n);
    for (std::size_t i = 0; i < n; ++i) {
      int x, y; std::cin >> x >> y;
      pts.push_back(K::Point_2(x, y));
    }

    Triangulation t;
    t.insert(pts.begin(), pts.end());
    
    precomputation(t);
    
    int m; std::cin >> m;
    while(m--) {
      
      int x, y; std::cin >> x >> y;
      K::Point_2 person(x, y);
      long d; std::cin >> d;
      
      auto nn = t.nearest_vertex(person);
      if(CGAL::squared_distance(nn -> point(), person) < d) {
        std::cout << 'n';
        continue;
      }
    
      long min_edge = 4*d;
      bool valid = t.locate(person) -> info() >= min_edge;
      std::cout << "ny"[valid];
    }
    std::cout << std::endl;
  }
}
