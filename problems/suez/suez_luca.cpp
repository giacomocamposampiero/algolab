#include <bits/stdc++.h>
#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpz.h>

using namespace std;

typedef int IT;
typedef CGAL::Gmpz ET;
typedef CGAL::Quadratic_program<IT> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;
typedef pair<int,int> PI;

long ceil_to_double(const CGAL::Quotient<ET>& x){
  double a = ceil(CGAL::to_double(x));
  while (a < x) a += 1;
  while (a-1 >= x) a -= 1;
  return (long)a;
}

void testcase(){
  int n, m, h, w;
  cin >> n >> m >> h >> w;
  
  vector<PI> newp;
  int x, y;
  for(int i = 0; i < n; i++){
    cin >> x >> y;
    newp.push_back(PI(x,y));
  }
  
  vector<PI> oldp;
  for(int i = 0; i < m; i++){
    cin >> x >> y;
    oldp.push_back(PI(x,y));
  }
  
  Program lp (CGAL::SMALLER, true, 1, false, 0);
  int ncon = 0;
  for(int i = 0; i < n; i++){
    for(int j = i+1; j < n; j++){
      if((long)h*abs(newp[j].first-newp[i].first) > (long)w*abs(newp[j].second-newp[i].second)){
        lp.set_a(i, ncon, w); lp.set_a(j, ncon, w);
        lp.set_b(ncon, 2*abs(newp[j].first-newp[i].first));
      }
      else{
        lp.set_a(i, ncon, h); lp.set_a(j, ncon, h);
        lp.set_b(ncon, 2*abs(newp[j].second-newp[i].second));
      }
      ncon++;
    }
  }
  
  //it is sufficient to define constraints on the nearest already present rectangles
  for(int i = 0; i < n; i++){
    long best = numeric_limits<long>::max();
    int minidx;
    char dim;
    for(int j = 0; j < m; j++){
      long distx = (long)h*abs(oldp[j].first-newp[i].first);
      long disty = (long)w*abs(oldp[j].second-newp[i].second);
      if(distx > disty){
        if(distx < best){
          best = distx;
          minidx = j;
          dim = 'x';
        }
      }
      else{
        if(disty < best){
          best = disty;
          minidx = j;
          dim = 'y';
        }
      }
    }
    if(m > 0){
      if(dim == 'x'){
        lp.set_a(i, ncon, w);
        lp.set_b(ncon, 2*abs(oldp[minidx].first-newp[i].first)-w);
      }
      else{
        lp.set_a(i, ncon, h);
        lp.set_b(ncon, 2*abs(oldp[minidx].second-newp[i].second)-h);
      }
      ncon++;
    }
  }
  
  
  for(int i = 0; i < n; i++)
    lp.set_c(i, -2*(h+w));
  
  Solution sol = CGAL::solve_linear_program(lp, ET());
  
  cout << ceil_to_double(-sol.objective_value()) << endl;
}

int main(){
  ios_base::sync_with_stdio(false);
  int t; cin >> t;
  for(int i = 0; i < t; i++)
    testcase();
  
  return 0;
}