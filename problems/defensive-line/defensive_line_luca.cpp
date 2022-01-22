#include <bits/stdc++.h>

using namespace std;

typedef vector<vector<int>> MAT;

int f(vector<int> &starting, MAT &memo, int m, int start, int n){
  if(m == 0)
    return 0;
  
  if(start >= n){
    return -numeric_limits<int>::max();
  }
  
  if(memo[start][m] != -1)  return memo[start][m];
  int res = -1;
  if(starting[start] == -1)
    res = f(starting, memo, m, start+1, n);
  else
    res = max(starting[start]+f(starting, memo, m-1, start+starting[start], n), f(starting, memo, m, start+1, n));
  
  memo[start][m] = res;
  return res;
}

void testcase(){
  int n; cin >> n;
  int m; cin >> m;
  int k; cin >> k;
  
  vector<int> defense;
  int v;
  for(int i = 0; i < n; i++){
    cin >> v;
    defense.push_back(v);
  }
  
  vector<int> starting(n, -1);
  int i = 0, j = 0;
  int val = defense[0];
  while(j < n){
    if(val == k){
      starting.at(i) = j-i+1;
      j++;
      if(j == n)  break;
      val += defense[j];
    }
    
    else if(val < k){
      j++;
      if (j == n) break;
      val += defense[j];
    } 
    
    else{
      val -= defense[i];
      i++;
      if(i > j) {
        if(i == n) break;
        j = i;
        val = defense[i];
      }
    }
  }
  
  MAT memo(n, vector<int>(m+1, -1));
  
  int res = f(starting, memo, m, 0, n);
  
  if(res < 0)
    cout << "fail" << endl;
  else
    cout << res << endl;
}

int main(){
  ios_base::sync_with_stdio(false);
  int t; cin >> t;
  for(int i = 0; i < t; i++)
    testcase();
  
  return 0;
}