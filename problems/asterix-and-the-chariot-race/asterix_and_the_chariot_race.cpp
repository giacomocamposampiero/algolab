///
#include <vector>
#include <iostream>
#include <limits>

struct subtree {
  int picked;
  int covered;
  int not_covered;
};

subtree dfs(int root, std::vector<std::vector<int>> &tree, std::vector<int> &cost) {
  
  int picked = 0, covered = 0, not_covered = 0;
  int min_diff_covered = std::numeric_limits<int>::max();
  
  for(std::size_t i=0; i<tree[root].size(); i++) {
    
    auto sub = dfs(tree[root][i], tree, cost);
    
    picked += sub.picked;
    covered += sub.covered;
    not_covered += sub.not_covered;
    min_diff_covered = std::min(min_diff_covered, sub.picked - sub.covered);
    
  }
  
  int picked_result = cost[root] + not_covered;
  int covered_result = std::min(picked_result, covered + min_diff_covered);
  int not_covered_result = std::min(picked_result, covered);

  return {picked_result, covered_result, not_covered_result};
}

void testcase() {
  
  int n; std::cin >> n;
  
  std::vector<std::vector<int>> tree(n);
  std::vector<int> cost(n, 0);
  
  for(int i=0; i<n-1; i++) {
    int u, v; std::cin >> u >> v;
    tree[u].push_back(v);
  }
  
  for(int i=0; i<n; i++) std::cin >> cost[i];
  
  subtree t = dfs(0, tree, cost);
  
  std::cout << t.covered << std::endl;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  int t; std::cin >> t;
  while(t--) testcase();
}
