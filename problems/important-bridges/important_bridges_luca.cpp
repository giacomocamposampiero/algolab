#include <bits/stdc++.h>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/biconnected_components.hpp>

using namespace std;

struct edge_component_t
{
    enum
    {
        num = 555
    };
    typedef boost::edge_property_tag kind;
} edge_component;

typedef boost::adjacency_list< boost::vecS, boost::vecS, boost::undirectedS, boost::no_property,
        boost::property< edge_component_t, size_t > >
        graph;
typedef boost::graph_traits< graph >::vertex_descriptor vertex_t;
typedef boost::graph_traits< graph >::edge_descriptor edge_t;
typedef pair<int,int> PI;

void testcase(){
  int n; cin >> n;
  int m; cin >> m;
  
  graph G(n);
  
  int e1, e2;
  for(int i = 0; i < m; i++){
    cin >> e1 >> e2;
    boost::add_edge(e1, e2, G);
  }
  
  boost::property_map< graph, edge_component_t >::type component = boost::get(edge_component, G);
  size_t num_comps = biconnected_components(G, component);
  
  vector<int> n_edges(num_comps, 0);
  boost::graph_traits< graph >::edge_iterator ei, ei_end;
  for(boost::tie(ei, ei_end) = boost::edges(G); ei != ei_end; ++ei){
    n_edges[component[*ei]]++;
  }
  
  vector<PI> edges;
  for(boost::tie(ei, ei_end) = boost::edges(G); ei != ei_end; ++ei){
    if(n_edges[component[*ei]] == 1){
      int ei1 = min(boost::source(*ei, G), boost::target(*ei, G));
      int ei2 = max(boost::source(*ei, G), boost::target(*ei, G));
      edges.push_back(PI(ei1, ei2));
    }
  }
  
  sort(edges.begin(), edges.end());
  
  cout << (int)edges.size() << endl;
  for(int i = 0; i < (int)edges.size(); i++)
    cout << edges[i].first << " " << edges[i].second << endl;
  
}

int main(){
  ios_base::sync_with_stdio(false);
  int c; cin >> c;
  for(int i = 0; i < c; i++)
    testcase();
  
  return 0;
}