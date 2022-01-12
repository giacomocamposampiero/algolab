#include <bits/stdc++.h>

using namespace std;

typedef pair<long, long> PR;

bool f(vector<PR> &moves, vector<PR> &list, int start, int n, long d, long t, long D, long T, long pot){
  //list
  list.push_back(PR(d, t));
  
  if(d >= D){
    if(t < T) return true;
    
    return false;
  }
  if(start >= n)  return false;
  
  return f(moves, list, start+1, n, d+moves[start].first+pot, t+moves[start].second, D, T, pot) || f(moves, list, start+1, n, d, t, D, T, pot);
}

bool split_and_list(vector<PR> &moves, int n, long D, long T, long pot){
  //split
  vector<PR> S1, S2;
  for(int i = 0; i < n; i++){
    if(i%2 == 0)
      S1.push_back(moves[i]);
    else
      S2.push_back(moves[i]);
  }
  
  //list
  vector<PR> L1, L2;
  if(f(S1, L1, 0, (int)S1.size(), 0, 0, D, T, pot))  return true;
  if(f(S2, L2, 0, (int)S2.size(), 0, 0, D, T, pot))  return true;
  
  //sort L2 with respect to time so that I...
  sort(L2.begin(), L2.end(), [](auto &p1, auto &p2) -> bool{
    return p1.second < p2.second;
  });
  
  //...store the best distance found for t <= t_i
  long best = -1;
  vector<long> bestdist;
  for(int i = 0; i < (int)L2.size(); i++){
    if(L2[i].first > best)  best = L2[i].first;
    bestdist.push_back(best);
  }
  
  for(int i = 0; i < (int)L1.size(); i++){
    long d1 = L1[i].first;
    long t1 = L1[i].second;
    int left = 0, right = (int)L2.size()-1;
    while(left <= right){
      int mid = (left+right)/2;
      if(t1 + L2[mid].second < T){
        if(d1 + bestdist[mid] >= D) return true;
        left = mid+1;
      }
      else
        right = mid-1;
    }
  }
  
  return false;
}

void testcase(){
  int n; cin >> n;
  int m; cin >> m;
  long D; cin >> D;
  long T; cin >> T;
  
  vector<PR> moves;
  long d, t;
  for(int i = 0; i < n; i++){
    cin >> d >> t;
    moves.push_back(PR(d, t));
  }
  
  vector<long> potions;
  long s;
  for(int i = 0; i < m; i++){
    cin >> s;
    potions.push_back(s);
  }
  
  //first try without potions
  bool res = split_and_list(moves, n, D, T, 0);
  if(res == true){
    cout << 0 << endl;
    return;
  }
  
  int left = 0, right = m-1;
  int mid = -1;
  while(left <= right){
    mid = (left+right)/2;
    bool res = split_and_list(moves, n, D, T, potions[mid]);
    if(res == true)
      right = mid-1;
    else
      left = mid+1;
  }
  
  if(left == m)
    cout << "Panoramix captured" << endl;
  else
    cout << left+1 << endl; //+1 because potions start from 1
}

int main(){
  ios_base::sync_with_stdio(false);
  int t; cin >> t;
  for(int i = 0; i < t; i++)
    testcase();
    
  return 0;
}