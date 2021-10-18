#include <iostream>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef K::Point_2 P;
typedef K::Segment_2 S;

bool contains(std::vector<P> &piece, P &source, P &target);
  
void testcase() {
  int m; std::cin >> m; // m-1 = legs of the hike
  int n; std::cin >> n; // number of map parts
  
  // read hike checkpoints
  std::vector<P> legs(m);
  long x, y;
  for(int i=0; i<m; i++) {
    std::cin >> x; std::cin >> y;
    legs[i] = P(x,y);
  }

  // read map parts
  std::vector<std::vector<P>> map(n, std::vector<P>(6));
  for(int i=0; i<n; i++) {
    for(int j=0; j<6; j++) {
      std::cin >> x; std::cin >> y;
      map[i][j] = P(x,y);
    }
    if(!CGAL::left_turn(map[i][0], map[i][1], map[i][2])) std::swap(map[i][0], map[i][1]);
    if(!CGAL::left_turn(map[i][2], map[i][3], map[i][1])) std::swap(map[i][2], map[i][3]);
    if(!CGAL::left_turn(map[i][4], map[i][5], map[i][1])) std::swap(map[i][4], map[i][5]);
  }
  
  // precompute maps and legs intersections
  std::vector<std::vector<int>> memo(n, std::vector<int>(m, 0));
  for(int i=0; i<n; i++) 
    for(int j=1; j<m; j++) 
      memo[i][j] = contains(map[i], legs[j-1], legs[j]);
  

  // sliding window to optimize the number of map pieces
  int best_l=0, best_u=n-1;
  int low=0, up=0;
  bool cont=false;
  
  while(up<n) {
    // check if the leg i is contained in the current map pieces window
    // if not, increase the upper pointer
    for(int i=1; i<m; i++) {
      cont = false;
      for(int j=low; j<=up; j++) {
        //std::cout << "map " << j << " - check " << i << " res--> ";
        if(memo[j][i]) { cont=true; break; }
      }
      // if one of the checkp is not contained in the interval, it's not okay
      if(!cont) break;
    }
    if(!cont) up++; 
    else {
      if((best_u-best_l) > (up-low)) {
        // better interval, update it
        best_u = up;
        best_l = low;
      }
      low++;
    }
  }
  // std::cout << best_u << ' ' << best_l<<std::endl;
  std::cout << best_u - best_l + 1 << std::endl;
}

bool contains(std::vector<P> &piece, P &source, P &target) {
  bool res =  !CGAL::right_turn(piece[0], piece[1], source) &&
              !CGAL::right_turn(piece[0], piece[1], target) &&
              !CGAL::right_turn(piece[2], piece[3], source) &&
              !CGAL::right_turn(piece[2], piece[3], target) &&
              !CGAL::right_turn(piece[4], piece[5], source) &&
              !CGAL::right_turn(piece[4], piece[5], target);  
  return res;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  int c; std::cin >> c;
  for(int i=0; i<c; i++) testcase();
}
