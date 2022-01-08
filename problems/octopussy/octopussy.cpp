#include <iostream>
#include <vector>
#include <queue>

void testcase() {
  
  int n; std::cin >> n;
  
  std::vector<int> bomb(n, 0);
  for(int i=0; i<n; i++) std::cin >> bomb[i];
  
  auto cmp = [](const auto left, const auto right) { return left.second < right.second;};
  std::priority_queue<std::pair<int,int>, std::vector<std::pair<int,int>>, decltype(cmp)> queue(cmp);
  queue.push(std::make_pair(0, bomb[0]));
  
  for(int i=n; i>0; i--) {
    
    std::pair<int,int> curr = queue.top();
    queue.pop();

    if(curr.second < i) {
      std::cout << "no" << std::endl;
      return;
    }
    
    if(curr.first < (n-1)/2) {
      queue.push(std::make_pair(2*curr.first+1, bomb[2*curr.first+1]));
      queue.push(std::make_pair(2*curr.first+2, bomb[2*curr.first+2]));
    }

  }
  
  std::cout << "yes" << std::endl;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  int t; std::cin >> t;
  while(t--) testcase();
}
