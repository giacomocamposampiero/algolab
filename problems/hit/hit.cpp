#include <iostream>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel IK;
typedef IK::Ray_2 R;
typedef IK::Point_2 P;
typedef IK::Segment_2 S;

int main() {
  
  std::ios_base::sync_with_stdio(false);
  int n; std::cin >> n;
  
  while(n) {
    
    bool hit = false;
    long x, y, a, b; std::cin >> x >> y >> a >> b;
    R ray(P(x, y), P(a, b));
    
    for(int i=0; i<n; i++) {
      long r, s, t, u; std::cin >> r >> s >> t >> u;
      if(!hit) {
        S segment(P(r, s), P(t, u));
        if(CGAL::do_intersect(ray, segment)) hit = true;
      }
    }
    
    if(hit) std::cout << "yes" << std::endl;
    else std::cout << "no" << std::endl;
    
    std::cin >> n;
    
  }

}
