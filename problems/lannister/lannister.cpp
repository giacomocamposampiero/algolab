#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpz.h>

typedef long IT;
typedef CGAL::Gmpz ET;

typedef CGAL::Quadratic_program<IT> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;
typedef std::pair<int,int> POS;

void testcase() {
  
  int n, m; std::cin >> n >> m;
  long s; std::cin >> s;
  int constraint = 0;
  
  std::vector<POS> houses;
  for(int i = 0; i<n+m; i++) {
    int x, y; std::cin >> x >> y;
    houses.push_back(std::make_pair(x, y));
  }
  
  Program lp (CGAL::SMALLER, false, 0, false, 0); 
  const int a = 0;
  const int b = 1;
  const int c = 2;
  const int d = 3;
  const int l = 4;
  
  long sum_x = 0, sum_y = 0;
  
  // noble houses
  for (int i = 0; i < n; ++i) {
    // set up constraint a x + b y + c <= 0
    lp.set_a(a, constraint, houses[i].first); 
    lp.set_a(b, constraint, houses[i].second);
    lp.set_a(c, constraint++, 1);
    sum_x -= houses[i].first;
    sum_y -= houses[i].second;
  }
  
  // common houses
  for (int i = n; i < n+m; ++i) {
    // set up constraint a x + b y + c >= 0
    lp.set_a(a, constraint, -houses[i].first); 
    lp.set_a(b, constraint, -houses[i].second);
    lp.set_a(c, constraint++, -1);
    sum_x += houses[i].first;
    sum_y += houses[i].second;
  }
  
  lp.set_l(a, true, 1);
  lp.set_u(a, true, 1);
  
  // check Cercei's constraints
  Solution sol = CGAL::solve_linear_program(lp, ET());
  if(sol.is_infeasible()) {std::cout << "Yuck!" << std::endl; return;}
  
  if(s != -1) {
    lp.set_a(a, constraint, sum_x - s); 
    lp.set_a(b, constraint, sum_y);
    lp.set_a(c, constraint++, m-n);
  }
  
  for(int i=0; i<n+m; i++) {
    // dist <= l
    lp.set_a(b, constraint, houses[i].first); 
    lp.set_a(d, constraint, 1);
    lp.set_a(l, constraint, -1);
    lp.set_b(constraint++, houses[i].second);
    
    // -l <= dist
    lp.set_a(b, constraint, -houses[i].first); 
    lp.set_a(d, constraint, -1);
    lp.set_a(l, constraint, -1);
    lp.set_b(constraint++, -houses[i].second);
  }
  
  lp.set_l(l, true, 0);
  lp.set_c(l, 1);

  // solve the program, using ET as the exact type
  sol = CGAL::solve_linear_program(lp, ET());
  
  if(sol.is_infeasible()) std::cout << "Bankrupt!" << std::endl;
  else std::cout << std::fixed << std::setprecision(0) << std::ceil(CGAL::to_double(sol.objective_value())) << std::endl;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  int t; std::cin >> t;
  while(t--) testcase();
}
