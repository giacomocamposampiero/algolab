#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

void insert(std::vector<int> &v, std::vector<int> &positions, int i, int j) {
  if((v[j-1]-v[i])%2==0) positions.push_back((v[j-1]-v[i])/2+v[i]);
  else {
    positions.push_back(std::floor((v[j-1]-v[i])/2.0)+v[i]);
    positions.push_back(std::ceil((v[j-1]-v[i])/2.0)+v[i]);
  }
}

void testcase() {
  int n; std::cin >> n;
  std::vector<int> v(n);
  
  for(int i=0; i<n; i++)
    std::cin >> v[i];
  
  // Nlog(N)
  std::sort(v.begin(), v.end());
  


  int i=0, j=0;
  int maxp = 0;
  int maxd = 0;
  std::vector<int> results;
  
  
  while(j<n) {
    
    // find interval coordinates
    while((std::abs(v[j]-v[i])<=200) && j<n) {j++;}
    
    int nump = j-i, mdist = std::ceil((v[j-1]-v[i])/2.0);
    if(nump > maxp || (nump==maxp && mdist < maxd)) {
      // new solution found, empty the array
      results.clear();
      // update max parasols and max distance in the interval
      maxp = nump;
      maxd = mdist;
      insert(v, results, i, j);
    } else if(nump==maxp && mdist==maxd) {
      insert(v, results, i, j);
    }
    i++;
  }
  
  // output
  std::cout << maxp << ' ' << maxd << std::endl;
  for(auto x : results) std::cout << x << ' ';
  std::cout << std::endl;
}

int main() {
  int t; std::cin >> t;
  for(int i=0; i<t; i++) testcase();
}
