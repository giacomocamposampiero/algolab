#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
// BGL includes
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>
#include <boost/tuple/tuple.hpp>

// BGL graph definitions
// =====================
// Graph Type with nested interior edge properties for Flow Algorithms
typedef  boost::adjacency_list_traits<boost::vecS, boost::vecS, boost::directedS> traits;
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS, boost::no_property,
  boost::property<boost::edge_capacity_t, long,
    boost::property<boost::edge_residual_capacity_t, long,
      boost::property<boost::edge_reverse_t, traits::edge_descriptor> > > >  graph;
// Interior Property Maps
typedef  boost::graph_traits<graph>::edge_descriptor      edge_desc;
typedef  boost::graph_traits<graph>::vertex_descriptor      vertex_desc;
typedef  boost::graph_traits<graph>::out_edge_iterator      out_edge_it;

// Custom Edge Adder Class, that holds the references
// to the graph, capacity map and reverse edge map
// ===================================================
class edge_adder {
 graph &G;

 public:
  explicit edge_adder(graph &G) : G(G) {}

  void add_edge(int from, int to, long capacity) {
    auto c_map = boost::get(boost::edge_capacity, G);
    auto r_map = boost::get(boost::edge_reverse, G);
    const edge_desc e = boost::add_edge(from, to, G).first;
    const edge_desc rev_e = boost::add_edge(to, from, G).first;
    c_map[e] = capacity;
    c_map[rev_e] = 0; // reverse edge has no capacity!
    r_map[e] = rev_e;
    r_map[rev_e] = e;
  }
};

int N; 

void add_knight(std::vector<int> &chess, edge_adder &adder, int i, int j) {
  
  if(i > 0   && j < N-2 && chess[(i-1)*N + j+2]) adder.add_edge(i*N+j, (i-1)*N + j+2, 1);
  if(i > 0   && j > 1   && chess[(i-1)*N + j-2]) adder.add_edge(i*N+j, (i-1)*N + j-2, 1);
  if(i < N-1 && j > 1   && chess[(i+1)*N + j-2]) adder.add_edge(i*N+j, (i+1)*N + j-2, 1);
  if(i < N-1 && j < N-2 && chess[(i+1)*N + j+2]) adder.add_edge(i*N+j, (i+1)*N + j+2, 1);
  
  if(i > 1   && j < N-1 && chess[(i-2)*N + j+1]) adder.add_edge(i*N+j, (i-2)*N + j+1, 1);
  if(i > 1   && j > 0   && chess[(i-2)*N + j-1]) adder.add_edge(i*N+j, (i-2)*N + j-1, 1);
  if(i < N-2 && j < N-1 && chess[(i+2)*N + j+1]) adder.add_edge(i*N+j, (i+2)*N + j+1, 1);
  if(i < N-2 && j > 0   && chess[(i+2)*N + j-1]) adder.add_edge(i*N+j, (i+2)*N + j-1, 1);
  
}

void testcase() {

  std::cin >> N;
  graph G(N*N);
  edge_adder adder(G);
  auto rc_map = boost::get(boost::edge_residual_capacity, G);

  const vertex_desc v_source = boost::add_vertex(G);
  const vertex_desc v_sink = boost::add_vertex(G);
  
  std::vector<int> chess(N*N, 0);
  for(int i=0; i<N*N; i++) std::cin >> chess[i];
  
  for(int i=0; i<N; i++) {
    for(int j=0; j<N; j++) {
      if(chess[i*N+j] == 0) continue;
      if((i+j)%2 == 0) {
        add_knight(chess, adder, i, j);
        adder.add_edge(v_source, i*N+j, 1);
      } else adder.add_edge(i*N+j, v_sink, 1);
    }
  }

  // Find a min cut via maxflow
  boost::push_relabel_max_flow(G, v_source, v_sink);

  // BFS to find vertex set S
  std::vector<int> vis(N*N+2, false); // visited flags
  std::queue<int> Q; // BFS queue (from std:: not boost::)
  vis[v_source] = true; // Mark the source as visited
  Q.push(v_source);
  while (!Q.empty()) {
    const int u = Q.front(); Q.pop();
    out_edge_it ebeg, eend;
    for (boost::tie(ebeg, eend) = boost::out_edges(u, G); ebeg != eend; ++ebeg) {
      const int v = boost::target(*ebeg, G);
      // Only follow edges with spare capacity
      if (rc_map[*ebeg] == 0 || vis[v]) continue;
      vis[v] = true;
      Q.push(v);
    }
  }
  
  int maxis = 0;
  
  for(int i = 0; i < N; i++) 
    for(int j = 0; j < N; j++) 
      if(chess[i*N+j] && ((i+j)%2 != vis[i*N+j])) maxis++;
    

  std::cout << maxis << std::endl;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  int t; std::cin >> t;
  while(t--) testcase();
}
