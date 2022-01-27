#include <iostream>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/cycle_canceling.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>
#include <boost/graph/successive_shortest_path_nonnegative_weights.hpp>
#include <boost/graph/find_flow_cost.hpp>

typedef boost::adjacency_list_traits<boost::vecS, boost::vecS, boost::directedS> traits;
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS, boost::no_property,
    boost::property<boost::edge_capacity_t, long,
        boost::property<boost::edge_residual_capacity_t, long,
            boost::property<boost::edge_reverse_t, traits::edge_descriptor,
                boost::property <boost::edge_weight_t, long> > > > > graph; // new! weightmap corresponds to costs

typedef boost::graph_traits<graph>::edge_descriptor             edge_desc;
typedef boost::graph_traits<graph>::out_edge_iterator           out_edge_it; // Iterator
typedef boost::graph_traits<graph>::vertex_descriptor vertex_desc;

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

void testcase() {
  
  int e, w, m, d; std::cin >> e >> w >> m >> d;
  int p, l; std::cin >> p >> l;
  
  graph G(2*(e+w));
  edge_adder adder(G);  
  const vertex_desc v_source = boost::add_vertex(G);
  const vertex_desc v_sink = boost::add_vertex(G);
  const vertex_desc right_constraint = boost::add_vertex(G);
  const vertex_desc left_constraint = boost::add_vertex(G);
  
  for(int i=0; i<m; i++) {
    int u, v, r; std::cin >> u >> v >> r;
    adder.add_edge(u, e+v, 1, r);
  }
  
  for(int i=0; i<e; i++) {
    adder.add_edge(v_source, i, l, 0);
    adder.add_edge(left_constraint, i, w, 0);
  }
  
  for(int i=e; i<e+w; i++) {
    adder.add_edge(i, v_sink, l, 0);
    adder.add_edge(i, right_constraint, e, 0);
  }

  for(int i=0; i<d; i++) {
    int u, v, r; std::cin >> u >> v >> r;
    adder.add_edge((e+w)+u, (e+w)+e+v, 1, r);
  }
  
  if(d>0) {
    for(int i=e+w; i<(e+w)+e; i++) adder.add_edge(left_constraint, i, w, 0);
    for(int i=(2*e+w); i<(2*e+w)+w; i++) adder.add_edge(i, right_constraint, e, 0);
  }
  
  adder.add_edge(v_source, left_constraint, p-e*l, 0);
  adder.add_edge(right_constraint, v_sink, p-w*l,  0);

  int flow = boost::push_relabel_max_flow(G, v_source, v_sink);
  boost::successive_shortest_path_nonnegative_weights(G, v_source, v_sink);
  int cost = boost::find_flow_cost(G);
  
  if(flow == p) std::cout << cost << std::endl;
  else std::cout << "No schedule!" << std::endl;
  
}

int main() {
  std::ios_base::sync_with_stdio(false);
  int t; std::cin >> t;
  while(t--) testcase();
}
