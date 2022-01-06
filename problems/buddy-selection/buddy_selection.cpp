#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/max_cardinality_matching.hpp>

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS> graph;
typedef boost::graph_traits<graph>::vertex_descriptor                       vertex_desc;

void testcase() {
  
  int n, c, f; std::cin >> n >> c >> f;
  
  std::vector<std::vector<std::string>> student(n);
  for(int i=0; i<n; i++) {
    for(int j=0; j<c; j++) {
      std::string s; std::cin >> s;
      student[i].push_back(s);
    }
  }
  
  for(int i=0; i<n; i++) std::sort(student[i].begin(), student[i].end());
  
  graph G(n);
  
  for(int i=0; i<n; i++) {
    for(int j=i+1; j<n; j++) {
      int matching = 0;
      int k=0, l=0;
      while(k<c && l<c) {
        if(student[i][k].compare(student[j][l]) == 0) {matching++; l++; k++;}
        else if(student[i][k].compare(student[j][l]) > 0) l++;
        else k++;
      }
      if(matching > f) boost::add_edge(i, j, G);
    }
  }
  
  std::vector<vertex_desc> mate_map(n);  

  boost::edmonds_maximum_cardinality_matching(G,
    boost::make_iterator_property_map(mate_map.begin(), boost::get(boost::vertex_index, G)));
  int matching_size = boost::matching_size(G,
    boost::make_iterator_property_map(mate_map.begin(), boost::get(boost::vertex_index, G)));

  if(matching_size == n/2) std::cout << "not optimal" << std::endl;
  else std::cout << "optimal" << std::endl;

}

int main() {
  std::ios_base::sync_with_stdio(false);
  int t; std::cin >> t;
  while(t--) testcase();
}
