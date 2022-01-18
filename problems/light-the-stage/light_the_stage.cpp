#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Delaunay_triangulation_2<K>  Triangulation;
typedef Triangulation::Edge_iterator  Edge_iterator;

struct part {
  long x;
  long y;
  int r;
};

void testcase() {
  
  int m, n; std::cin >> m >> n;
  
  std::vector<int> sol;
  
  std::vector<part> ptc(m);
  for(int i=0; i<m; i++) std::cin >> ptc[i].x >> ptc[i].y >> ptc[i].r;
  
  int h; std::cin >> h;
  
  std::vector<K::Point_2> pts;
  pts.reserve(n);
  for (int i = 0; i < n; ++i) {
    long x, y; std::cin >> x >> y;
    pts.push_back(K::Point_2(x, y));
  }

  Triangulation t;
  t.insert(pts.begin(), pts.end());
  
  for(int i=0; i<m; i++) {
    
    K::Point_2 p(ptc[i].x, ptc[i].y);
    K::Point_2 nv = t.nearest_vertex(p) -> point();
    
    K::FT min_dist = K::FT(h + ptc[i].r) * K::FT(h + ptc[i].r);
    
    if(CGAL::squared_distance(nv, p) >= min_dist) sol.push_back(i);
  }
  
  if(sol.size() == 0) {
    
    int left = 0, right = n-1, curr;

    while(left <= right){
      
      int count = 0;
      
      curr = (right + left) / 2;
      
      Triangulation t;
      t.insert(pts.begin(), pts.begin() + curr);
      
      std::vector<int> tmp;
      for(int i=0; i<m; i++) {
        
        K::Point_2 p(ptc[i].x, ptc[i].y);
        K::Point_2 nv = t.nearest_vertex(p) -> point();
        
        K::FT min_dist = K::FT(h + ptc[i].r) * K::FT(h + ptc[i].r);
        
        if(CGAL::squared_distance(nv, p) >= min_dist) { tmp.push_back(i); count++;}
      }
      
      if(count > 0) sol = tmp;
      
      if(count == 0) right = curr - 1;
      else left = curr + 1;
    
    }
    
  }
  for(std::size_t i=0; i<sol.size(); i++) std::cout << sol[i] << ' ';
  std::cout << std::endl;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  int t; std::cin >> t;
  while(t--) testcase();
}
