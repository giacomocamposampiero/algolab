#include <iostream>
#include <vector>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/graph/kruskal_min_spanning_tree.hpp>

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS,
  boost::no_property, boost::property<boost::edge_weight_t, int> >      weighted_graph;
typedef boost::property_map<weighted_graph, boost::edge_weight_t>::type weight_map;
typedef boost::graph_traits<weighted_graph>::edge_descriptor            edge_desc;
typedef boost::graph_traits<weighted_graph>::vertex_descriptor          vertex_desc;

void testcase() {
  
  int n, m; std::cin >> n >> m;
  weighted_graph G(n);
  weight_map weights = boost::get(boost::edge_weight, G);

  edge_desc e;
  for(int i=0; i<m; i++) {
    int u, v, w; std::cin >> u >> v >> w;
     e = boost::add_edge(u, v, G).first; 
     weights[e]=w;
  }
  
  // Kruskal
  int sum = 0;
  std::vector<edge_desc> mst;   
  boost::kruskal_minimum_spanning_tree(G, std::back_inserter(mst));
  for (std::vector<edge_desc>::iterator it = mst.begin(); it != mst.end(); ++it) 
    sum += weights[*it];
  
  // Dijkstra
  std::vector<int> dist_map(n);
  boost::dijkstra_shortest_paths(G, 0,
    boost::distance_map(boost::make_iterator_property_map(
      dist_map.begin(), boost::get(boost::vertex_index, G))));
  int max = -1;
  for(int i=0; i<n; i++) max = std::max(max, dist_map[i]);
  
  std::cout << sum << ' ' << max << std::endl;
  
}

int main() {
  std::ios_base::sync_with_stdio(false);
  int t; std::cin >> t;
  while(t--) testcase();
}
