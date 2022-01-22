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
typedef boost::graph_traits<graph>::edge_iterator           edge_it;

// Custom edge adder class
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
  int e, w, m, d;
  cin >> e >> w >> m >> d;
  int p, l;
  cin >> p >> l;
  
  graph G(2*e+2*w);
  edge_adder adder(G);
  
  const vertex_desc v_source = boost::add_vertex(G);
  const vertex_desc prefilter = boost::add_vertex(G);
  const vertex_desc postfilter = boost::add_vertex(G);
  const vertex_desc v_sink = boost::add_vertex(G);
  int u, v, r;
  for(int i = 0; i < m; i++){
    cin >> u >> v >> r;
    adder.add_edge(u, v+2*e, 1, r);
  }
  
  for(int i = 0; i < d; i++){
    cin >> u >> v >> r;
    adder.add_edge(u+e, v+2*e+w, 1, r);
  }
  
  adder.add_edge(v_source, prefilter, p-e*l, 0);
  for(int i = 0; i < e; i++){
    adder.add_edge(v_source, i, l, 0);
    adder.add_edge(prefilter, i, numeric_limits<int>::max(), 0);
    adder.add_edge(prefilter, i+e, numeric_limits<int>::max(), 0);
  }
  
  for(int i = 0; i < w; i++){
    adder.add_edge(i+2*e, v_sink, l, 0);
    adder.add_edge(i+2*e, postfilter, numeric_limits<int>::max(), 0);
    adder.add_edge(i+2*e+w, postfilter, numeric_limits<int>::max(), 0);
  }
  adder.add_edge(postfilter, v_sink, p-w*l, 0);
  
  auto c_map = boost::get(boost::edge_capacity, G);
  auto rc_map = boost::get(boost::edge_residual_capacity, G);

  boost::successive_shortest_path_nonnegative_weights(G, v_source, v_sink);
  int cost = boost::find_flow_cost(G);
  int s_flow = 0;
  out_edge_it e_beg, e_end;
  for(boost::tie(e_beg, e_end) = boost::out_edges(boost::vertex(v_source,G), G); e_beg != e_end; ++e_beg)
    s_flow += c_map[*e_beg] - rc_map[*e_beg];
  
  if(s_flow != p)
    cout << "No schedule!" << endl;
  else
    cout << cost << endl;
}

int main(){
  ios_base::sync_with_stdio(false);
  int t; cin >> t;
  for(int i = 0; i < t; i++)
    testcase();
    
  return 0;
}