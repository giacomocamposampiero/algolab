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

void testcase() {
  
  int h, w; std::cin >> h >> w;
  
  graph G(351+26);
  edge_adder adder(G);
  const vertex_desc v_source = boost::add_vertex(G);
  const vertex_desc v_sink = boost::add_vertex(G);
  
  std::vector<int> target(26, 0);
  std::string note; std::cin >> note;
  for(std::size_t i=0; i<note.size(); i++) {
    int index = ((int) note[i]) - 65;
    target[index]++;
  }
  for(int i=0; i<26; i++) adder.add_edge(351 + i, v_sink, target[i]);
  
  std::vector<std::vector<int>> front(h, std::vector<int>(w, 0));
  for(int i=0; i<h; i++) {
    for(int j=0; j<w; j++) {
      char c; std::cin >> c;
      front[i][j] = ((int) c) - 65;
    }
  }
  std::vector<std::vector<int>> back(h, std::vector<int>(w, 0));
  for(int i=0; i<h; i++) {
    for(int j=0; j<w; j++) {
      char c; std::cin >> c;
      back[i][j] = ((int) c) - 65;
    }
  }
  
  std::vector<std::vector<int>> source(26, std::vector<int>(26,0));
  for(int i=0; i<h; i++) {
    for(int j=0; j<w; j++) {
        int a = std::max(front[i][j], back[i][w-j-1]);
        int b = std::min(back[i][w-j-1], front[i][j]);
        source[a][b]++;
      }
    }
  
  int count = 0;
  for(int i=0; i<26; i++) {
    for(int j=0; j<26; j++) {
      if(source[i][j] != 0) {
        adder.add_edge(v_source, count, source[i][j]);
        adder.add_edge(count, 351 + i, source[i][j]);
        adder.add_edge(count, 351 + j, source[i][j]); 
        count++;
      }
    }
  }
  
  std::size_t flow = boost::push_relabel_max_flow(G, v_source, v_sink);
  if(flow == note.size()) std::cout << "Yes" << std::endl;
  else std::cout << "No" << std::endl; 
}

int main() {
  std::ios_base::sync_with_stdio(false);
  int t; std::cin >> t;
  while(t--) testcase();
}
