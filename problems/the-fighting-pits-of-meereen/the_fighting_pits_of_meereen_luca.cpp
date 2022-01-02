#include <bits/stdc++.h>

using namespace std;

typedef tuple<int,int,int,int,int,int,int> TI;

int excitement(int curr, int last, int seclast, int north, int south, int m){
  set<int> distinct;
  distinct.insert(curr);
  if(last != -1)
    distinct.insert(last);
  if(seclast != -1 && m == 3)
    distinct.insert(seclast);
  
  return 1000*(int)distinct.size() - pow(2, abs(north-south));
}

int f(vector<int> &fighters, map<TI,int> &memo, int north, int south, int lastn, int seclastn, int lasts, int seclasts, int start, int n, int m){
  if(start >= n)
    return 0;
  
  TI tup(start, north, south, lastn, seclastn, lasts, seclasts);
  if(memo.find(tup) != memo.end())  return memo[tup];
  
  int res = -1, res1 = -1, res2 = -1;
  int exc1 = excitement(fighters[start], lastn, seclastn, north+1, south, m);
  if(exc1 >= 0)
    res1 = exc1+f(fighters, memo, north+1, south, fighters[start], lastn, lasts, seclasts, start+1, n, m);
  
  int exc2 = excitement(fighters[start], lasts, seclasts, north, south+1, m);
  if(exc2 >= 0)
    res2 = exc2+f(fighters, memo, north, south+1, lastn, seclastn, fighters[start], lasts, start+1, n, m);
  
  res = max(res1, res2);
  memo[tup] = res;
  return res;
}

void testcase(){
  int n; cin >> n;
  int k; cin >> k;
  int m; cin >> m;
  
  vector<int> fighters;
  
  int x;
  for(int i = 0; i < n; i++){
    cin >> x;
    fighters.push_back(x);
  }
  
  map<TI,int> memo;
  int res = f(fighters, memo, 0, 0, -1, -1, -1, -1, 0, n, m);
  
  cout << res << endl;
}

int main(){
  ios_base::sync_with_stdio(false);
  int t; cin >> t;
  for(int i = 0; i < t; i++)
    testcase();
  
  return 0;
}