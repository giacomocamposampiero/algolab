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

long floor_to_double(const CGAL::Quotient<ET>& x){
  double a = floor(CGAL::to_double(x));
  while (a > x) a -= 1;
  while (a+1 <= x) a += 1;
  return (long)a;
}

bool testcase(){
  int n; cin >> n;
  int m; cin >> m;
  
  if(n == 0 && m == 0)  return true;
  
  Program lp (CGAL::SMALLER, true, 0, false, 0);
  
  vector<PI> nutrients;
  int mini, maxi;
  for(int i = 0; i < n; i++){
    cin >> mini >> maxi;
    nutrients.push_back(PI(mini, maxi));
  }
  
  vector<int> cost;
  vector<vector<int>> amounts(m, vector<int>(n));

  int p;
  for(int j = 0; j < m; j++){
    cin >> p;
    cost.push_back(p);
    int c;
    for(int i = 0; i < n; i++){
      cin >> c;
      amounts[j][i] = c;
    }
  }
  
  //constraints
  int ncon = 0;
  for(int i = 0; i < n; i++){
    for(int j = 0; j < m; j++){
      lp.set_a(j, ncon, amounts[j][i]);
      lp.set_a(j, ncon+1, -amounts[j][i]);
    }
    lp.set_b(ncon, nutrients[i].second);
    lp.set_b(ncon+1, -nutrients[i].first);
    ncon += 2;
  }
  
  //objective function
  for(int j = 0; j < m; j++)
    lp.set_c(j, cost[j]);
  
  Solution sol = CGAL::solve_linear_program(lp, ET());
  
  if(sol.is_infeasible())
    cout << "No such diet." << endl;
  else
    cout << floor_to_double(sol.objective_value()) << endl;
  
  return false;
}

int main(){
  ios_base::sync_with_stdio(false);
  bool end = false;
  while(!end)
    end = testcase();
  
  return 0;
}