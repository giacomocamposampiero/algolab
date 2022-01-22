#include <bits/stdc++.h>
#include <boost/pending/disjoint_sets.hpp>

using namespace std;

typedef boost::disjoint_sets_with_storage<> Uf;
typedef tuple<int,int,int> EDGE;

int sec_mst(vector<EDGE> &edges, vector<int> &idx_mst, int disc_idx, int n){
  Uf mst(n);
  int count = 0;
  int tot = 0;
  
  int u, v;
  for(int i = 0; i < edges.size(); i++){
    if(i != disc_idx){
      u = get<1>(edges[i]);
      v = get<2>(edges[i]);
      if(mst.find_set(u) != mst.find_set(v)){
        mst.union_set(mst.find_set(u), mst.find_set(v));
        tot += get<0>(edges[i]);
        count++;
        idx_mst.push_back(i); //the i-th edge is part of the MST
      }
    }
    if(count == n-1)  break;
  }
  
  return tot;
}

void testcase(){
  int n; cin >> n;
  int i; cin >> i;
  
  vector<EDGE> edges;
  int c;
  for(int j = 0; j < n-1; j++){
    for(int k = 1; k < n-j; k++){
      cin >> c;
      edges.push_back(EDGE(c, j, j+k));
    }
  }
  
  sort(edges.begin(), edges.end());
  
  //first compute the edges that are in the MST
  vector<int> idx_mst;
  sec_mst(edges, idx_mst, -1, n); //-1 because I don't discard any edges now
  //remove one edge of the MST at a time and obtain the second-best MST
  int best = numeric_limits<int>::max();
  for(int i = 0; i <= n-1; i++){
    best = min(best, sec_mst(edges, idx_mst, idx_mst[i], n));
  }
  
  cout << best << endl;
}

int main(){
  ios_base::sync_with_stdio(false);
  int t; cin >> t;
  for(int i = 0; i < t; i++)
    testcase();
  
  return 0;
}