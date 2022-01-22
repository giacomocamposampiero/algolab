#include <bits/stdc++.h>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <boost/pending/disjoint_sets.hpp>

using namespace std;

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Delaunay_triangulation_2<K> Triangulation;
typedef K::Point_2 P;
typedef boost::disjoint_sets_with_storage<> Uf;
typedef tuple<long, P, P, bool> TLPB; //bool 0: edge between two trees, bool 1: edge between bone and tree

void testcase(){
  int n; cin >> n;
  int m; cin >> m;
  long s; cin >> s;
  int k; cin >> k;
  
  vector<P> trees;
  map<P,int> idx;
  int x, y;
  for(int i = 0; i < n; i++){
    cin >> x >> y;
    trees.push_back(P(x,y));
    idx[P(x,y)] = i;
  }
  
  Triangulation t;
  t.insert(trees.begin(), trees.end());
  
  Uf ds(n);
  vector<TLPB> edges;
  for(auto e: t.finite_edges()){
    P v1 = e.first->vertex((e.second + 1) % 3)->point();
    P v2 = e.first->vertex((e.second + 2) % 3)->point();
    edges.push_back(TLPB(CGAL::squared_distance(v1, v2), v1, v2, false));
    if(CGAL::squared_distance(v1, v2) <= s && ds.find_set(idx[v1]) != ds.find_set(idx[v2]))
      ds.union_set(ds.find_set(idx[v1]), ds.find_set(idx[v2]));
  }
  
  vector<int> belong(n, 0);
  for(int i = 0; i < m; i++){
    cin >> x >> y;
    P bone(x,y);
    P nearest = t.nearest_vertex(bone)->point();
    if(4*(long)CGAL::squared_distance(bone, nearest) <= s){
      int idxset = ds.find_set(idx[nearest]);
      belong[idxset]++;
    }
    edges.push_back(TLPB(4*(long)CGAL::squared_distance(bone, nearest), bone, nearest, true));
  }
  
  Uf min_rad_set(n);
  long q = 0;
  vector<int> new_belong(n, 0);
  sort(edges.begin(), edges.end());
  
  for(auto e: edges){
    long dist = get<0>(e);
    P v1 = get<1>(e);
    P v2 = get<2>(e);
    bool bone = get<3>(e);
    if(bone){
      new_belong[min_rad_set.find_set(idx[v2])]++;
      if(new_belong[min_rad_set.find_set(idx[v2])] >= k){
        q = dist;
        break;
      }
    }
    else{
      if(min_rad_set.find_set(idx[v1]) != min_rad_set.find_set(idx[v2])){
        int bones1 = new_belong[min_rad_set.find_set(idx[v1])];
        int bones2 = new_belong[min_rad_set.find_set(idx[v2])];
        min_rad_set.union_set(min_rad_set.find_set(idx[v1]), min_rad_set.find_set(idx[v2]));
        new_belong[min_rad_set.find_set(idx[v1])] = bones1+bones2;
        if(bones1+bones2 >= k){
          q = dist;
          break;
        }
      }
    }
  }
  
  cout << *max_element(belong.begin(), belong.end()) << " " << q << endl;
}

int main(){
  ios_base::sync_with_stdio(false);
  int t; cin >> t;
  for(int i = 0; i < t; i++)
    testcase();
  
  return 0;
}