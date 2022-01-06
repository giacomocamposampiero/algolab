#include <bits/stdc++.h>
#include <CGAL/Exact_predicates_exact_constructions_kernel.h>

using namespace std;

typedef CGAL::Exact_predicates_exact_constructions_kernel K;
typedef K::Point_2 P;
typedef K::Segment_2 S;
typedef K::Ray_2 R;

long floor_to_double(const K::FT& x)
{
  double a = floor(CGAL::to_double(x));
  while (a > x) a -= 1;
  while (a+1 <= x) a += 1;
  return (long)a;
}

bool testcase(){
  int n; cin >> n;
  if(n == 0)  return true;
  
  long x, y, a, b;
  cin >> x >> y >> a >> b;
  R ray(P(x,y), P(a,b));
  
  S myseg;
  vector<S> segs;
  long r, s, t, u;
  for(int i = 0; i < n; i++){
    cin >> r >> s >> t >> u;
    S seg(P(r,s), P(t,u));
    segs.push_back(seg);
  }
  
  random_shuffle(segs.begin(), segs.end()); //avoid adversarial input
  
  //if an intersection is found, cut the ray so to avoid useless intersection computations (with more distant points)
  bool intersection = false;
  bool at_least_one = false;
  P best;
  for(int i = 0; i < n; i++){
    S seg = segs[i];
    if(at_least_one) intersection = CGAL::do_intersect(seg, myseg);
    else intersection = CGAL::do_intersect(seg, ray);
    
    if(intersection){
      auto o = at_least_one ? CGAL::intersection(seg, myseg) : CGAL::intersection(seg, ray);
      at_least_one = true;
      if(const P* op = boost::get<P>(&*o)){
        myseg = S(P(x,y), *op);
        best = *op;
      }
      else if(const S* os = boost::get<S>(&*o)){
        K::FT dist_source = CGAL::squared_distance(P(x,y), os->source());
        K::FT dist_target = CGAL::squared_distance(P(x,y), os->target());
        P nearest;
        if(dist_source < dist_target)
          nearest = os->source();
        else
          nearest = os->target();
        myseg = S(P(x,y), nearest);
        best = nearest;
      }
      else
        throw runtime_error("Strange");
    }
  }
  
  if(at_least_one)
    cout << floor_to_double(best.x()) << " " << floor_to_double(best.y()) << endl;
  else
    cout << "no" << endl;
  
  return false;
}

int main(){
  ios_base::sync_with_stdio(false);
  bool end = false;
  while(!end)
    end = testcase();
  
  return 0;
}