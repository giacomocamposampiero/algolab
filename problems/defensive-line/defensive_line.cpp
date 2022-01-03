#include <iostream>
#include <vector>

std::vector<std::vector<int>> memo;

int explore(std::vector<int> &ivs, int index, int attackers) {
  
  if(attackers == 0) return 0;
  if((int) ivs.size() - index < attackers) return -1;
  if(memo[index][attackers] != -2) return memo[index][attackers];
  
  if(ivs[index] == -1) memo[index][attackers] = explore(ivs, index + 1, attackers);
  else {
    int next_take = explore(ivs, index + ivs[index], attackers-1);
    int take = next_take >= 0 ? ivs[index] + next_take : -1;
    int pass = explore(ivs, index + 1, attackers);
    memo[index][attackers] = std::max(take, pass);
  //std::cout <<"interval " << index << " || take "<< take << " || pass " << pass << " || att "<<attackers << std::endl;
  }
  return memo[index][attackers];
}


void testcase() {

  int n, m, k; std::cin >> n >> m >> k;
  std::vector<int> ps(n+1, 0);
  for(int i=1; i<=n; i++) {
    int v; std::cin >> v;
    ps[i] = ps[i-1] + v;
  }
  
  // sliding window to find intervals, O(n)
  int i=0, j=1;
  std::vector<int> starting = std::vector<int>(n, -1);

  while(i<n) {
    while(j<n && ps[j]-ps[i] < k) j++;
    if(ps[j]-ps[i] == k) starting[i] = j-i;
    i++;
  }
  
  // DP
  memo = std::vector<std::vector<int>>(n, std::vector<int>(m+1, -2));
  int res = explore(starting, 0, m);
  if(res != -1) std::cout << res << std::endl;
  else std::cout << "fail" << std::endl;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  int t; std::cin >> t;
  while(t--) testcase();
}
