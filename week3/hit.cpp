#include <iostream>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef K::Point_2 P;
typedef K::Segment_2 S;
typedef K::Ray_2 R;

int main() {
  
  std::ios_base::sync_with_stdio(false);
  int n; std::cin >> n;
  
  while(n != 0) {
    bool intersect = false;
    long x; std::cin >> x;
    long y; std::cin >> y;
    long a; std::cin >> a;
    long b; std::cin >> b;
    
    P r1(x, y), r2(a, b);
    R ray(r1, r2);
    
    
    for(int i=0; i<n; i++) {
      long r; std::cin >> r;
      long s; std::cin >> s;
      long t; std::cin >> t;
      long u; std::cin >> u;
      if(!intersect) {
        P s1(r, s), s2(t, u);
        S segment(s1, s2);
        if(CGAL::do_intersect(ray, segment)) intersect = true;
      }
    }
    if(intersect) std::cout << "yes" << std::endl;
    else std::cout << "no" << std::endl;
    std::cin >> n;
  }
}
