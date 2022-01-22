#include <bits/stdc++.h>

using namespace std;

typedef pair<int,int> PI;

int deacR(vector<bool> &deactivated, int start, int n){
  if(start >= n || deactivated[start])
    return 0;
  
  int res = 1 + deacR(deactivated, 2*start+1, n) + deacR(deactivated, 2*start+2, n);
  deactivated[start] = true;
  return res;
}

void testcase(){
  int n; cin >> n;
  
  vector<PI> bombs;
  int t;
  for(int i = 0; i < n; i++){
    cin >> t;
    bombs.push_back(PI(t, i));
  }
  
  sort(bombs.begin(), bombs.end());
  int count = 0;
  vector<bool> deactivated(n, false);
  for(int i = 0; i < n; i++){
    count += deacR(deactivated, bombs[i].second, n);
    if(count > bombs[i].first){
      cout << "no" << endl;
      return;
    }
  }
  
  cout << "yes" << endl;
}

int main(){
  ios_base::sync_with_stdio(false);
  int t; cin >> t;
  for(int i = 0; i < t; i++){
    testcase();
  }
  
  return 0;
}