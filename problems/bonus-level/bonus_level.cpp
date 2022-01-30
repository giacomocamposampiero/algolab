///1
#include <iostream>
#include <vector>
#include <limits>

typedef std::vector<std::vector<std::vector<int>>> VVVI;
typedef std::vector<std::vector<int>> VVI;

int n;

int play(VVVI &memo, VVI &map, int i1, int i2, int diag) {
  
  int j1 = diag-i1;
  int j2 = diag-i2;
  
  if(i1 == n-1 && j1 == n-1 && i2 == n-1 && j2 == n-1) return map[n-1][n-1];
  if(i2 == n || j2 == n || j1 == n || i1 == n) return -100000;
  
  if(memo[diag][i1][i2] != -1) return memo[diag][i1][i2];
  
  int tmp  = map[i1][j1];
  map[i1][j1] = 0;
  
  int max1 =  std::max(tmp + play(memo, map, i1+1, i2+1, diag+1), tmp + play(memo, map, i1, i2, diag+1));
  int max2 =  std::max(tmp + play(memo, map, i1+1, i2, diag+1), tmp + play(memo, map, i1, i2+1, diag+1));
  
  int score = map[i2][j2] + std::max(max1, max2);
  
  map[i1][j1] = tmp;
  
  memo[diag][i1][i2] = score;
  return score;
}

void testcase() {
  
  std::cin >> n;

  VVI map(n, std::vector<int>(n, 0));
  for(int i=0; i<n; i++) 
    for(int j=0; j<n; j++)
      std::cin >> map[i][j];
      
  VVVI memo(2*n-1, VVI(n, std::vector<int>(n, -1)));
  
  int score = play(memo, map, 0, 0, 0);
  std::cout << score << std::endl;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  int t; std::cin >> t;
  while(t--) testcase();
}
