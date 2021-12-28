#include <vector>
#include <iostream>
#include <stack>
#include <algorithm>
#include <functional>

int sium_subtree(int index, std::vector<std::vector<std::pair<int,int>>> &adj, std::vector<long> &sum) {
  if(adj[index].empty()) return 0;
  int subtree = 0;
  for(int i=0, size=adj[index].size(); i<size; i++) {
    sum[adj[index][i].first] = sium_subtree(adj[index][i].first, adj, sum) + adj[index][i].second;
    subtree += sum[adj[index][i].first];
  }
  return subtree;
}

void testcase() {
  
  int n; std::cin >> n;
  
  std::vector<int> gold = std::vector<int>(n+1, 0);
  for(int i=1; i<=n; i++) std::cin >> gold[i];
  
  std::vector<std::vector<std::pair<int,int>>> adjacency = std::vector<std::vector<std::pair<int,int>>>(n+1);

  for(int i=0; i<n; i++) {
    int u, v, l; std::cin >> u >> v >> l;
    adjacency[u].push_back(std::make_pair(v, l)); 
  }
  
  std::vector<long> subtrees = std::vector<long>(n+1, 0);
  sium_subtree(0, adjacency, subtrees);
  
  std::stack<std::pair<int,int>> stack = std::stack<std::pair<int,int>>();
  long count = 0, galleons = 0;
  stack.push(std::make_pair(0,0));

  while(!stack.empty()) {
    std::pair<int,int> current = stack.top();
    
    if(gold[current.first] > 0) {
      count += current.second; 
      galleons += gold[current.first] - count;
      gold[current.first] = 0;
    }

    std::vector<std::pair<int,int>> children = adjacency[current.first];
    
    if(children.size() > 0) {
      std::sort(children.begin(), children.end(), [&subtrees](std::pair<int,int> a, std::pair<int,int> b) {
        return subtrees[a.first] > subtrees[b.first];
      });
      for(auto x : children) stack.push(x);
      adjacency[current.first].clear();
    } else {
      count += current.second;
      stack.pop();
    }
    
  }
  
  std::cout << galleons << std::endl;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  int t; std::cin >> t;
  for(int i=0; i<t; i++) testcase();
}
