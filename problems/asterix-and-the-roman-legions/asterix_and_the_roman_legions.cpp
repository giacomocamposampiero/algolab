///2
#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpz.h>

typedef long IT;
typedef CGAL::Gmpz ET;

typedef CGAL::Quadratic_program<IT> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;


void testcase() {

  Program lp (CGAL::SMALLER, false, 0, false, 0); 
  
  const int X = 0; 
  const int Y = 1;
  const int r = 2;
  
  int xs, ys, n; std::cin >> xs >> ys >> n;
  
  for(int i=0; i<n; i++) {
    
    long a, b, c, v; std::cin >> a >> b >> c >> v;
    int norm = std::sqrt(a*a+b*b);
    
    if(xs*a + ys*b + c < 0) {
      lp.set_a(X, i, a); 
      lp.set_a(Y, i, b); 
      lp.set_b(i, -c);
    } else {      
      lp.set_a(X, i, -a); 
      lp.set_a(Y, i, -b); 
      lp.set_b(i, c);
    }
    lp.set_a(r, i, norm*v);
    
  }
  
  lp.set_l(r, true, 0);
  lp.set_c(r, -1);

  Solution s = CGAL::solve_linear_program(lp, ET());
  if(s.is_optimal()) {
    std::cout << (long) std::floor(- CGAL::to_double(s.objective_value())) << std::endl;
  } else std::cout << s <<std::endl;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  int t; std::cin >> t;
  while(t--) testcase();
}
