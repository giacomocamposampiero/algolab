#include <iostream>
#include <vector>
#include <limits> 

void testcase() {
  int n, k; std::cin >> n >> k;
  std::vector<int> s = std::vector<int>(n+1, 0);
  for(int i=1; i<=n; i++) {
    int v; std::cin >> v;
    s[i] = v + s[i-1];
  }
  
  int i=0, j=1;
  int bi=0, bj=1, mindiff = std::numeric_limits<int>::max();
  while(j<=n) {
    int diff = s[j]-s[i]-k;
    if(std::abs(diff) < mindiff) { bi = i; bj = j-1; mindiff = std::abs(diff); }
    if(diff < 0) j++;
    else i++;
  }
  
  std::cout << bi << ' ' << bj << std::endl;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  int t; std::cin >> t;
  for(int i=0; i<t; i++) testcase();
}
