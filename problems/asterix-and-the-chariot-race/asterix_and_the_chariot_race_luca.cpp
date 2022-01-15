#include <bits/stdc++.h>
#include <boost/graph/adjacency_list.hpp>

using namespace std;

typedef boost::adjacency_list<boost::vecS,
                              boost::vecS,
                              boost::directedS> graph;
typedef boost::graph_traits<graph>::out_edge_iterator out_edge_it;
typedef vector<vector<vector<int>>> TRIMAT;

int f(graph &G, TRIMAT &memo, vector<int> &costs, int start, bool covered, bool compulsory){
  out_edge_it oe_beg, oe_end;
  boost::tie(oe_beg, oe_end) = boost::out_edges(start, G);
  
  if(oe_beg == oe_end){  //no children
    if(covered) return 0;
    //else
    return costs[start];
  }
  
  if(memo[covered][compulsory][start] != -1)  return memo[covered][compulsory][start];
  int cov = costs[start];
  for(boost::tie(oe_beg, oe_end) = boost::out_edges(start, G); oe_beg != oe_end; ++oe_beg){
    cov += f(G, memo, costs, boost::target(*oe_beg, G), true, false);
  }
  
  if(compulsory){
    memo[covered][compulsory][start] = cov;
    return cov;
  }
  
  int not_cov = 0;
  for(boost::tie(oe_beg, oe_end) = boost::out_edges(start, G); oe_beg != oe_end; ++oe_beg){
    not_cov += f(G, memo, costs, boost::target(*oe_beg, G), false, false);
  }
  
  if(covered){
    memo[covered][compulsory][start] = min(cov, not_cov);
    return min(cov, not_cov);
  }
  
  int one = cov;
  for(boost::tie(oe_beg, oe_end) = boost::out_edges(start, G); oe_beg != oe_end; ++oe_beg){
    one = min(one, not_cov - f(G, memo, costs, boost::target(*oe_beg, G), false, false) + f(G, memo, costs, boost::target(*oe_beg, G), false, true));
  }
  
  memo[covered][compulsory][start] = one;
  return one;
}

void testcase(){
  int n; cin >> n;
  
  graph G(n);
  
  int u, v;
  for(int i = 0; i < n-1; i++){
    cin >> u >> v;
    boost::add_edge(u, v, G);
  }
  
  vector<int> costs;
  int c;
  for(int i = 0; i < n; i++){
    cin >> c;
    costs.push_back(c);
  }
  
  TRIMAT memo(2, vector<vector<int>>(2, vector<int>(n, -1)));
  int res = f(G, memo, costs, 0, false, false);
  
  cout << res << endl;
}

int main(){
  ios_base::sync_with_stdio(false);
  int t; cin >> t;
  for(int i = 0; i < t; i++)
    testcase();
  
  return 0;
}