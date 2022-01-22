#include <iostream>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/kruskal_min_spanning_tree.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>

typedef boost::adjacency_list<boost::vecS,
                              boost::vecS,
                              boost::undirectedS,
                              boost::no_property,
                              boost::property<boost::edge_weight_t, int>
                              > graph;
                              
typedef boost::graph_traits<graph>::edge_descriptor edge_desc;
typedef boost::graph_traits<graph>::edge_iterator edge_it;

using namespace std;

void testcase(){
  int n, e, s, a, b;
  cin >> n >> e >> s >> a >> b;
  
  vector<graph> vg(s, graph(n));
  
  int t1, t2, w;
  for(int i = 0; i < e; i++){
    cin >> t1 >> t2;
    for(int j = 0; j < s; j++){
      cin >> w;
      boost::add_edge(t1, t2, w, vg[j]);
    }
  }
  
  int h;
  for(int i = 0; i < s; i++)  //not needed
    cin >> h;
  
  //merge all vg's MSTs in a new graph
  graph new_graph(n);
  for(int i = 0; i < s; i++){
    vector<edge_desc> mst;
    auto w_map = boost::get(boost::edge_weight, vg[i]);
    boost::kruskal_minimum_spanning_tree(vg[i], std::back_inserter(mst));
    for(auto it = mst.begin(); it != mst.end(); ++it)
      boost::add_edge(boost::source(*it, vg[i]), boost::target(*it, vg[i]), w_map[*it], new_graph);
  }
  
  vector<int> dist_map(n);
  boost::dijkstra_shortest_paths(new_graph, a, boost::distance_map(boost::make_iterator_property_map(dist_map.begin(), boost::get(boost::vertex_index, new_graph))));

  cout << dist_map[b] << endl;
}

int main(){
  ios_base::sync_with_stdio(false);
  int t; cin >> t;
  for(int i = 0; i < t; i++)
    testcase();
  
  return 0;
}