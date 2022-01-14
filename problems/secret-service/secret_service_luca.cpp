#include <bits/stdc++.h>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/graph/max_cardinality_matching.hpp>

using namespace std;

typedef boost::adjacency_list<
                              boost::vecS,
                              boost::vecS,
                              boost::directedS,
                              boost::no_property, // no vertex property
                              boost::property<boost::edge_weight_t, int> // edge property (interior)
                              > graph;
typedef boost::graph_traits<graph>::vertex_descriptor vertex_desc;

void testcase(){
  int n, m, a, s, c, d;
  cin >> n >> m >> a >> s >> c >> d;
  
  graph G(n);
  char w;
  int x, y, z;
  for(int i = 0; i < m; i++){
    cin >> w >> x >> y >> z;
    boost::add_edge(x, y, z, G);
    if(w == 'L')
      boost::add_edge(y, x, z, G);
  }
  
  vector<int> agents;
  int alpha;
  for(int i = 0; i < a; i++){
    cin >> alpha;
    agents.push_back(alpha);
  }
  vector<int> shelters;
  int sigma;
  for(int i = 0; i < s; i++){
    cin >> sigma;
    shelters.push_back(sigma);
  }
  
  vector<vector<int>> new_edges(a, vector<int>(s));
  for(int i = 0; i < a; i++){
    vector<int> dist_map(n);
    boost::dijkstra_shortest_paths(G, agents[i], boost::distance_map(boost::make_iterator_property_map(dist_map.begin(), boost::get(boost::vertex_index, G))));
    for(int j = 0; j < s; j++){
      new_edges[i][j] = dist_map[shelters[j]];
    }
  }
  
  int left = 0, right = pow(10,8);
  while(left <= right){
    int mid = (left+right)/2;
    graph newG(a+c*s);
    for(int i = 0; i < a; i++){
      for(int j = 0; j < s; j++){
        for(int k = 1; k <= c; k++){
          if(new_edges[i][j] <= mid-k*d)  //don't add d on the other side because of overflow: not reachable vertex from Dijkstra: numeric_limits<int>::max()
            boost::add_edge(i, a+(k-1)*s+j, new_edges[i][j], newG);
        }
      }
    }
    
    vector<vertex_desc> mate_map(a+c*s); // exterior property map
    boost::edmonds_maximum_cardinality_matching(newG, boost::make_iterator_property_map(mate_map.begin(), boost::get(boost::vertex_index, newG)));
    int matching_size = boost::matching_size(newG, boost::make_iterator_property_map(mate_map.begin(), boost::get(boost::vertex_index, newG)));
    if(matching_size == a)
      right = mid-1;
    else
      left = mid+1;
  }
  
  cout << right+1 << endl;
}

int main(){
  ios_base::sync_with_stdio(false);
  int t; cin >> t;
  for(int i = 0; i < t; i++)
    testcase();
  
  return 0;
}