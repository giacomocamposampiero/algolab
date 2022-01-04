#include <iostream>
#include <vector>

std::vector<std::vector<int>> memo;

int best(std::vector<int> &x, int i, int j, int turn, int m, int k) {
  if(i == j && turn % m == k) return x[i];
  else if(i == j) return 0;
  
  if(memo[i][j] != -1) return memo[i][j];
  
  int left = best(x, i+1, j, turn+1, m, k);
  int right = best(x, i, j-1, turn+1, m, k);
  
  if(turn % m == k) memo[i][j] = std::max(x[i]+left, x[j]+right);
  else memo[i][j] = std::min(left, right);
  
  return memo[i][j];
}

void testcase() {
  
  int n, m, k; std::cin >> n >> m >> k;
  std::vector<int> x(n, 0);
  for(int i=0; i<n; i++) std::cin >> x[i];
  
  memo = std::vector<std::vector<int>>(n, std::vector<int>(n, -1));
  int win = best(x, 0, n-1, 0, m, k);
  
  std::cout << win << std::endl;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  int t; std::cin >> t;
  while(t--) testcase();
}
