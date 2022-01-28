#include <boost/pending/disjoint_sets.hpp>
#include <vector>
#include <tuple>
#include <algorithm>
#include <iostream>

typedef std::tuple<int,int,long> Edge;
typedef std::vector<Edge> EdgeV;

void testcase() {
  
  int n, i; std::cin >> n >> i;
  
  std::vector<std::vector<int>> cost(n-1);
  for(int j=0; j<n-1; j++) {
    for(int k=0; k<n-j-1; k++) {
      int c; std::cin >> c;
      cost[j].push_back(c);
    }
  }
  
  EdgeV edges;
  for(int j=0; j<n-1; j++) {
    for(int k=1; k<n-j; k++) {
      int i1 = j;
      int i2 = j+k;
      edges.emplace_back(i1, i2, cost[j][k-1]);
      edges.emplace_back(i2, i1, cost[j][k-1]);
    }
  }

  std::sort(edges.begin(), edges.end(), [](const Edge& e1, const Edge& e2) -> bool {
    return std::get<2>(e1) < std::get<2>(e2);
  });

  boost::disjoint_sets_with_storage<> uf(n);
  int n_components = n;

  EdgeV spanning;
  for (EdgeV::const_iterator e = edges.begin(); e != edges.end(); ++e) {

    int c1 = uf.find_set(std::get<0>(*e));
    int c2 = uf.find_set(std::get<1>(*e));
    if (c1 != c2) {
      uf.link(c1, c2);
      spanning.emplace_back(*e);
      if (--n_components == 1) break;
    }
  }
  
  long min_cost = std::numeric_limits<long>::max();
  for(size_t i=0; i<spanning.size(); i++) {
    
    boost::disjoint_sets_with_storage<> uft(n);
    int n_components = n;
    
    long cost = 0;
    for (EdgeV::const_iterator e = edges.begin(); e != edges.end(); ++e) {
      if((std::get<0>(*e) != std::get<0>(spanning[i]) || std::get<1>(*e) != std::get<1>(spanning[i])) &&
         (std::get<0>(*e) != std::get<1>(spanning[i]) || std::get<1>(*e) != std::get<0>(spanning[i])) ) {
        int c1 = uft.find_set(std::get<0>(*e));
        int c2 = uft.find_set(std::get<1>(*e));
        if (c1 != c2) {
          uft.link(c1, c2);
          cost += std::get<2>(*e);
          if (--n_components == 1) break;
        }
      }
    }
    min_cost = std::min(min_cost, cost);
  }
  
  std::cout << min_cost << std::endl;

}

int main() {
  std::ios_base::sync_with_stdio(false);
  int t; std::cin >> t;
  while(t--) testcase();
}
