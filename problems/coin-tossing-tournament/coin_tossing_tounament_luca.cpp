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
  
  graph G(m+n);
  edge_adder adder(G);
  
  const vertex_desc v_source = boost::add_vertex(G);
  int a, b, c;
  for(int i = 0; i < m; i++){
    adder.add_edge(v_source, i, 1);
    cin >> a >> b >> c;
    switch(c){
      case 1:
        adder.add_edge(i, m+a, 1);
        break;
      case 2:
        adder.add_edge(i, m+b, 1);
        break;
      case 0:
        adder.add_edge(i, m+a, 1);
        adder.add_edge(i, m+b, 1);
        break;
    }
  }
  
  const vertex_desc v_sink = boost::add_vertex(G);
  int s;
  int sum = 0;
  for(int i = 0; i < n; i++){
    cin >> s;
    sum += s;
    adder.add_edge(i+m, v_sink, s);
  }
  
  long flow = boost::push_relabel_max_flow(G, v_source, v_sink);
  if(flow == sum && flow == m)
    cout << "yes" << endl;
  else
    cout << "no" << endl;
}

int main(){
  ios_base::sync_with_stdio(false);
  int t; cin >> t;
  for(int i = 0; i < t; i++)
    testcase();
    
  return 0;
}