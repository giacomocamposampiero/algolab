///4
#include <CGAL/Exact_predicates_exact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Triangulation_face_base_with_info_2.h>
#include <queue>

typedef CGAL::Exact_predicates_exact_constructions_kernel K;
typedef CGAL::Triangulation_vertex_base_2<K> Vb;
typedef CGAL::Triangulation_face_base_with_info_2<K::FT,K> Fb;
typedef CGAL::Triangulation_data_structure_2<Vb,Fb> Tds;
typedef CGAL::Delaunay_triangulation_2<K,Tds>  Triangulation;
typedef Triangulation::Face_iterator Face_iterator;
typedef Triangulation::Face_handle Face_handle;

void preprocessing(Triangulation &t) {
  
  std::priority_queue<std::pair<K::FT, Face_handle>> queue;
  
  for (auto f = t.all_faces_begin(); f != t.all_faces_end(); ++f) {
    
    if(t.is_infinite(f)) 
      queue.emplace(std::numeric_limits<double>::max(), f);
    else 
      queue.emplace(CGAL::squared_distance(t.dual(f), f->vertex(0)->point()), f);
      
    f -> info() = 0;
  }
  
  while(!queue.empty()) {
    
    auto curr = queue.top(); queue.pop();
    
    K::FT clearance = curr.first;
    Face_handle face = curr.second;
    
    if(face -> info() >= clearance) continue;
    face -> info() = clearance;
    
    for(int i=0; i<3; i++) {
      
      Face_handle neighbor = face->neighbor(i);
      if(t.is_infinite(neighbor) || neighbor -> info() != 0) continue;
      
      K::Point_2 u = face->vertex((i+1) % 3) -> point();
      K::Point_2 v = face->vertex((i+2) % 3) -> point();
      K::FT edge_len = CGAL::squared_distance(u, v);
      
      queue.emplace(CGAL::min(edge_len, clearance), neighbor);
    }
  }
  
}

void testcase() {
  
  int n, m; std::cin >> n >> m;
  long r; std::cin >> r;

  std::vector<K::Point_2> pts;
  pts.reserve(n);
  for (int i = 0; i < n; ++i) {
    long x, y; std::cin >> x >> y;
    pts.push_back(K::Point_2(x, y));
  }
  
  Triangulation t;
  t.insert(pts.begin(), pts.end());
  
  preprocessing(t);
  
  while(m--) {
    
    long x, y, s; std::cin >> x >> y >> s;

    K::Point_2 point(x,y);
    K::FT min_dist = K::FT(r+s) * K::FT(r+s);
    K::FT clearance = K::FT(2*r + 2*s) * K::FT(2*r + 2*s);

    K::FT init_dist = CGAL::squared_distance(point, t.nearest_vertex(point) -> point());
    
    if(init_dist < min_dist) {
      std::cout << 'n';
      continue;
    }
    
    auto face = t.locate(point);
    
    if(face -> info() >= 4 * min_dist) std::cout << 'y';
    else std::cout << 'n';
  }
  std::cout << std::endl;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  int t; std::cin >> t;
  while(t--) testcase();
}
