#include <bits/stdc++.h>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/successive_shortest_path_nonnegative_weights.hpp>
#include <boost/graph/find_flow_cost.hpp>

using namespace std;

typedef boost::adjacency_list_traits<boost::vecS, boost::vecS, boost::directedS> traits;
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS, boost::no_property,
    boost::property<boost::edge_capacity_t, long,
        boost::property<boost::edge_residual_capacity_t, long,
            boost::property<boost::edge_reverse_t, traits::edge_descriptor,
                boost::property <boost::edge_weight_t, long> > > > > graph; // new! weightmap corresponds to costs

typedef boost::graph_traits<graph>::edge_descriptor             edge_desc;
typedef boost::graph_traits<graph>::vertex_descriptor             vertex_desc;
typedef boost::graph_traits<graph>::out_edge_iterator           out_edge_it; // Iterator

class edge_adder {
 graph &G;

 public:
  explicit edge_adder(graph &G) : G(G) {}
  void add_edge(int from, int to, long capacity, long cost) {
    auto c_map = boost::get(boost::edge_capacity, G);
    auto r_map = boost::get(boost::edge_reverse, G);
    auto w_map = boost::get(boost::edge_weight, G); // new!
    const edge_desc e = boost::add_edge(from, to, G).first;
    const edge_desc rev_e = boost::add_edge(to, from, G).first;
    c_map[e] = capacity;
    c_map[rev_e] = 0; // reverse edge has no capacity!
    r_map[e] = rev_e;
    r_map[rev_e] = e;
    w_map[e] = cost;   // new assign cost
    w_map[rev_e] = -cost;   // new negative cost
  }
};

void testcase(){
  int c, g, b, k, a;
  cin >> c >> g >> b >> k >> a;
  
  graph G(c);
  edge_adder adder(G);
  
  int x, y, d, e;
  for(int i = 0; i < g; i++){
    cin >> x >> y >> d >> e;
    adder.add_edge(x, y, e, d);
  }
  
  const vertex_desc v_source = boost::add_vertex(G);
  adder.add_edge(v_source, k, 0, 0);
  
  auto c_map = boost::get(boost::edge_capacity, G);
  auto rc_map = boost::get(boost::edge_residual_capacity, G);
  
  edge_desc start = boost::edge(v_source, k, G).first;
  int left = 0, right = pow(10,7);
  int maxflow = -1;
  while(left <= right){
    int mid = (left+right)/2;
    c_map[start] = mid;
    boost::successive_shortest_path_nonnegative_weights(G, v_source, a);
    long cost = boost::find_flow_cost(G);
    if(cost <= b){
      left = mid+1;
      int s_flow = c_map[start] - rc_map[start];
      maxflow = max(maxflow, s_flow);
    }
    else
      right = mid-1;
  }
  
  cout << maxflow << endl;
  
}

int main(){
  ios_base::sync_with_stdio(false);
  int t; cin >> t;
  for(int i = 0; i < t; i++)
    testcase();
    
  return 0;
}