#include <bits/stdc++.h>

using namespace std;

typedef pair<int,int> PI;
typedef vector<vector<vector<PI>>> TRIMAT;

PI f(vector<PI> &bev, TRIMAT &memo, int start, int n, int vol, int k, bool distinct){
  if(vol >= k)
    return PI(0,0);
    
  if(start >= n)
    return PI(numeric_limits<int>::max(), 0);
  
  if(memo[distinct][start][vol] != PI(numeric_limits<int>::max(), -1))  return memo[distinct][start][vol];
  PI res;
  PI take_it = f(bev, memo, start, n, vol+bev[start].second, k, false);
  take_it.first += bev[start].first;
  if(distinct)  take_it.second++;
  
  PI dont = f(bev, memo, start+1, n, vol, k, true);
  
  if(take_it.first < dont.first)
    res = take_it;
  else if(take_it.first == dont.first && take_it.second > dont.second)
    res = take_it;
  else
    res = dont;
  
  memo[distinct][start][vol] = res;
  return res;
}

void testcase(){
  int n; cin >> n;
  int k; cin >> k;
  
  vector<PI> bev;
  int c, v;
  for(int i = 0; i < n; i++){
    cin >> c >> v;
    bev.push_back(PI(c,v));
  }
  
  TRIMAT memo(2, vector<vector<PI>>(n, vector<PI>(k, PI(numeric_limits<int>::max(), -1))));
  
  PI res = f(bev, memo, 0, n, 0, k, true);
  
  cout << res.first << " " << res.second << endl;
}

int main(){
  ios_base::sync_with_stdio(false);
  int t; cin >> t;
  for(int i = 0; i < t; i++)
    testcase();

  return 0;
}