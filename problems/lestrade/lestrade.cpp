#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Triangulation_vertex_base_with_info_2.h>
#include <CGAL/Triangulation_face_base_2.h>
#include <boost/pending/disjoint_sets.hpp>
#include <vector>
#include <tuple>
#include <algorithm>
#include <iostream>

#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpz.h>

typedef int IT;
typedef CGAL::Gmpz ET;
typedef CGAL::Quadratic_program<IT> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;

typedef CGAL::Triangulation_vertex_base_with_info_2<int,K>     Vb;
typedef CGAL::Triangulation_face_base_2<K>                     Fb;
typedef CGAL::Triangulation_data_structure_2<Vb,Fb>            Tds;
typedef CGAL::Delaunay_triangulation_2<K,Tds>                  Delaunay;

void testcase() {

  int sherlock, u, v, w; std::cin >> sherlock >> u >> v >> w;
  int a, g; std::cin >> a >> g;

  typedef std::pair<K::Point_2,int> IPoint;
  std::vector<IPoint> points;
  points.reserve(g);
  
  std::vector<int> where(g, 0);
  std::vector<int> whom(g, 0);
  std::vector<int> how(g, 0);
  
  for (int i = 0; i < g; ++i) {
    int x, y; std::cin >> x >> y >> where[i] >> whom[i] >> how[i];
    points.emplace_back(K::Point_2(x, y), i);
  }

  Delaunay t;
  t.insert(points.begin(), points.end());

  std::vector<int> min_cost(g, 4000);
  
  for (int i = 0; i < a; ++i) {
    int x, y, z; std::cin >> x >> y >> z;
    int nn = t.nearest_vertex(K::Point_2(x, y)) -> info();
    min_cost[nn] = std::min(min_cost[nn], z);
  }

  Program lp (CGAL::SMALLER, true, 0, true, 24); 
  
  int var = 0;
  for(int hi=0; hi<g; hi++) {
    if(min_cost[hi] != 4000) {
      lp.set_a(var, 0, -where[hi]); 
      lp.set_a(var, 1, -whom[hi]);
      lp.set_a(var, 2, -how[hi]);
      lp.set_c(var++, min_cost[hi]);
    }
  }
  
  lp.set_b(0, -u);
  lp.set_b(1, -v);
  lp.set_b(2, -w);
        
  Solution s = CGAL::solve_linear_program(lp, ET());
  
  if (s.objective_value() > sherlock || s.is_infeasible()) std::cout << 'H' << std::endl;
  else std::cout << 'L' << std::endl;
  
}

int main() {
  std::ios_base::sync_with_stdio(false);
  int t; std::cin >> t;
  while(t--) testcase();
}
