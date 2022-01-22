#include <bits/stdc++.h>
#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpz.h>

using namespace std;

typedef long IT;
typedef CGAL::Gmpz ET;
typedef CGAL::Quadratic_program<IT> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;

long ceil_to_double(const CGAL::Quotient<ET>& x){
  double a = ceil(CGAL::to_double(x));
  while (a < x) a += 1;
  while (a-1 >= x) a -= 1;
  return (long)a;
}

void testcase(){
  int n; cin >> n;
  int m; cin >> m;
  long s; cin >> s;
  
  Program lp (CGAL::SMALLER, false, 0, false, 0); 
  const int b = 0;
  const int c = 1;
  const int c2 = 2;
  const int d = 3;
  
  int x, y;
  int ncon = 0;
  long sumxn = 0, sumyn = 0;
  long sumxc = 0, sumyc = 0;
  for(int i = 0; i < n; i++){
    cin >> x >> y;
    sumxn += x;
    sumyn += y;
    //x + by + c <= 0
    lp.set_a(b, ncon, y);
    lp.set_a(c, ncon, 1);
    lp.set_b(ncon, -x);
    ncon++;
    //abs(yf-yd) <= d
    lp.set_a(b, ncon, -x);
    lp.set_a(c2, ncon, -1);
    lp.set_a(d, ncon, -1);
    lp.set_b(ncon, -y);
    ncon++;
    lp.set_a(b, ncon, x);
    lp.set_a(c2, ncon, 1);
    lp.set_a(d, ncon, -1);
    lp.set_b(ncon, y);
    ncon++;
  }
  
  for(int i = 0; i < m; i++){
    cin >> x >> y;
    sumxc += x;
    sumyc += y;
    //x + by + c >= 0
    lp.set_a(b, ncon, -y);
    lp.set_a(c, ncon, -1);
    lp.set_b(ncon, x);
    ncon++;
    //abs(yf-yd) <= d
    lp.set_a(b, ncon, x);
    lp.set_a(c2, ncon, 1);
    lp.set_a(d, ncon, -1);
    lp.set_b(ncon, y);
    ncon++;
    lp.set_a(b, ncon, -x);
    lp.set_a(c2, ncon, -1);
    lp.set_a(d, ncon, -1);
    lp.set_b(ncon, -y);
    ncon++;
  }
  
  Solution sol = CGAL::solve_linear_program(lp, ET());
  if(sol.is_infeasible()){
    cout << "Yuck!" << endl;
    return;
  }
  
  if(s != -1){
    lp.set_a(b, ncon, sumyc-sumyn);
    lp.set_a(c, ncon, m-n);
    lp.set_b(ncon, s-sumxc+sumxn);
  }
  
  lp.set_l(d, true, 0);
  lp.set_c(d, 1);
  
  sol = CGAL::solve_linear_program(lp, ET());
  if(sol.is_infeasible())
    cout << "Bankrupt!" << endl;
  else
    cout << ceil_to_double(sol.objective_value()) << endl;
}

int main(){
  ios_base::sync_with_stdio(false);
  int t; cin >> t;
  for(int i = 0; i < t; i++)
    testcase();
  
  return 0;
}