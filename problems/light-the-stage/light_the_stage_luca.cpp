#include <bits/stdc++.h>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>

using namespace std;

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Delaunay_triangulation_2<K> Triangulation;
typedef K::Point_2 P;

void testcase(){
  int m; cin >> m;
  int n; cin >> n;
  
  vector<pair<P,int>> participants;
  int x, y, r;
  for(int i = 0; i < m; i++){
    cin >> x >> y >> r;
    participants.push_back(make_pair(P(x,y), r));
  }
  
  int h; cin >> h;
  
  vector<P> lamps;
  map<P,int> seq;
  for(int i = 0; i < n; i++){
    cin >> x >> y;
    lamps.push_back(P(x,y));
    seq[P(x,y)] = i;
  }
  
  Triangulation t;
  t.insert(lamps.begin(), lamps.end());
  bool all_rounds = false;
  vector<int> rounds(m, -1);
  for(int i = 0; i < m; i++){
    P curr = participants[i].first;
    int rad = participants[i].second;
    P nearest = t.nearest_vertex(curr)->point();
    if(CGAL::squared_distance(curr, nearest) >= (long)(rad+h)*(rad+h)){
      all_rounds = true;
      cout << i << " ";
    }
    else{
      //find the minimum index
      for(int j = 0; j < n; j++){
        if(CGAL::squared_distance(curr, lamps[j]) < (long)(rad+h)*(rad+h)){
          rounds[i] = j;
          break;
        }
      }
    }
  }
  
  if(all_rounds == false){
    int maxround = -1;
    for(int i = 0; i < m; i++)
      maxround = max(maxround, rounds[i]);
    
    for(int i = 0; i < m; i++){
      if(rounds[i] == maxround)
        cout << i << " ";
    }
  }
  
  cout << endl;
}

int main(){
  ios_base::sync_with_stdio(false);
  int t; cin >> t;
  for(int i = 0; i < t; i++)
    testcase();
  
  return 0;
}