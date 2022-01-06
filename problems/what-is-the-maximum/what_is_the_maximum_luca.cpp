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

long ceil_to_double(const CGAL::Quotient<ET>& x){
  double a = ceil(CGAL::to_double(x));
  while (a < x) a += 1;
  while (a-1 >= x) a -= 1;
  return (long)a;
}

void prob1(){
  int a, b;
  cin >> a >> b;
  
  Program lp (CGAL::SMALLER, true, 0, false, 0);
  const int X = 0;
  const int Y = 1;
  
  lp.set_a(X, 0, 1);  lp.set_a(Y, 0, 1);  lp.set_b(0, 4);
  lp.set_a(X, 1, 4);  lp.set_a(Y, 1, 2);  lp.set_b(1, a*b);
  lp.set_a(X, 2, -1); lp.set_a(Y, 2, 1);  lp.set_b(2, 1);
  
  lp.set_c(Y, -b); lp.set_c(X, a);
  
  Solution sol = CGAL::solve_linear_program(lp, ET());
  
  if(sol.is_infeasible())
    cout << "no" << endl;
  else if(sol.is_unbounded())
    cout << "unbounded" << endl;
  else
    cout << floor_to_double(-sol.objective_value()) << endl;
}

void prob2(){
  int a, b;
  cin >> a >> b;
  
  Program lp (CGAL::SMALLER, false, 0, true, 0);
  const int X = 0;
  const int Y = 1;
  const int Z = 2;
  
  lp.set_a(X, 0, -1);  lp.set_a(Y, 0, -1);  lp.set_b(0, 4);
  lp.set_a(X, 1, -4);  lp.set_a(Y, 1, -2);  lp.set_a(Z, 1, -1); lp.set_b(1, a*b);
  lp.set_a(X, 2, 1); lp.set_a(Y, 2, -1);  lp.set_b(2, 1);
  
  lp.set_c(Y, b); lp.set_c(X, a); lp.set_c(Z, 1);
  
  Solution sol = CGAL::solve_linear_program(lp, ET());
  
  if(sol.is_infeasible())
    cout << "no" << endl;
  else if(sol.is_unbounded())
    cout << "unbounded" << endl;
  else
    cout << ceil_to_double(sol.objective_value()) << endl;
}

bool testcase(){
  int p; cin >> p;
  if(p == 0)  return true;
  
  switch(p){
    case 1:
      prob1();
      break;
    case 2:
      prob2();
      break;
  }
  
  return false;
}

int main(){
  ios_base::sync_with_stdio(false);
  bool end = false;
  while(!end)
    end = testcase();
  
  return 0;
}