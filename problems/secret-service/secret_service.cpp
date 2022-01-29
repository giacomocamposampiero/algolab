///
#include <iostream>
#include <vector>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/graph/max_cardinality_matching.hpp>

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS> matching_graph;
typedef boost::graph_traits<matching_graph>::vertex_descriptor             matching_vertex_desc;

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS, boost::no_property, boost::property<boost::edge_weight_t, int> >      weighted_graph;
typedef boost::property_map<weighted_graph, boost::edge_weight_t>::type weight_map;
typedef boost::graph_traits<weighted_graph>::edge_descriptor            edge_desc;
typedef boost::graph_traits<weighted_graph>::vertex_descriptor          vertex_desc;

void testcase() {

  int n, m, a, s, c, d; std::cin >> n >> m >> a >> s >> c >> d;

  weighted_graph G(n);
  weight_map weights = boost::get(boost::edge_weight, G);
  
  edge_desc e;
  for(int i=0; i<m; i++) {
    char w; int x, y, z; std::cin >> w >> x >> y >> z;
    e = boost::add_edge(x, y, G).first; weights[e]=z;
    if(w == 'L') {e = boost::add_edge(y, x, G).first; weights[e]=z;}
  }
  
  std::vector<int> agent(a, 0);
  for(int i=0; i<a; i++) std::cin >> agent[i];
  
  std::vector<int> shelter(s, 0);
  for(int i=0; i<s; i++) std::cin >> shelter[i]; 
  
  std::vector<int> dist_map(n);
  std::vector<std::vector<int>> adj(a, std::vector<int>(s, 0));
  for(int i=0; i<a; i++) {
    boost::dijkstra_shortest_paths(G, agent[i], boost::distance_map(boost::make_iterator_property_map(dist_map.begin(), boost::get(boost::vertex_index, G))));
    for(int j=0; j<s; j++) adj[i][j] = dist_map[shelter[j]];
  }
  
  int left=0, right=50002000;
  
  while(left < right) {
    
    int mid = (left == 0 && right == 50002000) ? 10 : (left+right)/2; 
    
    matching_graph M(a+s*c);
    
    for(int i=0; i<a; i++) {
      for(int j=0; j<s; j++) {
      
        int path_len = adj[i][j];
        if(path_len == std::numeric_limits<int>::max()) continue;
        
        for(int k = 1; k <= c; k++) 
          if (path_len + k * d <= mid) 
            boost::add_edge(i, a + (k-1) * s + j, M);
      }
    }

    std::vector<matching_vertex_desc> mate_map(a+s*c);  

    boost::edmonds_maximum_cardinality_matching(M,
      boost::make_iterator_property_map(mate_map.begin(), boost::get(boost::vertex_index, M)));
    int matching_size = boost::matching_size(M,
      boost::make_iterator_property_map(mate_map.begin(), boost::get(boost::vertex_index, M)));

    if(matching_size == a) right = mid; 
    else left = mid + 1;
  }
  
  std::cout << left << std::endl;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  int t; std::cin >> t;
  while(t--) testcase();
}
