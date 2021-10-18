#include <boost/config.hpp>
#include <list>
#include <boost/graph/biconnected_components.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <iterator>
#include <iostream>
#include <vector>
#include <boost/graph/graph_traits.hpp>

struct edge_component_t {
  enum { num = 555 };
  typedef boost::edge_property_tag kind;
} edge_component;

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS, boost::no_property, boost::property<edge_component_t,std::size_t>> graph;
typedef boost::graph_traits<graph>::vertex_descriptor vertex_t;
typedef boost::graph_traits<graph>::edge_descriptor edge_t;

void testcase() {
  
  int n; std::cin >> n;
  int m; std::cin >> m;

  // build the graph
  graph G(n);
  for(int i=0; i<m; i++) {
    int e1; std::cin >> e1;
    int e2; std::cin >> e2;
    boost::add_edge(e1, e2, G);
  }
  
  std::vector<std::pair<int,int>> res;
  
  boost::property_map<graph, edge_component_t>::type component = get(edge_component, G);
  size_t n_comp = boost::biconnected_components(G, component);
  std::vector<int> memo(n_comp, 0);
  
  boost::graph_traits<graph>::edge_iterator ei, ei_end;
  for(boost::tie(ei, ei_end) = boost::edges(G); ei != ei_end; ++ei) 
    memo[component[*ei]]++;
  
  for(boost::tie(ei, ei_end) = boost::edges(G); ei != ei_end; ++ei) {
    if(memo[component[*ei]] == 1) {
      int source = boost::source(*ei, G), target = boost::target(*ei, G);
      if(source < target) res.push_back(std::make_pair(source, target));
      else res.push_back(std::make_pair(target, source));
    }
  }
     
  std::sort(res.begin(), res.end()); 
  std::cout << res.size() << std::endl;
  for(std::size_t i=0; i<res.size(); i++) std::cout << res[i].first << ' ' << res[i].second << std::endl;
}

int main() {
  int c; std::cin >> c;
  for(int i=0; i<c; i++) testcase();
}
