#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpz.h>

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;

typedef int IT;
typedef CGAL::Gmpz ET;

typedef CGAL::Quadratic_program<IT> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;

double floor_to_double(const K::FT& x) {
  double a = std::floor(CGAL::to_double(x));
  while (a > x) a -= 1;
  while (a+1 <= x) a += 1;
  return a;
}

int main() {
  
  std::ios_base::sync_with_stdio(false);
  
  while(true) {
    
    int p; std::cin >> p;
    if(p == 0) return 0;
    
    int a, b; std::cin >> a >> b;
    Solution s;
    
    if(p == 1) {
      
      Program lp (CGAL::SMALLER, true, 0, false, 0); 
      const int X = 0; 
      const int Y = 1;
      
      lp.set_a(X, 0, 1); lp.set_a(Y, 0, 1); lp.set_b(0, 4);  // x+y <= 4
      lp.set_a(X, 1, 4); lp.set_a(Y, 1, 2); lp.set_b(1, a*b);  // 4x+2y <= ab
      lp.set_a(X, 2, -1); lp.set_a(Y, 2, 1); lp.set_b(2, 1);  // -x+y <= 1
      
      lp.set_c(X, a);                                       
      lp.set_c(Y, -b); 
      
      s = CGAL::solve_linear_program(lp, ET());
      
    } else {
      
      Program lp (CGAL::SMALLER, false, 0, true, 0); 
      const int X = 0; 
      const int Y = 1;
      const int Z = 2;
      
      lp.set_a(X, 0, -1); lp.set_a(Y, 0, -1); lp.set_b(0, 4); 
      lp.set_a(X, 1, -4); lp.set_a(Y, 1, -2); lp.set_a(Z, 1, -1); lp.set_b(1, a*b); 
      lp.set_a(X, 2, 1); lp.set_a(Y, 2, -1); lp.set_b(2, 1);  
      
      lp.set_c(X, a);                                       
      lp.set_c(Y, b); 
      lp.set_c(Z, 1); 
      
      s = CGAL::solve_linear_program(lp, ET());
      
    }
    
    if(s.is_infeasible()) std::cout << "no" << std::endl;
    else if(s.is_unbounded()) std::cout << "unbounded" << std::endl;
    else if(p==2) std::cout << (int) CGAL::to_double(s.objective_value()) << std::endl;
    else if(p==1) std::cout << - (int) CGAL::to_double(s.objective_value()) << std::endl;
    
  }
}
