#include <bits/stdc++.h>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>

using namespace std;

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef K::Point_2 Point;
typedef K::Ray_2 Ray;
typedef K::Segment_2 Segment;

int main(){
  ios_base::sync_with_stdio(false);
  int n; cin >> n;
  while(n != 0){
    long x, y, a, b;
    cin >> x >> y >> a >> b;
    Ray ray(Point(x,y), Point(a,b));
    
    bool intersect = false;
    long r, s, t, u;
    for(int i = 0; i < n; i++){
      cin >> r >> s >> t >> u;
      Segment seg(Point(r, s), Point(t, u));
      if(CGAL::do_intersect(ray, seg)){
        intersect = true;
        i++;
        while(i < n){ //clean input
          cin >> r >> s >> t >> u;
          i++;
        }
      }
    }
    
    if(intersect)
      cout << "yes" << endl;
    else
      cout << "no" << endl;
    
    cin >> n;
  }
  
  return 0;
}