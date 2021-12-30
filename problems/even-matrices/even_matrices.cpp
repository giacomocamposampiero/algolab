#include <iostream>
#include <vector>

void testcase() {
  int n; std::cin >> n;
  std::vector<std::vector<int>> s = std::vector<std::vector<int>>(n+1, std::vector<int>(n+1,0));
  for(int i=1; i<=n; i++) {
    for(int j=1; j<=n; j++) {
      int m; std::cin >> m;
      s[i][j] = m + s[i-1][j] + s[i][j-1] - s[i-1][j-1];
    }
  }
  int res = 0;
  for(int i1=0; i1<=n; i1++) {
    for(int i2=i1+1; i2<=n; i2++) {
      int even = 0, odd = 0;
      for(int j=1; j<=n; j++) {
        if((s[i1][j]+s[i2][j])%2==0) even++;
        else odd++;
      }
      res += even + even*(even-1)/2 + odd*(odd-1)/2;
    }
  }
  std::cout << res << std::endl;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  int t; std::cin >> t;
  for(int i=0; i<t; i++) testcase();
}
