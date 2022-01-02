#include <bits/stdc++.h>

using namespace std;

typedef vector<vector<vector<int>>> TRIMAT;

int f(vector<int> &v, TRIMAT &memo, int left, int right, bool turn){
  if(left > right)
    return 0;
  
  if(memo[turn][left][right] != -1) return memo[turn][left][right];
  int res = 0;
  if(turn)
    res = max(v[left]+f(v, memo, left+1, right, false), v[right]+f(v, memo, left, right-1, false));
  else
    res = min(f(v, memo, left+1, right, true), f(v, memo, left, right-1, true));  //worst possible assumption for friend's move
  
  memo[turn][left][right] = res;
  return res;
}

void testcase(){
  int n; cin >> n;
  vector<int> v;
  
  int vi;
  for(int i = 0; i < n; i++){
    cin >> vi;
    v.push_back(vi);
  }
  
  TRIMAT memo(2, vector<vector<int>>(n, vector<int>(n, -1)));
  int res = f(v, memo, 0, n-1, true);
  
  cout << res << endl;
}

int main(){
  ios_base::sync_with_stdio(false);
  int t; cin >> t;
  for(int i = 0; i < t; i++)  
    testcase();
  
  return 0;
}