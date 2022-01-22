#include <bits/stdc++.h>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Exact_predicates_exact_constructions_kernel_with_sqrt.h>
#include <CGAL/Delaunay_triangulation_2.h>

using namespace std;

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Exact_predicates_exact_constructions_kernel_with_sqrt SK;
typedef CGAL::Delaunay_triangulation_2<K> Triangulation;
typedef K::Point_2 P;

long ceil_to_double(const SK::FT& x){
  double a = ceil(CGAL::to_double(x));
  while (a < x) a += 1;
  while (a-1 >= x) a -= 1;
  return (long)a;
}

bool testcase(){
  int n; cin >> n;
  if(n == 0)  return true;
  
  int l, b, r, t;
  cin >> l >> b >> r >> t;
  
  vector<P> points;
  int x, y;
  for(int i = 0; i < n; i++){
    cin >> x >> y;
    points.push_back(P(x,y));
  }
  
  Triangulation tri;
  tri.insert(points.begin(), points.end());
  
  vector<long> times;
  for(auto v: tri.finite_vertex_handles()){
    double bound = min({abs(v->point().x()-l), abs(v->point().x()-r), abs(v->point().y()-b), abs(v->point().y()-t)});
    
    Triangulation::Vertex_circulator circ = tri.incident_vertices(v);
    double bestdist = numeric_limits<double>::max();
    if(circ != 0){
      do{
        if(!tri.is_infinite(circ)){
          bestdist = min(bestdist, CGAL::squared_distance(v->point(), circ->point()));
        }
      } while (++circ != tri.incident_vertices(v));
    }
    
    bestdist = CGAL::sqrt(bestdist)/2;
    bestdist = min(bestdist, bound);
    long tempo = ceil_to_double(CGAL::sqrt(bestdist-0.5));
    times.push_back(tempo);
  }
  
  sort(times.begin(), times.end());
  
  cout << times.front() << " " << times[n/2] << " " << times.back() << endl;
  
  return false;
}

int main(){
  ios_base::sync_with_stdio(false);
  bool end = false;
  while(!end)
    end = testcase();
  
  return 0;
}