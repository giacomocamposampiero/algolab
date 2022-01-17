#include <bits/stdc++.h>
#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpz.h>

using namespace std;

typedef int IT;
typedef CGAL::Gmpz ET;
typedef CGAL::Quadratic_program<IT> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;

long floor_to_double(const CGAL::Quotient<ET>& x){
  double a = floor(CGAL::to_double(x));
  while (a > x) a -= 1;
  while (a+1 <= x) a += 1;
  return (long)a;
}

void testcase(){
  long xs, ys, n;
  cin >> xs >> ys >> n;
  
  Program lp (CGAL::SMALLER, false, 0, false, 0); 
  const int X = 0, Y = 1, T = 2;
  int a, b, c, v;
  int ncon = 0;
  for(int i = 0; i < n; i++){
    cin >> a >> b >> c >> v;
    if(a*xs+b*ys+c <= 0){
      lp.set_a(X, ncon, a); lp.set_a(Y, ncon, b);
      lp.set_a(T, ncon, v*sqrt((long)a*a+(long)b*b)); //LONG!!!
      lp.set_b(ncon, -c);
      ncon++;
    }
    else{
      lp.set_a(X, ncon, -a); lp.set_a(Y, ncon, -b);
      lp.set_a(T, ncon, v*sqrt((long)a*a+(long)b*b));
      lp.set_b(ncon, c);
      ncon++;
    }
  }
  
  lp.set_l(T, true, 0);
  lp.set_c(T, -1);
  
  Solution sol = CGAL::solve_linear_program(lp, ET());
  
  cout << floor_to_double(-sol.objective_value()) << endl;
}

int main(){
  ios_base::sync_with_stdio(false);
  int t; cin >> t;
  for(int i = 0; i < t; i++)
    testcase();
  
  return 0;
}