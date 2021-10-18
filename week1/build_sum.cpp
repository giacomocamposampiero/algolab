#include <iostream>

void testcase() {
  int n; std::cin >> n;
  int sum = 0;
  for(int j=0; j<n; j++) {
    int a; std::cin >> a;
    sum += a;
  }
  std::cout << sum << std::endl;
}

int main() {
  int t; std::cin >> t;
  for(int i=0; i<t; i++) testcase();
}
