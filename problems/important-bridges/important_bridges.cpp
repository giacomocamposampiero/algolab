#include <boost/config.hpp>
#include <vector>
#include <boost/graph/biconnected_components.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <iterator>
#include <iostream>
#include <algorithm>

namespace boost {
  struct edge_component_t {
      enum
      {
          num = 6000
      };
      typedef edge_property_tag kind;
  } edge_component;
}

using namespace boost;
typedef adjacency_list< vecS, vecS, undirectedS, no_property, property< edge_component_t, std::size_t>> graph_t;
typedef graph_traits< graph_t >::vertex_descriptor vertex_t;

void testcase() {
    
  int n, m; std::cin >> n >> m;
  
  graph_t g(n);
  for(int i=0; i<m; i++) {
    int u, v; std::cin >> u >> v;
    boost::add_edge(u, v, g);
  }

  property_map< graph_t, edge_component_t >::type component = get(edge_component, g);
  biconnected_components(g, component);

  std::vector<int> comp_size(n, 0);
  graph_traits< graph_t >::edge_iterator ei, ei_end;
  for (boost::tie(ei, ei_end) = edges(g); ei != ei_end; ++ei) comp_size[component[*ei]]++;
  
  std::vector<std::pair<int,int>> bridges;
  for (boost::tie(ei, ei_end) = edges(g); ei != ei_end; ++ei) {
    int s = source(*ei, g);
    int t = target(*ei, g);
    if(comp_size[component[*ei]] == 1) 
      bridges.push_back(std::make_pair(std::min(s, t), std::max(s, t)));
  }
  
  std::sort(bridges.begin(), bridges.end());
  std::cout << bridges.size() << std::endl;
  for(std::size_t i=0; i<bridges.size(); i++) std::cout<< bridges[i].first << ' ' << bridges[i].second << std::endl;
  
}

int main() {
  std::ios_base::sync_with_stdio(false);
  int t; std::cin >> t;
  while(t--) testcase();
}
