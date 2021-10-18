#include <iostream>
#include <vector>
#include <climits>

int strategy(int index, int ms, std::vector<int> &ivs, std::vector<std::vector<int>> &memo) {
  if(ms == 0) return 0;
  if(index == (int)ivs.size()) return INT_MIN;
  if(memo[index][ms] != -1) return memo[index][ms];
  
  int res;
  
  if(ivs[index] == -1) res = strategy(index+1, ms, ivs, memo);
  else res = std::max(ivs[index]+strategy(index+ivs[index], ms-1, ivs, memo), strategy(index+1, ms, ivs, memo));
  
  memo[index][ms] = res;
  return res;
}

void testcase() {
  int n; std::cin >> n;
  int m; std::cin >> m;
  int k; std::cin >> k;
  
  // read defense values
  std::vector<int> defense(n+1, 0);
  for(int i=1; i<=n; i++) {
    int tmp; std::cin >> tmp;
    defense[i] = defense[i-1] + tmp;
  }
  
  // find all intervals 
  int i=1, j=1;
  std::vector<int> ivs(n, -1);
  while(j<=n) {
    while(defense[j]-defense[i-1] < k && j<=n) j++;
    if(defense[j]-defense[i-1] == k) ivs[i-1] = j-i+1;
    i++;
  }
  
  std::vector<std::vector<int>> memo(ivs.size(), std::vector<int>(m+1, -1));
  int res = strategy(0, m, ivs, memo);

  // output
  if(res < 1) std::cout << "fail" << std::endl;
  else std::cout << res << std::endl;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  int t; std::cin >> t;
  for(int i=0; i<t; i++) testcase();
}
