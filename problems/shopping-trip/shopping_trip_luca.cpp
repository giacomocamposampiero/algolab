#include <iostream>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>

using namespace std;

typedef boost::adjacency_list_traits<boost::vecS, boost::vecS, boost::directedS> traits;
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS, boost::no_property,
                              boost::property<boost::edge_capacity_t, long,
                              boost::property<boost::edge_residual_capacity_t, long,
                              boost::property<boost::edge_reverse_t, traits::edge_descriptor>>>> graph;
typedef traits::vertex_descriptor vertex_desc;
typedef traits::edge_descriptor edge_desc;
typedef boost::graph_traits<graph>::out_edge_iterator out_edge_it;

class edge_adder {
  graph &G;
  public:
    explicit edge_adder(graph &G) : G(G) {}
    
  void add_edge(int from, int to, long capacity) {
    auto c_map = boost::get(boost::edge_capacity, G);
    auto r_map = boost::get(boost::edge_reverse, G);
    const auto e = boost::add_edge(from, to, G).first;
    const auto rev_e = boost::add_edge(to, from, G).first;
    c_map[e] = capacity;
    c_map[rev_e] = 0; // reverse edge has no capacity!
    r_map[e] = rev_e;
    r_map[rev_e] = e;
  }
};

void testcase(){
  int n, m, s;
  cin >> n >> m >> s;
  
  graph G(n);
  edge_adder adder(G);
  
  vertex_desc v_sink = boost::add_vertex(G);
  int si;
  for(int i = 0; i < s; i++){
    cin >> si;
    adder.add_edge(si, v_sink, 1);
  }
  
  int u, v;
  for(int i = 0; i < m; i++){
    cin >> u >> v;
    adder.add_edge(u, v, 1);
    adder.add_edge(v, u, 1);
  }
  
  long flow = boost::push_relabel_max_flow(G, 0, v_sink);
  if(flow == s)
    cout << "yes" << endl;
  else
    cout << "no" << endl;
}

int main(){
  ios_base::sync_with_stdio(false);
  int T; cin >> T;
  for(int i = 0; i < T; i++)
    testcase();
    
  return 0;
}