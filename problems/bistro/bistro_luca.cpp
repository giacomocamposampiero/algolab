#include <bits/stdc++.h>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>

using namespace std;

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Delaunay_triangulation_2<K> Triangulation;
typedef K::Point_2 P;

bool testcase(){
  int n; cin >> n;
  if(n == 0)  return true;
  
  vector<P> points;
  int x, y;
  for(int i = 0; i < n; i++){
    cin >> x >> y;
    points.push_back(P(x,y));
  }
  
  Triangulation t;
  t.insert(points.begin(), points.end());
  
  int m; cin >> m;
  for(int i = 0; i < m; i++){
    cin >> x >> y;
    P newp(x,y);
    P nearest = t.nearest_vertex(newp)->point();
    cout << (long)CGAL::squared_distance(newp, nearest) << endl;
  }
  
  return false;
}

int main(){
  ios_base::sync_with_stdio(false);
  bool end = false;
  while(!end)
    end = testcase();
  
  return 0;
}