#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpz.h>

typedef int IT;
typedef CGAL::Gmpz ET;

typedef CGAL::Quadratic_program<IT> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;

int main() {
  
  std::ios_base::sync_with_stdio(false);
  
  while(true) {
    
    int n, m; std::cin >> n >> m;
    if(n == 0 && m == 0) return 0;
    
    std::vector<std::pair<int,int>> nutrients;
    for(int i=0; i<n; i++) {
      int min, max; std::cin >> min >> max;
      nutrients.push_back(std::make_pair(min, max));
    }
    
    std::vector<int> prices(m, 0);
    std::vector<std::vector<int>> food_n(m, std::vector<int>(n,0));
    for(int j=0; j<m; j++) {
      std::cin >> prices[j];
      for(int i=0; i<n; i++) std::cin >> food_n[j][i];
    }
    
    Program lp (CGAL::SMALLER, true, 0, false, 0); 
    int c = 0;
    
    // enough nutrient costraints
    for(int i=0; i<n; i++) {
      for(int j=0; j<m; j++) lp.set_a(j, c,  food_n[j][i]);
      lp.set_b(c++, nutrients[i].second);
      for(int j=0; j<m; j++) lp.set_a(j, c, -food_n[j][i]);
      lp.set_b(c++, -nutrients[i].first);
    }
    
    // objective function - minimize overall cost
    for(int j=0; j<m; j++) lp.set_c(j, prices[j]);
    
    Solution s = CGAL::solve_linear_program(lp, ET());
    
    if(s.is_infeasible()) std::cout << "No such diet." << std::endl;
    else std::cout << (int) CGAL::to_double(s.objective_value()) << std::endl;

  }
}
