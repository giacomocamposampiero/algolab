#include <iostream>
#include <vector>

void testcase() {
  
  int n; std::cin >> n;
  
  std::vector<std::vector<int>> II(n+1, std::vector<int>(n+1, 0));
  
  for(int i=1; i<=n; i++) {
    for(int j=1; j<=n; j++) {
      int v; std::cin >> v;
      II[i][j] = II[i-1][j]+II[i][j-1]-II[i-1][j-1]+v;
    }
  }

  int result = 0;
  
  for(int i=1; i<=n; i++) {
    for(int j=i; j<=n; j++) {
      int odd = 0;
      int even = 0;
      for(int x=1; x<=n; x++) {
        if ((II[j][x]-II[i-1][x])%2==0) even++;
        else odd++;
      }

      result += (even*(even-1))/2 + even + (odd*(odd-1))/2;
    }
  }
  
  std::cout << result << std::endl;
}


int main() {
  std::ios_base::sync_with_stdio(false);
  int t; std::cin >> t;
  for(int i=0; i<t; i++) testcase();
}
