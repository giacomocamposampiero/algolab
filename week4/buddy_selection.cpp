#include <iostream>
#include <string>
#include <vector>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/max_cardinality_matching.hpp>

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS> graph;
typedef boost::graph_traits<graph>::edge_descriptor edge_desc;
typedef boost::graph_traits<graph>::vertex_descriptor vertex_desc;

void testcase() {

  int n; std::cin >> n;
  int c; std::cin >> c;
  int f; std::cin >> f;
  
  std::string prop; prop.reserve(20);
  std::vector<std::vector<std::string>> chars(n, std::vector<std::string>(c, prop));
  
  for(int i=0; i<n; i++) {
    for(int j=0; j<c; j++) std::cin >> chars[i][j]; 
    std::sort(chars[i].begin(), chars[i].end());
  }

  graph G(n);

  for(int i=0; i<n; i++) {
    for(int j=i+1; j<n; j++) {
      int common_prop = 0;
      int k=0, l=0;
      while(k<c && l<c) {
        if(chars[i][k].compare(chars[j][l]) == 0) {common_prop++; l++; k++;}
        else if(chars[i][k].compare(chars[j][l]) > 0) l++;
        else k++;
      }
      if(common_prop > f) boost::add_edge(i, j, G); 
    }
  }
  
  std::vector<vertex_desc> mate_map(n); 
  //const vertex_desc NULL_VERTEX = boost::graph_traits<graph>::null_vertex();
  boost::edmonds_maximum_cardinality_matching(G, boost::make_iterator_property_map(mate_map.begin(), boost::get(boost::vertex_index, G)));
  int matching_size = boost::matching_size(G, boost::make_iterator_property_map(mate_map.begin(), boost::get(boost::vertex_index, G)));
  
  if(matching_size == (n/2)) std::cout << "not optimal" << std::endl;
  else std::cout << "optimal" << std::endl;
}

int main() {
  int t; std::cin >> t;
  for(int i=0; i<t; i++) testcase();
}
