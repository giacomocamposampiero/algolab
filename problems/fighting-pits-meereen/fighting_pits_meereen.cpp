///3
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

typedef std::vector<int> P;
typedef std::vector<P> Q;
typedef std::vector<Q> R;
typedef std::vector<R> M;

M memo;
int n, k, m; 

int score(int gate, int q, int fighter) {
  if(q == 1) return 1000;
  if(q == 2) return 1000 + 1000*(fighter != gate%k);
  return 1000 + ((gate/k != gate%k) && (gate/k != fighter))*1000 + (gate%k != fighter)*1000;
}

int update_gate(int gate, int fighter, int q) {
  return (q < 2)? fighter : fighter + (gate % k)*k;
}


int dp(std::vector<int> &fts, int p, int q, int north, int south) {

  if(std::abs(p-q) > 11) return -1;
  if(p + q == n) return 0;
  
  if(memo[p+q][p-q+11][north][south] != -2)  return memo[p+q][p-q+11][north][south];
  
  int fighter = fts[p+q];
  
  int nsc = score(north, std::min(p+1, m), fighter) - std::pow(2, std::abs(p+1-q));
  int ssc = score(south, std::min(q+1, m), fighter) - std::pow(2, std::abs(p-q-1));
  
  int nnext = dp(fts, p+1, q, update_gate(north, fighter, std::min(p+1, m)), south);
  int snext = dp(fts, p, q+1, north, update_gate(south, fighter, std::min(q+1, m)));
  
  int north_score = (nnext >= 0) ? nsc + nnext : -1;
  int south_score = (snext >= 0) ? ssc + snext : -1;
  
  memo[p+q][p-q+11][north][south] = std::max(north_score, south_score);
  return memo[p+q][p-q+11][north][south];
}

void testcase() {
  
  std::cin >> n >> k >> m;
  std::vector<int> fts = std::vector<int>(n,0);
  for(int i=0; i<n; i++) std::cin >> fts[i];
  memo = M(n, R(24, Q(k*k+1, P(k*k+1, -2))));
  int res = dp(fts, 0, 0, 0, 0);
  std::cout << res << std::endl;
  
}

int main() {
  std::ios_base::sync_with_stdio(false);
  int t; std::cin >> t;
  while(t--) testcase();
}
