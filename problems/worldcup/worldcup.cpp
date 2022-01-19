#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpz.h>

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Delaunay_triangulation_2<K>  Triangulation;
typedef Triangulation::Edge_iterator  Edge_iterator;

typedef int IT;
typedef CGAL::Gmpz ET;

typedef CGAL::Quadratic_program<IT> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;

struct contour {
  K::Point_2 center;
  long squared_r;
};

void testcase() {
  
  int n, m, c; std::cin >> n >> m >> c;
  
  Program lp (CGAL::SMALLER, true, 0, false, 0); 
  int constraint = 0;
  
  std::vector<int> alcool(n, 0);
  std::vector<K::Point_2> pts;
  pts.reserve(n+m);
  
  for(int i=0; i<n; i++) {
    
    int x, y, s, a; std::cin >> x >> y >> s >> a;
    pts.push_back(K::Point_2(x, y));
    alcool[i] = a;
    
    // supply constraint
    for(int j=0; j<m; j++) lp.set_a(m*i+j, constraint, 1); 
    lp.set_b(constraint++, s);
    
  }
  
  for(int j=0; j<m; j++) {
    
    int x, y, d, u; std::cin >> x >> y >> d >> u;
    pts.push_back(K::Point_2(x, y));
    
    // (exact) demand constraint
    for(int i=0; i<n; i++) lp.set_a(m*i+j, constraint,  1); 
    lp.set_b(constraint++,  d);
    for(int i=0; i<n; i++) lp.set_a(m*i+j, constraint, -1); 
    lp.set_b(constraint++, -d);
    
    // alcool constraint
    for(int i=0; i<n; i++) lp.set_a(m*i+j, constraint,  alcool[i]); 
    lp.set_b(constraint++,  u*100);
    
  }
  
  std::vector<int> r(n*m, 0);
  for(int i=0; i<n; i++) 
    for(int j=0; j<m; j++) 
      std::cin >> r[i*m+j];
      
  Triangulation t;
  t.insert(pts.begin(), pts.end());
  
  std::vector<contour> lines;
  for(int i=0; i<c; i++) {
    
    long x, y, radius; std::cin >> x >> y >> radius;
    
    K::Point_2 center(x, y);
    contour tmp = {center, radius*radius};

    K::Point_2 nn = t.nearest_vertex(center) -> point();
    
    if(CGAL::squared_distance(center, nn) < radius*radius) 
      lines.push_back(tmp);
  }
  
  // objective function
  for(int i=0; i<n; i++) {
    for(int j=0; j<m; j++) {
      
      int penalty = 0;
      
      for(std::size_t k=0; k<lines.size(); k++) {
        bool ware = CGAL::squared_distance(lines[k].center, pts[i]) < lines[k].squared_r;
        bool stad = CGAL::squared_distance(lines[k].center, pts[n+j]) < lines[k].squared_r;
        if(ware != stad) penalty++;
      }
      
      // set objective
      lp.set_c(i*m+j, penalty - r[i*m+j]*100);
    }  
  }
  
  // solve the program, using ET as the exact type
  Solution s = CGAL::solve_linear_program(lp, ET());
  
  if(s.is_infeasible()) std::cout << "RIOT!" << std::endl;
  else std::cout << (long) std::floor(- CGAL::to_double(s.objective_value())/100) << std::endl;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  int t; std::cin >> t;
  while(t--) testcase();
}
