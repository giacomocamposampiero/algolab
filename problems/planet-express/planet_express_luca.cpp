///1
#include <bits/stdc++.h>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/graph/strong_components.hpp>

using namespace std;

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS,
                              boost::no_property, boost::property<boost::edge_weight_t, int> > graph;
typedef boost::property_map<graph, boost::edge_weight_t>::type weight_map;
typedef boost::graph_traits<graph>::edge_descriptor            edge_desc;
typedef boost::graph_traits<graph>::vertex_descriptor          vertex_desc;
typedef boost::graph_traits<graph>::out_edge_iterator out_edge_it;

void testcase(){
  int n, m, k, T;
  cin >> n >> m >> k >> T;
  
  graph G(n);
  
  vector<int> tel_net;
  int ti;
  for(int i = 0; i < T; i++){
    cin >> ti;
    tel_net.push_back(ti);
  }
  
  int u, v, c;
  for(int i = 0; i < m; i++){
    cin >> u >> v >> c;
    boost::add_edge(v, u, c, G); //reverse graph
  }
  
  //Strongly connected components
  vector<int> scc_map(n);
  int nscc = boost::strong_components(G, boost::make_iterator_property_map(scc_map.begin(), boost::get(boost::vertex_index, G)));
  
  vector<int> count(nscc, 0);
  for(int i = 0; i < T; i++)
    count[scc_map[tel_net[i]]]++;
  
  //add a dummy node for each connected component
  for(int i = 0; i < T; i++){
    boost::add_edge(tel_net[i], n+scc_map[tel_net[i]], 0, G);
    boost::add_edge(n+scc_map[tel_net[i]], tel_net[i], count[scc_map[tel_net[i]]]-1, G);
  }
  
  // for(int i = 0; i < T; i++){
  //   for(int j = i+1; j < T; j++){
  //     if(scc_map[tel_net[i]] == scc_map[tel_net[j]]){
  //       boost::add_edge(tel_net[i], tel_net[j], count[scc_map[tel_net[i]]]-1, G);
  //       boost::add_edge(tel_net[j], tel_net[i], count[scc_map[tel_net[j]]]-1, G);
  //     }
  //   }
  // }
  
  //Dijkstra
  vector<int> dist_map(n+nscc);

  boost::dijkstra_shortest_paths(G, n-1,
    boost::distance_map(boost::make_iterator_property_map(
      dist_map.begin(), boost::get(boost::vertex_index, G))));

  int upper = 1000001;
  int mintime = upper;
  for(int i = 0; i < k; i++){
    mintime = min(mintime, dist_map[i]);
  }
  
  if(mintime < upper)
    cout << mintime << endl;
  else
    cout << "no" << endl;
}

int main(){
  ios_base::sync_with_stdio(false);
  int t; cin >> t;
  for(int i = 0; i < t; i++)
    testcase();
  
  return 0;
}