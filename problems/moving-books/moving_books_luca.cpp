#include <bits/stdc++.h>

using namespace std;

void testcase(){
  int n; cin >> n;
  int m; cin >> m;
  
  vector<int> strength;
  int s;
  for(int i = 0; i < n; i++){
    cin >> s;
    strength.push_back(s);
  }
  
  sort(strength.begin(), strength.end(), greater<int>());
  
  multiset<int> weights;
  int w;
  for(int i = 0; i < m; i++){
    cin >> w;
    weights.insert(w);
  }
  
  
  if(*prev(weights.end()) > strength[0]){
    cout << "impossible" << endl;
    return;
  }
  
  bool first_time = true;
  int tempo = 0;
  while(weights.size() != 0){
    if(!first_time)
      tempo++;
    for(int i = 0; i < n && weights.size() != 0; i++){
      auto up = weights.upper_bound(strength[i]);
      if(up != weights.begin()){  //strength[i] >= *up
        up = prev(up);
        weights.erase(up);
      }
      else break; //CUT useless people
    }
    first_time = false;
    tempo += 2;
  }
  
  cout << tempo << endl;
}

int main(){
  ios_base::sync_with_stdio(false);
  int t; cin >> t;
  for(int i = 0; i < t; i++)
    testcase();
  
  return 0;
}