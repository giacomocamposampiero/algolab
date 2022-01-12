#include <iostream>
#include <vector>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/strong_components.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS,
  boost::no_property, boost::property<boost::edge_weight_t, int> >      weighted_graph;
typedef boost::property_map<weighted_graph, boost::edge_weight_t>::type weight_map;
typedef boost::graph_traits<weighted_graph>::edge_descriptor            edge_desc;
typedef boost::graph_traits<weighted_graph>::vertex_descriptor          vertex_desc;
typedef boost::graph_traits<weighted_graph>::edge_iterator edge_it;

const int LIMIT = 1000001;

void testcase() {
  
  int n, m, k, T; std::cin >> n >> m >> k >> T;
  
  std::vector<int> tel(T, 0);
  for(int i=0; i<T; i++) std::cin >> tel[i];

  weighted_graph G(n);
  weight_map weights = boost::get(boost::edge_weight, G);
  

  
  edge_desc e;
  for(int i=0; i<m; i++) {
    int u, v, c; std::cin >> u >> v >> c;
    e = boost::add_edge(u, v, G).first; weights[e]=c;
  }
  
  std::vector<int> scc_map(n); 
  int nscc = boost::strong_components(G, boost::make_iterator_property_map(scc_map.begin(), boost::get(boost::vertex_index, G)));

  std::vector<std::vector<int>> components(nscc);
  for(int i=0; i<T; i++) components[scc_map[tel[i]]].push_back(tel[i]);
  

  int new_node = n;
  for(int i=0; i<nscc; i++) {
    int size = components[i].size();
    if(size > 1) {
      for(int j=0; j<size; j++) {
        e = boost::add_edge(components[i][j], new_node, G).first; weights[e]=size-1;
        e = boost::add_edge(new_node, components[i][j], G).first; weights[e]=0;
      }
      new_node++;
    }
  }
  
  weighted_graph IG(n);
  weight_map i_weights = boost::get(boost::edge_weight, IG);
  
  edge_it e_beg, e_end;
  for (boost::tie(e_beg, e_end) = boost::edges(G); e_beg != e_end; ++e_beg) {
    e = boost::add_edge(boost::target(*e_beg, G), boost::source(*e_beg, G), IG).first; 
    i_weights[e]=weights[*e_beg];
  }
  
  int min_dist = LIMIT;
  std::vector<int> dist_map(new_node);
  boost::dijkstra_shortest_paths(IG, n-1, boost::distance_map(boost::make_iterator_property_map(dist_map.begin(), boost::get(boost::vertex_index, IG))));
  
  for(int i=0; i<k; i++) min_dist = std::min(min_dist, dist_map[i]);

  if(min_dist < LIMIT) std::cout << min_dist << std::endl;
  else std::cout << "no" << std::endl;

}

int main() {
  std::ios_base::sync_with_stdio(false);
  int t; std::cin >> t;
  while(t--) testcase();
}
