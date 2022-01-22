#include <iostream>
#include <limits>
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
  int n; cin >> n;
  int m; cin >> m;
  
  graph G(n);
  edge_adder adder(G);

  int a, b, c;
  for(int i = 0; i < m; i++){
    cin >> a >> b >> c;
    adder.add_edge(a, b, c);
  }
  
  long flow, minflow = numeric_limits<long>::max();
  //I get figure 0
  for(int i = 1; i < n; i++){
    flow = boost::push_relabel_max_flow(G, 0, i);
    minflow = min(minflow, flow);
  }
  //I don't get figure 0
  for(int i = 1; i < n; i++){
    flow = boost::push_relabel_max_flow(G, i, 0);
    minflow = min(minflow, flow);
  }
  
  cout << minflow << endl;
}

int main(){
  ios_base::sync_with_stdio(false);
  int t; cin >> t;
  for(int i = 0; i < t; i++){
    testcase();
  }
  
  return 0;
}
