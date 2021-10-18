#include <iostream>
#include <vector>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/kruskal_min_spanning_tree.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>

typedef std::vector<int> neighbor_list; 
typedef std::vector<neighbor_list> cpp_graph;
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS,
  boost::no_property, boost::property<boost::edge_weight_t, int>> weighted_graph;
typedef boost::property_map<weighted_graph, boost::edge_weight_t>::type weight_map;
typedef boost::graph_traits<weighted_graph>::edge_descriptor edge_desc;

void testcase() {

  int n; std::cin >> n;
  int m; std::cin >> m;
  
  weighted_graph G(n);
  weight_map weights = boost::get(boost::edge_weight, G);
  edge_desc e;
  
  // build the graph
  for(int i=0; i<m; i++) {
    int x; std::cin >> x;
    int y; std::cin >> y;
    int w; std::cin >> w;
    e = boost::add_edge(x, y, G).first; weights[e]=w;
  }
  
  // find weigth of minimum spanning tree
  int sum = 0;
  std::vector<edge_desc> mst; // vector to store MST edges (not a property map!)
  boost::kruskal_minimum_spanning_tree(G, std::back_inserter(mst));
  for(std::vector<edge_desc>::iterator it = mst.begin(); it != mst.end(); ++it)
    sum += boost::get(weights, *it);
  
  // find maximum distance from vertex 0
  std::vector<int> dist_map(n);
  boost::dijkstra_shortest_paths(G, 0, boost::distance_map(boost::make_iterator_property_map(dist_map.begin(), boost::get(boost::vertex_index, G))));
  
  int max = -1;
  for(int i=0; i<n; i++)
    if(dist_map[i] > max) max = dist_map[i];
    
  // output
  std::cout << sum << ' ' << max << std::endl;
}

int main() {
  int t; std::cin >> t;
  for(int i=0; i<t; i++) testcase();
}
