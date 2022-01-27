#include <vector>
#include <iostream>
#include <stack>
#include <algorithm>
#include <functional>

struct chamber {
  long galleons;
  long length;
  double subtree_t;
  double subtree_n;
  std::vector<chamber*> descendants;
};

int n;

std::pair<long,long> precomputation(chamber &c) {

  std::pair<long,long> sub = {c.length,1};

  for(size_t i=0; i<c.descendants.size(); i++) {
    auto x = precomputation(*(c.descendants[i]));
    sub.first += x.first;
    sub.second += x.second;
  }
  
  std::sort(c.descendants.begin(), c.descendants.end(), [](const auto a, const auto b) {
    return ((*a).subtree_t / (*a).subtree_n) < ((*b).subtree_t / (*b).subtree_n);
  });
  
  c.subtree_t = sub.first;
  c.subtree_n = sub.second;
  return sub;
  
}

long visit(chamber &c, long *timing) {
  
  (*timing) += c.length;
  long gall = c.galleons - (*timing);
  
  std::vector<chamber> to_visit;

  for(size_t i=0; i<c.descendants.size(); i++) gall += visit(*(c.descendants[i]), timing);
  
  *timing += c.length;
  return gall;
  
}

void testcase() {
  
  std::cin >> n;
  
  std::vector<chamber> cs(n+1);
  for(int i=1; i<=n; i++) 
    std::cin >> cs[i].galleons;
  
  for(int i=1; i<=n; i++) {
    int u, v, l; std::cin >> u >> v >> l;
    cs[u].descendants.push_back(&cs[v]);
    cs[v].length = l;
  }
  
  precomputation(cs[0]);

  long t = 0;
  long gold = visit(cs[0], &t);
  
  std::cout << gold << std::endl;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  int t; std::cin >> t;
  while(t--) testcase();
}
