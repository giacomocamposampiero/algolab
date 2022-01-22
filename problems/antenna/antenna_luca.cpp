#include <bits/stdc++.h>
#include <CGAL/Exact_predicates_exact_constructions_kernel_with_sqrt.h>
#include <CGAL/Min_circle_2.h>
#include <CGAL/Min_circle_2_traits_2.h>

using namespace std;

typedef CGAL::Exact_predicates_exact_constructions_kernel_with_sqrt K;
typedef CGAL::Min_circle_2_traits_2<K> Traits;
typedef CGAL::Min_circle_2<Traits> Min_circle;
typedef K::Point_2 P;

long ceil_to_double(const K::FT& x)
{
  double a = ceil(CGAL::to_double(x));
  while (a < x) a += 1;
  while (a-1 >= x) a -= 1;
  return (long)a;
}

bool testcase(){
  int n; cin >> n;
  if(n == 0)  return true;
  
  vector<P> points;
  long x, y;
  for(int i = 0; i < n; i++){
    cin >> x >> y;
    points.push_back(P(x,y));
  }
  
  Min_circle mc(points.begin(), points.end(), true);
  Traits::Circle c = mc.circle();
  
  cout << ceil_to_double(CGAL::sqrt(c.squared_radius())) << endl;
  return false;
}

int main(){
  ios_base::sync_with_stdio(false);
  bool end = false;
  while(!end)
    end = testcase();
  
  return 0;
}