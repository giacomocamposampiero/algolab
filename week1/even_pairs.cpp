#include <iostream>
#include <vector>

void testcase() {
  int n; std::cin >> n;
  int sum = 0;
  int even=0, odd=0;
  for(int j=0; j<n; j++) {
    int num; std::cin >> num;
    sum += num;
    if(sum%2==0) even++;
    else odd++;
  }
  int result = even + even*(even-1)/2 + odd*(odd-1)/2;
  std::cout << result << std::endl;
}

int main() {
  int t; std::cin >> t;
  for(int i=0; i<t; i++) testcase();
}
