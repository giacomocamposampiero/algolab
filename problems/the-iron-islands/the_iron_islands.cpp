#include <iostream>
#include <vector>
#include <unordered_map>

int max_islands(std::vector<int> &path, int k) {
  int i = 0, j = 1, size = path.size();
  int max = 0;
  while(j<size) {
    while(j<size && (path[j] - path[i] < k)) j++;
    if(path[j] - path[i] == k) max = std::max(max, j-i);
    i++;
  }
  return max;
}

void testcase() {
  
  int n, k, w; std::cin >> n >> k >> w;
  
  std::vector<int> c(n, 0);
  for(int i=0; i<n; i++) std::cin >> c[i];
  
  std::vector<std::vector<int>> waterway(w, std::vector<int>(1, 0));
  for(int i=0; i<w; i++) {
    int l, sum=0; std::cin >> l;
    while(l--) {
      int r; std::cin >> r;
      sum += c[r];
      waterway[i].push_back(sum);
    }
  }
  
  int max = 0;
  for(size_t pa=0; pa<waterway.size(); pa++) 
  max = std::max(max, max_islands(waterway[pa], k));
  
  int pyke = c[0];
  std::unordered_map<int,int> complem;
  
  for(int i = 0; i < w; i++) {
    
    for(int j = 2; j < (int) waterway[i].size(); j++){
      
      if(waterway[i][j] >= k) break;
      
      int diff = k - waterway[i][j] + pyke;
      
      if(complem.find(diff) != complem.end())
        max = std::max(max, j + complem[diff] );
    }
    
    for(int j = 2; j < (int) waterway[i].size(); j++){
      
      if(waterway[i][j] >= k) break;
      
      if(complem.find(waterway[i][j]) == complem.end())
        complem[waterway[i][j]] = j-1;
      else
        complem[waterway[i][j]] = std::max(complem[waterway[i][j]], j-1);
    }
  }
  
  /*  
  for(int i=0; i<w; i++) {
    for(int j=i+1; j<w; j++) {
      int left = 1, right = 2, sum = 0;
      
      while(left < (int) waterway[i].size()-1 && waterway[i][left] < k) left++;
      
      while(left > 1) {
        sum = waterway[i][left];
       
        while(right < (int) waterway[j].size()-1 && (waterway[j][right]+sum-pyke) < k) right++;
        sum += waterway[j][right] - pyke;
        if(sum == k) max = std::max(max, left+right-1);
        left--;
      }
    }
  }*/
 
  std::cout << max << std::endl;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  int t; std::cin >> t;
  while(t--) testcase();
}
