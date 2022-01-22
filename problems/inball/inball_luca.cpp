#include <iostream>
#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpz.h>

using namespace std;

typedef int IT;
typedef CGAL::Gmpz ET;
typedef CGAL::Quadratic_program<IT> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;

long floor_to_double(const CGAL::Quotient<ET> &x){
  double a = floor(CGAL::to_double(x));
  while(a > x)  a -= 1;
  while(a+1 <= x) a += 1;
  return (long)a;
}

bool testcase(){
  int n; cin >> n;
  if(n == 0)  return true;
  
  int d; cin >> d;
  Program lp (CGAL::SMALLER, false, 0, false, 0);
  
  int a, b;
  const int r = d+1;
  int sum;
  for(int i = 0; i < n; i++){
    sum = 0;
    for(int j = 0; j < d; j++){
      cin >> a;
      sum += a*a;
      lp.set_a(j, i, a);
    }
    sum = sqrt(sum);
    lp.set_a(r, i, sum);
    cin >> b;
    lp.set_b(i, b);
  }
  
  lp.set_l(r, true, 0);
  lp.set_c(r, -1);
  
  Solution sol = CGAL::solve_linear_program(lp, ET());
  
  if(sol.is_infeasible())
    cout << "none" << endl;
  else if(sol.is_unbounded())
    cout << "inf" << endl;
  else
    cout << floor_to_double(-sol.objective_value()) << endl;
  
  return false;
}

int main(){
  ios_base::sync_with_stdio(false);
  bool end = false;
  while(!end)
    end = testcase();
    
  return 0;
}