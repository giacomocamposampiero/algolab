#include <iostream>
#include <vector>
#include <algorithm>

void testcase() {
  
  int n; std::cin >> n;
  std::vector<std::pair<int,int>> boats;
  
  for(int i=0; i<n; i++) {
    int l, p; std::cin >> l >> p;
    boats.push_back(std::make_pair(p, l));
  }
  std::sort(boats.begin(), boats.end());
  
  int last = -1e7, last_length = 1e7, b = 0;
  
  for(int i=0; i<n; i++) {
    int p = boats[i].first, l = boats[i].second;
    int start = std::max(p-l, last);
  
    if(start <= p) {
      last = start + l;
      last_length = l;
      b++;
    } else {
      int start_wt = std::max(p-l, last-last_length);
      if(last > start_wt + l) {
        last = start_wt + l;
        last_length = l;
      }
    }
    
  }
  
  std::cout << b << std::endl;
  
}

int main() {
  std::ios_base::sync_with_stdio(false);
  int t; std::cin >> t;
  while(t--) testcase();
}
