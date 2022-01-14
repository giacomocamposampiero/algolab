///3
#include <iostream>
#include <vector>
#include <algorithm>

long T; long D;
typedef std::vector<std::pair<long,long>> TD;

bool find_paths(TD &mov, TD &list, int i, long pot, long t, long d) {
  
  if(i == (int) mov.size()) return false;
  
  int curr_t = mov[i].first, curr_d = mov[i].second + pot;
  list.push_back(std::make_pair(curr_t + t, curr_d + d));
  
  if(curr_t + t >= T) return false;  // time exceeded, discard path
  if(curr_d + d >= D) return true;   // distance achieved before end of time
  
  return find_paths(mov, list, i+1, pot, t, d) || find_paths(mov, list, i+1, pot, t+curr_t, d+curr_d);
}


bool split_and_list(TD &mov, int i, long pot, long t, long d) {
  
  // split the set in half
  TD S1, S2;
  for(std::size_t i = 0; i < mov.size(); i++){
    if(i%2 == 0) S1.push_back(mov[i]);
    else S2.push_back(mov[i]);
  }
  
  // list
  TD L1, L2;
  if(find_paths(S1, L1, 0, pot, 0, 0)) return true;
  if(find_paths(S2, L2, 0, pot, 0, 0)) return true;
  
  // sort L2 with respect to time so that I...
  std::sort(L2.begin(), L2.end());
  
  // ...store the best distance found for t <= t_i
  long best = -1;
  std::vector<long> bestdist;
  for(int i = 0; i < (int) L2.size(); i++){
    if(L2[i].second > best)  best = L2[i].second;
    bestdist.push_back(best);
  }
  
  for(int i = 0; i < (int) L1.size(); i++) {
    
    long d1 = L1[i].second;
    long t1 = L1[i].first;
    
    int left = 0, right = (int)L2.size()-1;
    
    while(left <= right){
      int mid = (left+right)/2;
      if(t1 + L2[mid].first < T){
        if(d1 + bestdist[mid] >= D) return true;
        left = mid+1;
      }
      else right = mid-1;
    }
  }
  return false; 
}


void testcase() {

  int n; std::cin >> n;
  int m; std::cin >> m;
  std::cin >> D; std::cin >> T;
  TD movements;
  std::vector<long> gulps(++m, 0);
  
  for(int i=0; i<n; i++) {
    long d; std::cin >> d;
    long t; std::cin >> t;
    movements.push_back(std::make_pair(t,d));
  }
  std::sort(movements.begin(), movements.end());
  for(int i=1; i<m; i++) std::cin >> gulps[i];
  
  // try first to reach the target with 0 gulps
  bool panoramix = split_and_list(movements, 0, 0, 0, 0);
  if(panoramix) {
    std::cout << 0 << std::endl;
    return;
  }
  
  int left = 0, right = m-1, i, best = m+1;
  
  while(left <= right) {
    i = (left+right)/2;
    bool panoramix = split_and_list(movements, 0, gulps[i], 0, 0);
    if(panoramix) {best = i; right = i - 1;}
    else left = i + 1;
  }  
  
  if(best != m+1) std::cout << best << std::endl;
  else std::cout << "Panoramix captured" << std::endl;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  int t; std::cin >> t;
  for(int i=0; i<t; i++) testcase();
}
