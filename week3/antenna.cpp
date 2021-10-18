#include <CGAL/Exact_predicates_exact_constructions_kernel_with_sqrt.h>
#include <CGAL/Min_circle_2.h>
#include <CGAL/Min_circle_2_traits_2.h>
#include <vector>

typedef  CGAL::Exact_predicates_exact_constructions_kernel_with_sqrt K;
typedef  CGAL::Min_circle_2_traits_2<K> Traits;
typedef  CGAL::Min_circle_2<Traits> Min_circle;
typedef K::Point_2 P;

double floor_to_double(const K::FT& x) {
  double a = std::ceil(CGAL::to_double(x));
  while (a < x) a += 1;
  while (a-1 >= x) a -= 1;
  return a;
}

void testcase(int n) {
  std::vector<P> cit;
  for(int i=0; i<n; i++) {
    long x; std::cin >> x;
    long y; std::cin >> y;
    cit.push_back(P(x, y));
  }
  Min_circle mc(cit.begin(), cit.end(), true);
  Traits::Circle c = mc.circle();
  long radius = floor_to_double(CGAL::sqrt(c.squared_radius()));
  std::cout << radius << std::endl;
}

int main() {
  int n; std::cin >> n;
  while(n != 0) {
    testcase(n);
    std::cin >> n;
  }
}
