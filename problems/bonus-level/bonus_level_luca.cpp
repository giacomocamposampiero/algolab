#include <bits/stdc++.h>

using namespace std;

typedef vector<vector<int>> MAT;
typedef vector<vector<vector<int>>> TRIMAT;

int f(MAT &coins, TRIMAT &memo, int i1, int i2, int diag, int n){
  int j1 = diag-i1;
  int j2 = diag-i2;
  if(i1 == n-1 && j1 == n-1 && i2 == n-1 && j2 == n-1)
    return coins[i1][j1];
  
  if(memo[i1][i2][diag] != -1)  return memo[i1][i2][diag];
  
  int tmp  = coins[i1][j1];
  //I pick it
  coins[i1][j1] = 0;
  int res1 = -1, res2 = -1, res3 = -1, res4 = -1;
  if(i1 < n-1 && i2 < n-1)
    res1 = tmp + f(coins, memo, i1+1, i2+1, diag+1, n);
  if(i1 < n-1 && j2 < n-1)
    res2 = tmp + f(coins, memo, i1+1, i2, diag+1, n);
  if(i2 < n-1 && j1 < n-1)
    res3 = tmp + f(coins, memo, i1, i2+1, diag+1, n);
  if(j1 < n-1 && j2 < n-1)
    res4 = tmp + f(coins, memo, i1, i2, diag+1, n);
  
  int res = coins[i2][j2] + max(max(res1, res2), max(res3, res4));
  //backtrack
  coins[i1][j1] = tmp;
  
  memo[i1][i2][diag] = res;
  return res;
}

void testcase(){
  int n; cin >> n;
  
  MAT coins(n, vector<int>(n));
  int a;
  for(int i = 0; i < n; i++){
    for(int j = 0; j < n; j++){
      cin >> a;
      coins[i][j] = a;
    }
  }
  
  TRIMAT memo(n, MAT(n, vector<int>(2*n-1, -1)));
  int res = f(coins, memo, 0, 0, 0, n);
  
  cout << res << endl;
}

int main(){
  ios_base::sync_with_stdio(false);
  int t; cin >> t;
  for(int i = 0; i < t; i++)
    testcase();
  
  return 0;
}