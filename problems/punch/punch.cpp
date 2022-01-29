///
#include <iostream>
#include <vector>
#include <limits>

typedef std::pair<int,int> PI;
typedef std::vector<PI> VPI;
typedef std::vector<std::vector<PI>> VVPI;
typedef std::vector<std::vector<std::vector<PI>>> VVVPI;

const int MAX_COST = 10000*10000;

int n, k; 

PI find_cost(VVVPI &memo, VPI &bvs, int index, int volume, bool diff) {

  if(volume >= k) return {0,0};
  if(index == n) return {MAX_COST, 0};
  
  if(memo[diff][index][volume].first != -1) return memo[diff][index][volume];
  
  auto stay = find_cost(memo, bvs, index, volume + bvs[index].second, false);
  auto proceed = find_cost(memo, bvs, index+1, volume, true);
  
  if(diff) stay.second++;
  stay.first += bvs[index].first; 
  
  PI res;
  if(stay.first < proceed.first) res = stay;
  else if(stay.first == proceed.first) {
    if(stay.second > proceed.second) res = stay;
    else res = proceed;
  }
  else res = proceed;
  
  memo[diff][index][volume] = res;
  return memo[diff][index][volume];
}

void testcase() {
  
  std::cin >> n >> k;
  
  VPI bvs(n);
  for(int i=0; i<n; i++) std::cin >> bvs[i].first >> bvs[i].second;
  
  VVVPI memo(2, VVPI(n, VPI(k, {-1, -1})));
  
  PI best = find_cost(memo, bvs, 0, 0, true);
  
  std::cout << best.first << ' ' << best.second << std::endl;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  int t; std::cin >> t;
  while(t--) testcase();
}
