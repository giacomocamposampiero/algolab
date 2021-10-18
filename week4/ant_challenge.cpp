#include <iostream>
#include <vector>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/kruskal_min_spanning_tree.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS,
  boost::no_property, boost::property<boost::edge_weight_t, int>> weighted_graph;
typedef boost::property_map<weighted_graph, boost::edge_weight_t>::type weight_map;
typedef boost::graph_traits<weighted_graph>::edge_descriptor edge_desc;

void testcase() {
  
  int n; std::cin >> n;
  int e; std::cin >> e;
  int s; std::cin >> s;
  int a; std::cin >> a;
  int b; std::cin >> b;

  std::vector<weighted_graph> G(s, weighted_graph(n));
  std::vector<weight_map> weights;
  for(int i=0; i<s; i++) weights.push_back(boost::get(boost::edge_weight, G[i]));
  edge_desc ed;
  
  for(int i=0; i<e; i++) {
    int t1; std::cin >> t1; 
    int t2; std::cin >> t2;
    for(int j=0; j<s; j++) {
      int w; std::cin >> w;
      ed = (boost::add_edge(t1, t2, G[j])).first; weights[j][ed] = w;
    }
  }
  
  weighted_graph forest(n);
  weight_map f_wei = boost::get(boost::edge_weight, forest);
  for(int i=0; i<s; i++) {
    int hive; std::cin >> hive;
    std::vector<edge_desc> mst;
    boost::kruskal_minimum_spanning_tree(G[i], std::back_inserter(mst));
    for(std::vector<edge_desc>::iterator it = mst.begin(); it != mst.end(); ++it) { 
      int source = boost::source(*it, G[i]), target = boost::target(*it, G[i]);
      std::pair<edge_desc, bool> edge = boost::edge(source, target, forest);
      if(!edge.second) {
         ed = (boost::add_edge(source, target, forest)).first; f_wei[ed] = weights[i][*it];
      } else if(weights[i][*it] < boost::get(boost::edge_weight_t(), forest, edge.first)) {
        boost::put(boost::edge_weight_t(), forest, edge.first, weights[i][*it]);
      }
    }
  }
  
  std::vector<int> dist_map(n); 
  boost::dijkstra_shortest_paths(forest, a, boost::distance_map(boost::make_iterator_property_map(dist_map.begin(),
    boost::get(boost::vertex_index, forest))));
  
  // output
  std::cout << dist_map[b] << std::endl;
}

int main() {
  int t; std::cin >> t;
  for(int i=0; i<t; i++) testcase();
}
