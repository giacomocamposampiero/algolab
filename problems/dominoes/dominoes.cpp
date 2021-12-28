#include <iostream>

void testcase() {
  int n; std::cin >> n;
  int max_dist = 2;
  int j;
  for(j=1; j<=n; j++) {
    int h; std::cin >> h;
    if(max_dist>j && j+h>max_dist) max_dist = j+h;
  }
  if(max_dist-1 > n) std::cout << n << std::endl;
  else std::cout << max_dist - 1 << std::endl;
}

int main() {
  int t; std::cin >> t;
  for(int i=0; i<t; i++) testcase();
}
