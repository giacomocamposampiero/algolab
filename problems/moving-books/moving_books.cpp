#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

void testcase() {
  
  int n, m; std::cin >> n >> m;
  std::multiset<int> w;
  std::vector<int> s(n, 0);
  
  for(int i=0; i<n; i++) std::cin >> s[i];
  for(int i=0; i<m; i++) { int tmp; std::cin >> tmp; w.insert(tmp); }
  
  std::sort(s.begin(), s.end());
  
  int min = -1;
  int limit = 0; 
  while(!w.empty()) {

    if(limit == n) {
      std::cout << "impossible" << std::endl;
      return;
    }
    
    for(int i=limit; i<n; i++) {
      auto pack = w.upper_bound(s[i]);
      if(pack == w.begin()) limit++;
      else {
        pack--;
        w.erase(pack);
      }
    }
    min += 3;
  }
  
  std::cout << min << std::endl;
  
}

int main() {
  std::ios_base::sync_with_stdio(false);
  int t; std::cin >> t;
  while(t--) testcase();
}
