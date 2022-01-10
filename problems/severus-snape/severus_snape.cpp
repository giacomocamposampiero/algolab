#include <vector>
#include <iostream>
#include <algorithm>

long n, m, H; 
long P, W, a, b; 

long severus(std::vector<std::vector<std::vector<long>>> &memo, std::vector<std::pair<long,long>> &pot, int start, int to_pick, long happiness) {
  
  if(happiness <= 0) happiness = 0;
  if(to_pick <= 0) {
    if(happiness == 0) return 0;
    return -std::numeric_limits<long>::max();
  }
  if(start >= n) return -std::numeric_limits<long>::max();

  if(memo[start][to_pick][happiness] != -1) return memo[start][to_pick][happiness];
  
  long take = pot[start].first + severus(memo, pot, start+1, to_pick-1, happiness-pot[start].second);
  long leave = severus(memo, pot, start+1, to_pick, happiness);
  
  long power = std::max(take, leave);
  
  memo[start][to_pick][happiness] = power;
  return power;

}

int evaluate(std::vector<std::vector<std::vector<long>>> &memo, std::vector<std::pair<long,long>> &potA, std::vector<long> &potB, int end) {
  
  int nb = 0, na = std::numeric_limits<int>::max();
  long w = 0;
  
  while(nb < end) w += potB[nb++];
  
  for(int to_pick = 1; to_pick <= n; to_pick++){
    long res = severus(memo, potA, 0, to_pick, H);
    if(res >= P + nb*b) { na = to_pick; break; }
  }
  
  if(w- na*a >= W && na < std::numeric_limits<int>::max())
    return na+nb;
  
  return std::numeric_limits<int>::max();
}

void testcase() {
  
  std::cin >> n >> m >> a >> b >> P >> H >> W;
  
  std::vector<std::pair<long,long>> potA;
  std::vector<long> potB(m, 0);
  
  for(int i=0; i<n; i++) {
    long p, h; std::cin >> p >> h;
    potA.push_back(std::make_pair(p, h));
  }
  for(int i=0; i<m; i++) std::cin >> potB[i];
  
  std::vector<std::vector<std::vector<long>>> memo(n, std::vector<std::vector<long>>(n+1, std::vector<long>(H+1, -1)));
  std::sort(potB.begin(), potB.end(), std::greater<long>());
  
  int left = 0, right = m;
  int mid = m;
  int minval = std::numeric_limits<int>::max();
  while(left <= right){
    int res = evaluate(memo, potA, potB, mid);
    if(res <= minval) {
      right = mid-1;
      minval = res;
    }
    else left = mid+1;
    mid = (left+right)/2;
  }
  
  if(minval == std::numeric_limits<int>::max())
    std::cout << -1 << std::endl;
  else
    std::cout << minval << std::endl;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  int t; std::cin >> t;
  while(t--) testcase();
}
