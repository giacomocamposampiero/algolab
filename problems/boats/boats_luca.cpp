#include <bits/stdc++.h>

using namespace std;

typedef pair<int,int> PI;

void testcase(){
  int n; cin >> n;
  
  vector<PI> boats;
  int l, p;
  for(int i = 0; i < n; i++){
    cin >> l >> p;
    boats.push_back(PI(p, l));
  }
  
  sort(boats.begin(), boats.end());
  
  //place a boat with the ring at the extreme right and see which adjacent boat to put
  int start = numeric_limits<int>::min();
  int last = numeric_limits<int>::min();
  int count = 0;
  for(int i = 0; i < n; i++){
    if(boats[i].first >= start){
      count++;
      last = start;
      start = max(boats[i].first, start+boats[i].second);
    }
    else{ //consider removing previous choice
      int new_start = max(last+boats[i].second, boats[i].first);
      start = min(start, new_start);
    }
  }
  
  cout << count << endl;
}


int main(){
  ios_base::sync_with_stdio(false);
  int t; cin >> t;
  for(int i = 0; i < t; i++){
    testcase();
  }
    
  return 0;
}