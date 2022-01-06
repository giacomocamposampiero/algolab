#include <iostream>
#include <vector>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/kruskal_min_spanning_tree.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS,
  boost::no_property, boost::property<boost::edge_weight_t, int> >      weighted_graph;
typedef boost::property_map<weighted_graph, boost::edge_weight_t>::type weight_map;
typedef boost::graph_traits<weighted_graph>::edge_descriptor            edge_desc;
typedef boost::graph_traits<weighted_graph>::vertex_descriptor          vertex_desc;

void testcase() {
  
  int n, e, s, a, b; std::cin >> n >> e >> s >> a >> b;
  
  std::vector<weighted_graph> GS(s, weighted_graph(n));
  std::vector<weight_map> weights;
  for(int i=0; i<s; i++) weights.push_back(boost::get(boost::edge_weight, GS[i]));
  
  
  while(e--) {
    int u, v; std::cin >> u >> v;
    for(int i=0; i<s; i++) {
      int w; std::cin >> w;
      edge_desc ed = boost::add_edge(u, v, GS[i]).first; 
      weights[i][ed] = w;
    }
  }
  
  // useless, but read them
  for(int i=0; i<s; i++) std::cin >> e;
  
  // s times Kruskal
  weighted_graph global(n);
  weight_map global_weights = boost::get(boost::edge_weight, global);
  
  for(int i=0; i<s; i++) {
  
    std::vector<edge_desc> mst;
    boost::kruskal_minimum_spanning_tree(GS[i], std::back_inserter(mst));
    
    for(std::vector<edge_desc>::iterator it = mst.begin(); it != mst.end(); ++it) {
      edge_desc ed = boost::add_edge(boost::source(*it, GS[i]), boost::target(*it, GS[i]), global).first; 
      global_weights[ed] = weights[i][*it];
    }
  }
  
  // Dijkstra
  std::vector<int> dist_map(n);

  boost::dijkstra_shortest_paths(global, a,
    boost::distance_map(boost::make_iterator_property_map(
      dist_map.begin(), boost::get(boost::vertex_index, global))));
  
  std::cout << dist_map[b] << std::endl;
  
}

int main() {
  std::ios_base::sync_with_stdio(false);
  int t; std::cin >> t;
  while(t--) testcase();
}
