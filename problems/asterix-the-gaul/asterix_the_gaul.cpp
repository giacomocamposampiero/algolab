#include <iostream>
#include <vector>
#include <algorithm>

long T; long D;

bool find_paths(std::vector<std::pair<long,long>> &mov, int i, long pot, long t, long d) {
  if(i == (int) mov.size()) return false;
  
  int curr_t = mov[i].first, curr_d = mov[i].second + pot;
  if(curr_t + t >= T) return false;  // time exceeded, discard path
  if(curr_d + d >= D) return true;   // distance achieved before end of time
  
  return find_paths(mov, i+1, pot, t, d) || find_paths(mov, i+1, pot, t+curr_t, d+curr_d);
}

void testcase() {

  int n; std::cin >> n;
  int m; std::cin >> m;
  std::cin >> D; std::cin >> T;
  std::vector<std::pair<long,long>> movements;
  std::vector<long> gulps(++m, 0);
  
  for(int i=0; i<n; i++) {
    long d; std::cin >> d;
    long t; std::cin >> t;
    movements.push_back(std::make_pair(t,d));
  }
  std::sort(movements.begin(), movements.end());
  for(int i=1; i<m; i++) std::cin >> gulps[i];
  
  
  int left = 0, right = m-1, i, best = m+1;
  
  while(left <= right) {
    i = (left+right)/2;
    bool panoramix = find_paths(movements, 0, gulps[i], 0, 0);
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
