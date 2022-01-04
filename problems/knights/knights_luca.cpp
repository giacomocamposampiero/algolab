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
typedef boost::graph_traits<graph>::edge_iterator edge_it;

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
  int m, n, k, c;
  cin >> m >> n >> k >> c;
  
  graph G(2*m*n); //modify
  edge_adder adder(G);
  const int size = m*n;
  
  vertex_desc v_source = boost::add_vertex(G);
  vertex_desc v_sink = boost::add_vertex(G);
  for(int i = 0; i < n; i++){
    for(int j = 0; j < m; j++){
      adder.add_edge(i*m+j, i*m+j+size, c);
      if(j < m-1){
        adder.add_edge(i*m+j+size, i*m+j+1, 1);
        adder.add_edge(i*m+j+1+size, i*m+j, 1);
      }
      if(i < n-1){
        adder.add_edge(i*m+j+size, (i+1)*m+j, 1);
        adder.add_edge((i+1)*m+j+size, i*m+j, 1);
      }
      if(i == 0 || i == n-1)
        adder.add_edge(i*m+j+size, v_sink, 1);
      if(j == 0 || j == m-1)
        adder.add_edge(i*m+j+size, v_sink, 1);
    }
  }
  
  int x, y;
  for(int i = 0; i < k; i++){
    cin >> x >> y;
    adder.add_edge(v_source, y*m+x, 1);
  }
  
  long flow = boost::push_relabel_max_flow(G, v_source, v_sink);
  
  cout << flow << endl;
}

int main(){
  ios_base::sync_with_stdio(false);
  int t; cin >> t;
  for(int i = 0; i < t; i++){
    testcase();
  }
    
  return 0;
}