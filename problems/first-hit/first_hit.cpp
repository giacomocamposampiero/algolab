#include <iostream>
#include <CGAL/Exact_predicates_exact_constructions_kernel.h>

typedef CGAL::Exact_predicates_exact_constructions_kernel K;
typedef K::Point_2 P;
typedef K::Segment_2 S;
typedef K::Ray_2 R;

double floor_to_double(const K::FT& x) {
  double a = std::floor(CGAL::to_double(x));
  while (a > x) a -= 1;
  while (a+1 <= x) a += 1;
  return a;
}

void testcase(int n) {
  
  long x, y, a, b; std::cin >> x >> y >> a >> b;
  
  P origin(x, y), punto(a, b);
  R ray(origin, punto);
  std::vector<S> segms;
  
  bool intersect = false;
  S opt;
  
  for(int i=0; i<n; i++) {
    long r, s, t, u; std::cin >> r >> s >> t >> u;
    segms.push_back(S(P(r,s), P(t,u)));
  }
  
  std::random_shuffle(segms.begin(), segms.end());
    
  for(int i=0; i<n; i++) {
    if((!intersect && CGAL::do_intersect(ray, segms[i])) || (intersect && CGAL::do_intersect(opt, segms[i]))) {
      auto o = (!intersect)? CGAL::intersection(ray, segms[i]) : CGAL::intersection(opt, segms[i]);
      P intersection;
      if (const P* op = boost::get<P>(&*o)) {
        intersection = *op;
      } else if (const S* os = boost::get<S>(&*o)) {
        K::FT d1 = CGAL::squared_distance((*os).source(), origin);
        K::FT d2 = CGAL::squared_distance((*os).target(), origin);
        intersection = (d1 < d2)? (*os).source() : (*os).target();
      }
      opt = S(intersection, origin);
      if(!intersect) intersect=true;
    }
  }
  
  if(intersect) {
    long r1 = floor_to_double(opt.source().x());
    long r2 = floor_to_double(opt.source().y());
    std::cout << r1 << ' ' << r2 << std::endl;
  } else std::cout << "no" << std::endl;  

}

int main() {
  std::ios_base::sync_with_stdio(false);
  int n; std::cin >> n;
  while(n != 0) {
    testcase(n);
    std::cin >> n;
  }
}


