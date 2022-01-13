#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpz.h>
#include <cmath>

typedef int IT;
typedef CGAL::Gmpz ET;

typedef CGAL::Quadratic_program<IT> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;

int main() {
  
  std::ios_base::sync_with_stdio(false);
  while(true) {
    
    int n; std::cin >> n;
    if(n == 0) return 0;
    int d; std::cin >> d;
    
    Program lp (CGAL::SMALLER, false, 0, false, 0); 
    const int R = d;
    
    for(int i=0; i<n; i++) {
      int norm = 0;
      for(int x_d=0; x_d<d; x_d++) {
        int a; std::cin >> a;
        lp.set_a(x_d, i, a);
        norm += a * a;
      }
      lp.set_a(R, i, std::floor(std::sqrt(norm)));
      int b; std::cin >> b;
      lp.set_b(i, b);
    }
    
    lp.set_l(R, true, 0);
    lp.set_c(R, -1);
  
    Solution s = CGAL::solve_linear_program(lp, ET());
    
    if (s.is_unbounded()) std::cout << "inf" << std::endl;
    else if (s.is_infeasible()) std::cout << "none" << std::endl;
    else std::cout <<  (int) (- CGAL::to_double(s.objective_value())) << std::endl;
    
  }
}
