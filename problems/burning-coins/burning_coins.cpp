#include <vector>
#include <iostream>

std::vector<std::vector<int>> memo;

int funct(std::vector<int> &p, int i, int j) {
  if(i > j) return 0;
  if(memo[i][j] == -1) {
    int common = funct(p, i+1, j-1);
    int front = p[i] + std::min(funct(p, i+2, j), common);
    int back = p[j] + std::min(funct(p, i, j-2), common);
    memo[i][j] = std::max(front, back);
  }
  return memo[i][j];
}

void testcase() {
  int n; std::cin >> n;
  std::vector<int> coin = std::vector<int>(n,0);
  memo = std::vector<std::vector<int>>(n, std::vector<int>(n, -1));
  for(int i=0; i<n; i++) std::cin >> coin[i];
  std::cout << funct(coin, 0, n-1) << std::endl;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  int t; std::cin >> t;
  for(int i=0; i<t; i++) testcase();
}
