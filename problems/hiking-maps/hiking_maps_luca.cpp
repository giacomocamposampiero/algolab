#include <bits/stdc++.h>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>

using namespace std;

typedef CGAL::Exact_predicates_inexact_constructions_kernel EPIC;
typedef EPIC::Point_2 P;

bool check(P &q0, P &q1, P &q2, P &q3, P &q4, P &q5, P &start, P &end){
  return !CGAL::right_turn(q0, q1, start) && !CGAL::right_turn(q0, q1, end) &&
          !CGAL::right_turn(q2, q3, start) && !CGAL::right_turn(q2, q3, end) &&
          !CGAL::right_turn(q4, q5, start) && !CGAL::right_turn(q4, q5, end);
}

void testcase(){
  int m; cin >> m;
  int n; cin >> n;
  
  vector<P> path;
  int x, y;
  for(int i = 0; i < m; i++){
    cin >> x >> y;
    path.push_back(P(x,y));
  }
  
  int x0, x1, x2, x3, x4, x5;
  int y0, y1, y2, y3, y4, y5;
  vector<vector<bool>> contains(n, vector<bool>(m, false));
  for(int i = 0; i < n; i++){
    cin >> x0 >> y0 >> x1 >> y1;
    cin >> x2 >> y2 >> x3 >> y3;
    cin >> x4 >> y4 >> x5 >> y5;
    P q0(x0, y0), q1(x1, y1), q2(x2, y2), q3(x3, y3), q4(x4, y4), q5(x5, y5);
    //arrange points for later orientation check
    if(CGAL::right_turn(q0, q1, q2))  swap(q0, q1);
    if(CGAL::right_turn(q2, q3, q4))  swap(q2, q3);
    if(CGAL::right_turn(q4, q5, q0))  swap(q4, q5);
    
    for(int j = 0; j < m-1; j++)
      contains[i][j] = check(q0, q1, q2, q3, q4, q5, path[j], path[j+1]);
  }
  
  int b = 0, e = 0;
  int best = n;
  while(e < n){
    bool found = false;
    for(int j = 0; j < m-1; j++){
      found = false;
      for(int i = b; i <= e; i++){
        if(contains[i][j]){
          found = true;
          break;
        }
      }
      if(!found)
        break;
    }
    if(!found)
      e++;
    else{
      best = min(best, e-b+1);
      b++;
    }
  }
  
  cout << best << endl;
}

int main(){
  ios_base::sync_with_stdio(false);
  int c; cin >> c;
  for(int i = 0; i < c; i++)
    testcase();
    
  return 0;
}