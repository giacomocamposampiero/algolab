#include <iostream>
#include <vector>
#include <unordered_map>
#include <map>
#include <algorithm>

int distance(int n, int meeple, int max, std::vector<std::vector<int>> &tran, std::vector<std::vector<int>> &memo) {
  if(meeple == n) return 0;
  if(memo[meeple][max] != -1) return memo[meeple][max];
  
  int tmp;
  if(max) {
    tmp = n;
    for(int i=0, tsize=tran[meeple].size(); i<tsize; i++) {
      int dist = 1 + distance(n, tran[meeple][i], 0, tran, memo);
      if(dist < tmp) tmp = dist;
    }
  } else {
    tmp = -1;
    for(int i=0, tsize=tran[meeple].size(); i<tsize; i++) {
      int dist = 1 + distance(n, tran[meeple][i], 1, tran, memo);
      if(dist > tmp) tmp = dist;
    }
  }
  
  memo[meeple][max] = tmp;
  return tmp;
}

void testcase() {
  int n; std::cin >> n;
  int m; std::cin >> m;
  int r; std::cin >> r; // starting position red
  int b; std::cin >> b; // starting position black
  std::vector<std::vector<int>> tran(n+1, std::vector<int>());
  
  for(int i=0; i<m; i++) {
    int u; std::cin >> u; // start transition
    int v; std::cin >> v; // end transition
    tran[u].push_back(v);
  }

  std::vector<std::vector<int>> memo(n, std::vector<int>(2, -1));

  // output
  int ds = distance(n, r, 1, tran, memo);
  int dm = distance(n, b, 1, tran, memo);
  
  int winner = (ds < dm)? 0 : 1;
  if(ds == dm) winner = (ds%2 == 0)? 1 : 0;
  std::cout << winner << std::endl;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  int t; std::cin >> t;
  for(int i=0; i<t; i++) testcase();
}
