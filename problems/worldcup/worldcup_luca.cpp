#include <bits/stdc++.h>
#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpz.h>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>

using namespace std;

typedef int IT;
typedef CGAL::Gmpz ET;
typedef CGAL::Quadratic_program<IT> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;
typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef K::Point_2 P;
typedef tuple<P,int,int> TPI;

long floor_to_double(const CGAL::Quotient<ET>& x){
  double a = floor(CGAL::to_double(x));
  while (a > x) a -= 1;
  while (a+1 <= x) a += 1;
  return (long)a;
}

void testcase(){
  int n, m, c;
  cin >> n >> m >> c;
  
  vector<TPI> warehouses;
  int x, y, s, a;
  for(int i = 0; i < n; i++){
    cin >> x >> y >> s >> a;
    warehouses.push_back(TPI(P(x,y), s, a));
  }
  
  vector<TPI> stadiums;
  int d, u;
  for(int i = 0; i < m; i++){
    cin >> x >> y >> d >> u;
    stadiums.push_back(TPI(P(x,y), d, u));
  }
  
  Program lp (CGAL::SMALLER, true, 0, false, 0); 
  int ncon = 0;
  for(int i = 0; i < n; i++){
    for(int j = 0; j < m; j++)
      lp.set_a(i*m+j, ncon, 1);
    
    lp.set_b(ncon, get<1>(warehouses[i]));
    ncon++;
  }
  
  for(int j = 0; j < m; j++){
    for(int i = 0; i < n; i++){
      lp.set_a(i*m+j, ncon, 1);
      lp.set_a(i*m+j, ncon+1, -1);
      lp.set_a(i*m+j, ncon+2, get<2>(warehouses[i]));  //*100
    }
    lp.set_b(ncon, get<1>(stadiums[j]));
    lp.set_b(ncon+1, -get<1>(stadiums[j]));
    lp.set_b(ncon+2, 100*get<2>(stadiums[j]));
    ncon += 3;
  }
  
  int r;
  vector<vector<int>> rev(n, vector<int>(m));
  for(int i = 0; i < n; i++){
    for(int j = 0; j < m; j++){
      cin >> r;
      rev[i][j] = r;
    }
  }
  
  vector<vector<int>> ware_lines(n, vector<int>(c, 0));
  vector<vector<int>> stad_lines(m, vector<int>(c, 0));
  double rad;
  for(int i = 0; i < c; i++){
    cin >> x >> y >> rad;
    for(int j = 0; j < n; j++){
      if(CGAL::squared_distance(P(x,y), get<0>(warehouses[j])) <= rad*rad)
        ware_lines[j][i] = 1;
    }
    for(int j = 0; j < m; j++){
      if(CGAL::squared_distance(P(x,y), get<0>(stadiums[j])) <= rad*rad)
        stad_lines[j][i] = 1;
    }
  }
  
  for(int i = 0; i < n; i++){
    for(int j = 0; j < m; j++){
      int num_lines = 0;
      for(int k = 0; k < c; k++)
        num_lines += ware_lines[i][k] ^ stad_lines[j][k];
      //100*rev-num_lines
      //divide result by 100
      lp.set_c(i*m+j, -100*rev[i][j]+num_lines);
    }
  }
  
  Solution sol = CGAL::solve_linear_program(lp, ET());
  if(sol.is_infeasible())
    cout << "RIOT!" << endl;
  else
    cout << floor_to_double(-sol.objective_value()/100) << endl;
}

int main(){
  ios_base::sync_with_stdio(false);
  int t; cin >> t;
  for(int i = 0; i < t; i++)
    testcase();
  
  return 0;
}