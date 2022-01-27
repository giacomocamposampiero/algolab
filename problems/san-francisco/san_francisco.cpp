#include <vector>
#include <iostream>

typedef std::pair<int,long> edge;

long max_score(std::vector<std::vector<long>> &memo, std::vector<std::vector<edge>> &adj, int start, int remaining, long score) {
    
  if(remaining == 0) return 0;
  if(memo[start][remaining] != -1) return memo[start][remaining];
  
  long curr = 0;
  int descendant = adj[start].size();
  
  for(int i=0; i<descendant; i++)
    curr = std::max(curr, adj[start][i].second + max_score(memo, adj, adj[start][i].first, remaining-1, score + adj[start][i].second));
  
  if(descendant == 0) curr = max_score(memo, adj, 0, remaining, score);
  memo[start][remaining] = curr;

  return memo[start][remaining];
}

void testcase() {
  
  long n, m, x, k; std::cin >> n >> m >> x >> k;
  
  std::vector<std::vector<edge>> adj(n);
  std::vector<std::vector<long>> memo(n, std::vector<long>(k+1, -1));
  
  for(int i=0; i<m; i++) {
    long u, v, p; std::cin >> u >> v >> p;
    adj[u].push_back(edge(v, p));
  }
  
  int left = 1, right = k, min = k+1;
  while(left <= right) {
    int mid = left + (right-left)/2;
    long maxs = max_score(memo, adj, 0, mid, 0);
    if(maxs >= x) { right = mid - 1; min = mid; }
    else left = mid + 1;
  }
  
  if(min <= k) std::cout << min << std::endl;
  else std::cout << "Impossible" << std::endl;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  int t; std::cin >> t;
  while(t--) testcase();
}
