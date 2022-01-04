#include <bits/stdc++.h>
#include <boost/graph/adjacency_list.hpp>

using namespace std;

typedef boost::adjacency_list<
                              boost::vecS,
                              boost::vecS,
                              boost::directedS,
                              boost::no_property, // no vertex property
                              boost::property<boost::edge_weight_t, int> // edge property (interior)
                              > graph;
typedef boost::graph_traits<graph>::out_edge_iterator out_edge_it;
typedef vector<vector<long>> MAT;

long f(graph &G, MAT &memo, int start, int nmoves){
  if(nmoves == 0)  
    return 0;
  
  if(memo[start][nmoves] != -1) return memo[start][nmoves];
  auto w_map = boost::get(boost::edge_weight, G);
  out_edge_it oe_beg, oe_end;
  long res = -1;
  bool has_out_edges = false;
  for(boost::tie(oe_beg, oe_end) = boost::out_edges(start, G); oe_beg != oe_end; ++oe_beg){
    has_out_edges = true;
    res = max(res, w_map[*oe_beg] + f(G, memo, boost::target(*oe_beg, G), nmoves-1));
  }
  
  if(!has_out_edges)
    res = f(G, memo, 0, nmoves);
  
  memo[start][nmoves] = res;
  return res;
}

void testcase(){
  int n; cin >> n;
  int m; cin >> m;
  long x; cin >> x;
  int k; cin >> k;
  
  graph G(n);
  
  int u, v, p;
  for(int i = 0; i < m; i++){
    cin >> u >> v >> p;
    boost::add_edge(u, v, p, G);
  }
  
  MAT memo(n, vector<long>(k+1, -1));
  for(int moves = 1; moves <= k; moves++){
    long res = f(G, memo, 0, moves);
    if(res >= x){
      cout << moves << endl;
      return;
    }
  }
  
  cout << "Impossible" << endl;
}

int main(){
  ios_base::sync_with_stdio(false);
  int t; cin >> t;
  for(int i = 0; i < t; i++)
    testcase();
  
  return 0;
}