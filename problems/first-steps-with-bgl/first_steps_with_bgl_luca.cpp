#include <bits/stdc++.h>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/graph/kruskal_min_spanning_tree.hpp>

using namespace std;

typedef boost::adjacency_list<
                              boost::vecS,
                              boost::vecS,
                              boost::directedS,
                              boost::no_property, // no vertex property
                              boost::property<boost::edge_weight_t, int> // edge property (interior)
                              > graph;
typedef boost::graph_traits<graph>::edge_descriptor edge_desc;

void testcase(){
  int n; cin >> n;
  int m; cin >> m;
  
  graph G(n);
  
  int u, v, c;
  for(int i = 0; i < m; i++){
    cin >> u >> v >> c;
    boost::add_edge(u, v, c, G);
    boost::add_edge(v, u, c, G);
  }
  
  int tot_weight = 0;
  auto w_map = boost::get(boost::edge_weight, G);
  vector<edge_desc> mst; // vector to store MST edges (not a property map!)
  boost::kruskal_minimum_spanning_tree(G, std::back_inserter(mst));
  for(auto it = mst.begin(); it != mst.end(); ++it)
    tot_weight += w_map[*it];
  
  vector<int> dist_map(n); //exterior property
  boost::dijkstra_shortest_paths(G, 0, boost::distance_map(boost::make_iterator_property_map(dist_map.begin(), boost::get(boost::vertex_index, G))));
  
  int maxdist = -1;
  for(int i = 1; i < n; i++){
    maxdist = max(maxdist, dist_map[i]);
  }
  
  cout << tot_weight << " " << maxdist << endl;
}

int main(){
  ios_base::sync_with_stdio(false);
  int t; cin >> t;
  for(int i = 0; i < t; i++)
    testcase();
  
  return 0;
}