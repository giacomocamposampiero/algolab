#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

struct species {
  std::vector<species*> offsprings;
  std::string name;
  int age;
};

struct query {
  std::string name;
  std::string result;
  int id;
  int max_age;
};


void dfs(species &node, std::vector<query> &queries, std::vector<species> &vec) {
  
  vec.push_back(node);
  
  // check queries for the current node
  auto p = std::equal_range(queries.begin(), queries.end(), node, [](const auto a, const auto b) {
    return (a.name).compare(b.name) < 0;
  });
  
  for(auto i = p.first; i != p.second; ++i) {
    
    int target = i -> max_age;
    int l = -1, r = vec.size()-1;
    
    while(l + 1 < r) {
      int m = (l + r)/2;
      if(vec[m].age <= target) r = m;
      else l = m;
    }
    
    i -> result = vec[r].name;
  }

  // DFS on node children
  for(int i=0; i<(int)node.offsprings.size(); i++)
    dfs(*node.offsprings[i], queries, vec);
  
  vec.pop_back();
}

void testcase() {
  
  int n, q; std::cin >> n >> q;
  
  std::vector<species> tree_of_life(n);
  for(int i=0; i<n; i++) {
    std::cin >> tree_of_life[i].name >> tree_of_life[i].age;
  }
  
  std::sort(tree_of_life.begin(), tree_of_life.end(), [](const auto a, const auto b) {
    return (a.name).compare(b.name) < 0;
  });
  
  for(int i=0; i<n-1; i++) {
    std::string anchestor, offspring; std::cin >> offspring >> anchestor;
    auto a_pt = std::lower_bound(tree_of_life.begin(), tree_of_life.end(), anchestor, [](const auto a, const auto b) {
      return (a.name).compare(b) < 0;
    });
  
    auto o_pt = std::lower_bound(tree_of_life.begin(), tree_of_life.end(), offspring, [](const auto a, const auto b) {
      return (a.name).compare(b) < 0;
    });
    (a_pt -> offsprings).push_back(&(*o_pt));
  }
  
  int root = std::max_element(tree_of_life.begin(), tree_of_life.end(), [](const auto a, const auto b) {
    return a.age < b.age;
  }) - tree_of_life.begin();
  
  std::vector<query> queries(q);
  for(int i=0; i<q; i++) {
    std::cin >> queries[i].name >> queries[i].max_age;
    queries[i].id = i;
  }
  
  
  std::sort(queries.begin(), queries.end(), [](const auto a, const auto b) {
    return (a.name).compare(b.name) < 0;
  });
  
  std::vector<species> tmp;
  dfs(tree_of_life[root], queries, tmp);
  
  std::sort(queries.begin(), queries.end(), [](const auto a, const auto b) {
    return a.id < b.id;
  });
  
  for(int i=0; i<q; i++) std::cout << queries[i].result << ' ';
  std::cout << std::endl;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  int t; std::cin >> t;
  while(t--) testcase();
}
