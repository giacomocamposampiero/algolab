#include <bits/stdc++.h>

using namespace std;

typedef pair<int,int> PI;

void testcase(){
  int n; cin >> n;
  int k; cin >> k;
  
  vector<int> cards;
  int v;
  for(int i = 0; i < n; i++){
    cin >> v;
    cards.push_back(v);
  }
  
  int i = 0, j = 0;
  int val = cards[0];
  int minval = numeric_limits<int>::max();
  PI minidx;
  while(j < n){
    if(abs(val-k) < minval){
      minval = min(minval, abs(val-k));
      minidx = PI(i,j);
    }
    
    if(val == k){
      minval = 0;
      minidx = PI(i,j);
      break;
    }
    
    if(val < k){
      j++;
      if(j == n)  break;
      val += cards[j];
    }
    
    else{
      minval = min(minval, abs(val-k));
      val -= cards[i];
      i++;
      if(i > j){
        if(i == n)  break;
        j = i;
        val = cards[i];
      }
    }
  }
  
  cout << minidx.first << " " << minidx.second << endl;
}

int main(){
  ios_base::sync_with_stdio(false);
  int t; cin >> t;
  for(int i = 0; i < t; i++)
    testcase();
  
  return 0;
}