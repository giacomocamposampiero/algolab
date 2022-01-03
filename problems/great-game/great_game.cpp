#include <vector>
#include <iostream>

std::vector<std::vector<int>> memo;

int min_winning(std::vector<std::vector<int>> &t, int index, bool player, int n) {

  if(index == n) return 0;
  if(memo[index][player] != -1) return memo[index][player];
  
  // if player, player move --> min, otherwise adversary move --> max
  std::vector<int> following = t[index];
  int dist = player ? n : -1;
  for(int size=following.size(), i=0; i<size; i++) {
    int next = min_winning(t, following[i], !player, n);
    dist = player ? std::min(dist, next) : std::max(dist, next);
  }
  memo[index][player] = dist + 1;
  return dist + 1;
}

void testcase() {
  
  int n, m; std::cin >> n >> m;
  int r, b; std::cin >> r >> b;
  std::vector<std::vector<int>> transitions(n+1, std::vector<int>());
  for(int i=0; i<m; i++) {
    int u, v; std::cin >> u >> v;
    transitions[u].push_back(v);
  }
  
  memo = std::vector<std::vector<int>>(n+1, std::vector<int>(2, -1));
  int red = min_winning(transitions, r, true, n);
  int black = min_winning(transitions, b, true, n);
  
  if(black < red) std::cout << 1 << std::endl;
  else if(red < black) std::cout << 0 << std::endl;
  else std::cout << (red % 2 == 0) << std::endl;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  int t; std::cin >> t;
  while(t--) testcase();
}
