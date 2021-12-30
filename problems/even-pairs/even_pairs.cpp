#include <vector>
#include <iostream>

void testcase() {
  int n; std::cin >> n;
  int sum = 0, even = 0, odd = 0;
  for(int i=0; i<n; i++) {
    int x; std::cin >> x;
    sum += x;
    if(sum % 2 == 0) even++;
    else odd++;
  }
  int intervals = even + even*(even-1)/2 + odd*(odd-1)/2;
  std::cout << intervals << std::endl;
}

int main() {
  int t; std::cin >> t;
  for(int i=0; i<t; i++) testcase();
}
