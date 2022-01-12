#include <iostream>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>

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

int m, n, k, c; 

int in_node(int row, int col) {
  return 2*(row*m + col);
}

int out_node(int row, int col) {
  return 2*(row*m + col) + 1;
}

void testcase() {
  
  std::cin >> m >> n >> k >> c;
  
  graph G(2*n*m);
  edge_adder adder(G);
  const vertex_desc v_source = boost::add_vertex(G);
  const vertex_desc v_sink = boost::add_vertex(G);
  
  for(int i=0; i<n; i++) {
    for(int j=0; j<m; j++) {

      if(i==0) adder.add_edge(out_node(i,j), v_sink, 1); // exit above
      else {
        adder.add_edge(out_node(i,j), in_node(i-1,j), 1); // other hallway above
        adder.add_edge(out_node(i-1,j), in_node(i,j), 1);
      }

      if(j==0) adder.add_edge(out_node(i,j), v_sink, 1); // exit left
      else {
        adder.add_edge(out_node(i,j), in_node(i,j-1), 1); // other hallway left
        adder.add_edge(out_node(i,j-1), in_node(i,j), 1);
      }
      
      if(j==m-1) adder.add_edge(out_node(i,j), v_sink, 1); // exit right
      if(i==n-1) adder.add_edge(out_node(i,j), v_sink, 1); // exit down
    }
  }
  
  for(int i=0; i<n; i++)
    for(int j=0; j<m; j++)
      adder.add_edge(in_node(i,j), out_node(i,j), c);
  
  for(int i=0; i<k; i++) {
    int col, row; std::cin >> col >> row;
    adder.add_edge(v_source, in_node(row,col), 1);
  }

  long flow = boost::push_relabel_max_flow(G, v_source, v_sink);
  std::cout << flow << std::endl;

}

int main() {
  std::ios_base::sync_with_stdio(false);
  int t; std::cin >> t;
  while(t--) testcase();
}
