//75 POINTS SOLUTION
#include <bits/stdc++.h>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>

using namespace std;

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef K::Point_2 P;
typedef K::Segment_2 S;
typedef K::Direction_2 D;
typedef tuple<long, D, int> TLDI;

void testcase(){
  int n; cin >> n;
  
  vector<TLDI> bikers;
  long y0, x1, y1;
  for(int i = 0; i < n; i++){
    cin >> y0 >> x1 >> y1;
    D dir(S(P(0, y0), P(x1, y1)));
    bikers.push_back(TLDI(y0, dir, i)); //starting y, direction, original index
  }
  
  sort(bikers.begin(), bikers.end());
  
  vector<int> results;
  D bestdir = get<1>(bikers[n-1]);
  results.push_back(get<2>(bikers[n-1]));
  for(int i = n-2; i >= 0; i--){
    D dir = get<1>(bikers[i]);
    if(dir <= bestdir){
      results.push_back(get<2>(bikers[i]));
      bestdir = dir;
    }
  }

  sort(results.begin(), results.end());
  
  for(auto r : results)
    cout << r << " ";

  cout << endl;
}

int main(){
  ios_base::sync_with_stdio(false);
  int t; cin >> t;
  for(int i = 0; i < t; i++)
    testcase();
  
  return 0;
}