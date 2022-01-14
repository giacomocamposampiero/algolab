#include <iomanip>
#include <iostream>
#include <vector>
#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpq.h>

typedef CGAL::Gmpq ET;
typedef CGAL::Quadratic_program<ET> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution; 
typedef CGAL::Quotient<ET> Objective;

double ceil_to_double( Objective const & o ) {
  double d = std::ceil( CGAL::to_double( o ) ); while( d < o ) d += 1;
  while(d-1>= o)d-=1;
  return d;
}

struct coord {
  int x, y;
};

void testcase() {
  
  int n, m, h, w; std::cin >> n >> m >> h >> w;
  
  std::vector<coord> nails(n);
  for(int i=0; i<n; i++) std::cin >> nails[i].x >> nails[i].y;
  
  std::vector<coord> old(m);
  for(int i=0; i<m; i++) std::cin >> old[i].x >> old[i].y;
  
  Program lp (CGAL::SMALLER, true, 1, false, 0); 
  int constraint = 0;
  
  for(int i=0; i<n; i++) {
    for(int j=i+1; j<n; j++) {
      lp.set_a(i, constraint, 1); 
      lp.set_a(j, constraint, 1); 
      ET dx = std::abs( nails[i].x - nails[j].x );
      ET dy = std::abs( nails[i].y - nails[j].y );
      lp.set_b(constraint++, 2 * std::max(dx/w, dy/h));
    }
  }
  
  for(int i=0; m > 0 && i<n; i++) { 
    ET best = 33554432;
    for(int j=0; j<m; j++) {
      ET dx = std::abs( nails[i].x - old[j].x );
      ET dy = std::abs( nails[i].y - old[j].y );
      best = std::min(best, 2 * std::max(dx/w, dy/h) - 1);
    }
    lp.set_a(i, constraint, 1); 
    lp.set_b(constraint++,  best);
  }

  for(int ai=0; ai<n; ai++) lp.set_c(ai, -2*(h+w)); 
  
  Solution s = CGAL::solve_linear_program(lp, ET());
  std::cout << std::setprecision(0) << std::fixed << ceil_to_double( -s.objective_value() ) << std::endl;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  int t; std::cin >> t;
  while(t--) testcase();
}
