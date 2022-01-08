//100 POINTS SOLUTION
#include <bits/stdc++.h>
#include <CGAL/Gmpq.h>

using namespace std;

typedef tuple<long, CGAL::Gmpq, int> TLDI;

void testcase(){
  int n; cin >> n;
  
  vector<TLDI> bikers;
  long y0, x1, y1;
  for(int i = 0; i < n; i++){
    cin >> y0 >> x1 >> y1;
    bikers.push_back(TLDI(y0, CGAL::Gmpq(y1-y0, x1), i)); //starting y, direction, original index
  }
  
  sort(bikers.begin(), bikers.end());
  
  vector<bool> forever(n, true);
  CGAL::Gmpq bestdir = get<1>(bikers[0]);
  //bottom to top
  for(int i = 1; i < n; i++){
    CGAL::Gmpq curr = get<1>(bikers[i]);
    if(CGAL::abs(curr) < CGAL::abs(bestdir) || (CGAL::abs(curr) == CGAL::abs(bestdir) && curr > 0))
      bestdir = curr;
    else if(curr < bestdir)
      forever[get<2>(bikers[i])] = false;
  }
  
  bestdir = get<1>(bikers[n-1]);
  //top to bottom
  for(int i = n-2; i >= 0; i--){
    CGAL::Gmpq curr = get<1>(bikers[i]);
    if(CGAL::abs(curr) <= CGAL::abs(bestdir))
      bestdir = curr;
    else if(curr > bestdir)
      forever[get<2>(bikers[i])] = false;
  }

  for(int i = 0; i < n; i++)
    if(forever[i])
      cout << i << " ";

  cout << endl;
}

int main(){
  ios_base::sync_with_stdio(false);
  int t; cin >> t;
  for(int i = 0; i < t; i++)
    testcase();
  
  return 0;
}