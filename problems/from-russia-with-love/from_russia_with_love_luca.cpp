#include <iostream>
#include <vector>

using namespace std;

typedef vector<vector<int>> MAT;

int f(MAT &memok, MAT &memoNk, vector<int> &x, int turn, int k, int l, int r, int m){
  if(l > r)
    return 0;
    
  turn = turn % m;
  
  if(turn != k && memoNk[l][r] != -1) return memoNk[l][r];
  
  if(turn == k && memok[l][r] != -1)  return memok[l][r];
  
  int res = -1;
  if(turn != k){
    res = min(f(memok, memoNk, x, turn+1, k, l+1, r, m), f(memok, memoNk, x, turn+1, k, l, r-1, m));
  }
  
  else{
    res = max(x.at(l) + f(memok, memoNk, x, turn+1, k, l+1, r, m), x.at(r) + f(memok, memoNk, x, turn+1, k, l, r-1, m));
  }
  
  if(turn != k)
    memoNk[l][r] = res;
  
  if(turn == k)
    memok[l][r] = res;
    
  return res;
}

void testcase(){
  int n; cin >> n;
  int m; cin >> m;
  int k; cin >> k;
  vector<int> x;
  MAT memok(n, vector<int>(n,-1)), memoNk(n, vector<int>(n, -1));
  
  for(int i = 0; i < n; i++){
    int a; cin >> a;
    x.push_back(a);
  }
  
  int tot = f(memok, memoNk, x, 0, k, 0, n-1, m);
  
  cout << tot << endl;
  
}

int main(){
  ios_base::sync_with_stdio(false);
  int t; cin >> t;
  for(int i = 0; i < t; i++)
    testcase();
    
  return 0;
}