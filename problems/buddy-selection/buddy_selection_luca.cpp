#include <bits/stdc++.h>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/max_cardinality_matching.hpp>

using namespace std;

typedef boost::adjacency_list<boost::vecS,
                              boost::vecS,
                              boost::undirectedS> graph;
typedef boost::graph_traits<graph>::vertex_descriptor vertex_desc;

int common(vector<string> &s1, vector<string> &s2, int c){
  int count = 0;
  int i = 0, j = 0;
  while(i < c && j < c){
    if(s1[i] == s2[j]){
      i++;
      j++;
      count++;
    }
    else if(s1[i] < s2[j])
      i++;
    else
      j++;
  }
  
  return count;
}

void testcase(){
  int n, c, f;
  cin >> n >> c >> f;
  
  graph G(n);
  vector<vector<string>> characteristics(n, vector<string>(c));
  for(int i = 0; i < n; i++){
    string str;
    for(int j = 0; j < c; j++){
      cin >> str;
      characteristics[i][j] = str;
    }
    sort(characteristics[i].begin(), characteristics[i].end());
  }
  
  //add an edge between two students if they have more than f common characteristics
  for(int i = 0; i < n; i++){
    for(int j = i+1; j < n; j++){
      int count = common(characteristics[i], characteristics[j], c);
      if(count > f){
        boost::add_edge(i, j, G);
        //cout << "ADDED EDGE: " << i << " -> " << j << endl;
      }
    }
  }
  
  vector<vertex_desc> mate_map(n); // exterior property map
  boost::edmonds_maximum_cardinality_matching(G, boost::make_iterator_property_map(mate_map.begin(), boost::get(boost::vertex_index, G)));
  int matching_size = boost::matching_size(G, boost::make_iterator_property_map(mate_map.begin(), boost::get(boost::vertex_index, G)));

  if(matching_size == n/2)
    cout << "not optimal" << endl;
  else
    cout << "optimal" << endl;
}

int main(){
  ios_base::sync_with_stdio(false);
  int t; cin >> t;
  for(int i = 0; i < t; i++)
    testcase();
  
  return 0;
}