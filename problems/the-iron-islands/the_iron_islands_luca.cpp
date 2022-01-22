#include <bits/stdc++.h>

using namespace std;

int sliding_window(vector<int> &men, vector<int> &v, int k){
  int size = (int)v.size();
  int i = 0, j = 0;
  int val = men[v[0]];
  int maxcount = 0;
  
  while(j < size){
    if(val == k){
      maxcount = max(maxcount, j-i+1);
      j++;
      if(j == size) break;
      val += men[v[j]];
    }
    else if(val < k){
      j++;
      if(j == size)  break;
      val += men[v[j]];
    }
    else{
      val -= men[v[i]];
      i++;
      if(i > j){
        if(i == size)  break;
        j = i;
        val = men[v[i]];
      }
    }
  }
  
  return maxcount;
}

void testcase(){
  int n, k, w;
  cin >> n >> k >> w;
  
  vector<int> men;
  int c;
  for(int i = 0; i < n; i++){
    cin >> c;
    men.push_back(c);
  }
  
  vector<vector<int>> waterway(w, vector<int>());
  int l, r;
  int maxcount = 0;
  for(int i = 0; i < w; i++){
    cin >> l;
    for(int j = 0; j < l; j++){
      cin >> r;
      waterway[i].push_back(r);
    }
    maxcount = max(maxcount, sliding_window(men, waterway[i], k));
  }
  
  int pyke = men[0];
  map<int,int> complem; //sum, number of islands
  for(int i = 0; i < w; i++){
    int sum = 0;
    vector<int> pref_sum;
    for(int j = 1; j < (int)waterway[i].size(); j++){
      sum += men[waterway[i][j]];
      pref_sum.push_back(sum);
      
      if(sum + pyke >= k)
        break;
      
      int diff = k - sum - pyke;
      if(complem.find(diff) != complem.end())
        maxcount = max(maxcount, j + complem[diff] + 1);
    }
    
    for(int j = 0; j < (int)pref_sum.size(); j++){
      if(complem.find(pref_sum[j]) == complem.end())
        complem[pref_sum[j]] = j+1;
      else
        complem[pref_sum[j]] = max(complem[pref_sum[j]], j+1);
    }
  }
  
  cout << maxcount << endl;
}

int main(){
  ios_base::sync_with_stdio(false);
  int t; cin >> t;
  for(int i = 0; i < t; i++)
    testcase();
  
  return 0;
}