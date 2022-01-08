#include <CGAL/Gmpq.h>

#include <iostream>
#include <vector>
#include <algorithm>

void testcase() {
  
  int n; std::cin >> n;
  std::vector<bool> infinite(n, true);
  
  std::vector<std::tuple<long, CGAL::Gmpq, long>> info;
  for(int i=0; i<n; i++) {
    long y0, x1, y1; std::cin >> y0 >> x1 >> y1;
    info.push_back(std::make_tuple(y0, CGAL::Gmpq(y1 - y0, x1), i));
  }
  
  std::sort(info.begin(), info.end(), [](const auto a, const auto b) {
    return std::get<0>(a) < std::get<0>(b);   
  });
  
  CGAL::Gmpq min_slope = std::get<1>(info[n-1]);
  infinite[std::get<2>(info[n-1])] = true;
  
  // top-bottom iteration
  for(int i=n-2; i>=0; i--) {
    if(CGAL::abs(std::get<1>(info[i])) <= CGAL::abs(min_slope)) 
      min_slope = std::get<1>(info[i]);
    else if(std::get<1>(info[i]) > min_slope)
      infinite[std::get<2>(info[i])] = false;
  }
  
  // bottom-top iteration
  min_slope = std::get<1>(info[0]);
  for(int i=1; i<n; i++) {
    if(CGAL::abs(std::get<1>(info[i])) < CGAL::abs(min_slope) || (CGAL::abs(std::get<1>(info[i])) == CGAL::abs(min_slope) &&  std::get<1>(info[i]) > min_slope)) 
      min_slope = std::get<1>(info[i]);
    else if(std::get<1>(info[i]) < min_slope)
      infinite[std::get<2>(info[i])] = false;
  }
  
  for(std::size_t i=0; i<infinite.size(); i++) 
    if(infinite[i]) std::cout << i << ' ';
  std::cout << std::endl;
  
}

int main() {
  std::ios_base::sync_with_stdio(false);
  int t; std::cin >> t;
  while(t--) testcase();
}
