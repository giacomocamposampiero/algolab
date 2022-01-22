#include <iostream>
#include <vector>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/successive_shortest_path_nonnegative_weights.hpp>
#include <boost/graph/find_flow_cost.hpp>

using namespace std;

typedef boost::adjacency_list_traits<boost::vecS, boost::vecS, boost::directedS> traits;
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS, boost::no_property,
                              boost::property<boost::edge_capacity_t, long,
                              boost::property<boost::edge_residual_capacity_t, long,
                              boost::property<boost::edge_reverse_t, traits::edge_descriptor,
                              boost::property <boost::edge_weight_t, long> > > > > graph;
typedef boost::graph_traits<graph>::edge_descriptor edge_desc;
typedef boost::graph_traits<graph>::vertex_descriptor vertex_desc;
typedef boost::graph_traits<graph>::out_edge_iterator out_edge_it;

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
      w_map[e] = cost; // new assign cost
      w_map[rev_e] = -cost; // new negative cost
    }
};

void testcase(){
  int N, M, S;
  cin >> N >> M >> S;
  
  graph G(N+M+S);
  edge_adder adder(G);
  
  const vertex_desc v_sink = boost::add_vertex(G);
  int l;
  for(int i = 0; i < S; i++){
    cin >> l;
    adder.add_edge(N+M+i, v_sink, l, 0);
  }
  
  int s;
  for(int i = 0; i < M; i++){
    cin >> s;
    adder.add_edge(N+i, N+M+s-1, 1, 0); //-1 because s starts from 1
  }
  
  const vertex_desc v_source = boost::add_vertex(G);
  int b;
  for(int i = 0; i < N; i++){
    adder.add_edge(v_source, i, 1, 0);
    for(int j = 0; j < M; j++){
      cin >> b;
      adder.add_edge(i, j+N, 1, -b+100);
    }
  }
  
  auto c_map = boost::get(boost::edge_capacity, G);
  auto rc_map = boost::get(boost::edge_residual_capacity, G);

  boost::successive_shortest_path_nonnegative_weights(G, v_source, v_sink);
  int cost = boost::find_flow_cost(G);
  int s_flow = 0;
  out_edge_it e_beg, e_end;
  for(boost::tie(e_beg, e_end) = boost::out_edges(boost::vertex(v_source,G), G); e_beg != e_end; ++e_beg) {
    s_flow += c_map[*e_beg] - rc_map[*e_beg];
  }
  
  cost = -(cost-s_flow*100);
  
  cout << s_flow << " " << cost << endl;
  
}

int main(){
  ios_base::sync_with_stdio(false);
  int T; cin >> T;
  for(int i = 0; i < T; i++)
    testcase();
    
  return 0;
}