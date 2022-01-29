#include <bits/stdc++.h>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <boost/pending/disjoint_sets.hpp>

using namespace std;

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Delaunay_triangulation_2<K> Triangulation;
typedef K::Point_2 P;
typedef boost::disjoint_sets_with_storage<> Uf;
typedef tuple<long, P, P> TLP;

void testcase(){
  int n; cin >> n;
  int m; cin >> m;
  long p; cin >> p;
  
  vector<P> jammers;
  map<P,int> idx;
  int x, y;
  for(int i = 0; i < n; i++){
    cin >> x >> y;
    jammers.push_back(P(x,y));
    idx[P(x,y)] = i;
  }
  
  Triangulation t;
  t.insert(jammers.begin(), jammers.end());
  
  Uf ds(n);
  vector<TLP> edges;
  //only add edges under the umbrella (length <= p)
  for(auto e = t.finite_edges_begin(); e != t.finite_edges_end(); e++){
    P v1 = e->first->vertex((e->second+1)%3)->point();
    P v2 = e->first->vertex((e->second+2)%3)->point();
    long dist = CGAL::squared_distance(v1, v2);
    edges.push_back(TLP(dist, v1, v2));
    int idx1 = idx[v1];
    int idx2 = idx[v2];
    if(dist <= p && ds.find_set(idx1) != ds.find_set(idx2))
      ds.union_set(ds.find_set(idx1), ds.find_set(idx2));
  }
  
  sort(edges.begin(), edges.end());
  
  Uf dsa(n);
  long a = 0;
  Uf dsb(n);
  long b = 0;
  
  int x0, y0, x1, y1;
  for(int i = 0; i < m; i++){
    cin >> x0 >> y0 >> x1 >> y1;
    P source(x0, y0);
    P target(x1, y1);
    P nsrc = t.nearest_vertex(source)->point();
    P ntrg = t.nearest_vertex(target)->point();
    int idxs = idx[nsrc];
    int idxt = idx[ntrg];
    if((long)4*CGAL::squared_distance(source, nsrc) > p || 
      (long)4*CGAL::squared_distance(target, ntrg) > p)
      cout << "n";
    else{
      if(ds.find_set(idxs) == ds.find_set(idxt)){
        cout << "y";
        b = max(b, 4*(long)CGAL::squared_distance(source, nsrc));
        b = max(b, 4*(long)CGAL::squared_distance(target, ntrg));
        int idxe = 0;
        while(dsb.find_set(idxs) != dsb.find_set(idxt)){
          dsb.union_set(idx[get<1>(edges[idxe])], idx[get<2>(edges[idxe])]);
          b = max(b, get<0>(edges[idxe]));
          idxe++;
        }
      }
      else
        cout << "n";
    }
    a = max(a, 4*(long)CGAL::squared_distance(source, nsrc));
    a = max(a, 4*(long)CGAL::squared_distance(target, ntrg));
    int idxe = 0;
    while(dsa.find_set(idxs) != dsa.find_set(idxt)){
      dsa.union_set(idx[get<1>(edges[idxe])], idx[get<2>(edges[idxe])]);
      a = max(a, get<0>(edges[idxe]));
      idxe++;
    }
  }
  
  cout << endl;
  cout << a << endl;
  cout << b << endl;
}

int main(){
  ios_base::sync_with_stdio(false);
  int t; cin >> t;
  for(int i = 0; i < t; i++)
    testcase();
  
  return 0;
}