#include <iostream>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>

using namespace std;

typedef boost::adjacency_list_traits<boost::vecS, boost::vecS, boost::directedS> traits;
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS, boost::no_property,
                              boost::property<boost::edge_capacity_t, long,
                              boost::property<boost::edge_residual_capacity_t, long,
                              boost::property<boost::edge_reverse_t, traits::edge_descriptor>>>> graph;
typedef traits::vertex_descriptor vertex_desc;
typedef traits::edge_descriptor edge_desc;
typedef boost::graph_traits<graph>::out_edge_iterator out_edge_it;

class edge_adder {
  graph &G;
  public:
    explicit edge_adder(graph &G) : G(G) {}
    void add_edge(int from, int to, long capacity) {
      auto c_map = boost::get(boost::edge_capacity, G);
      auto r_map = boost::get(boost::edge_reverse, G);
      const auto e = boost::add_edge(from, to, G).first;
      const auto rev_e = boost::add_edge(to, from, G).first;
      c_map[e] = capacity;
      c_map[rev_e] = 0; // reverse edge has no capacity!
      r_map[e] = rev_e;
      r_map[rev_e] = e;
    }
};

int idx(int i, int j, int n){
  return i*n+j;
}

void testcase(){
  int n; cin >> n;
  vector<vector<int>> chessboard(n, vector<int>(n));
  
  int pres;
  int holes = 0;
  for(int i = 0; i < n; i++){
    for(int j = 0; j < n; j++){
      cin >> pres;
      chessboard[i][j] = pres;
      if(pres == 0)
        holes++;
    }
  }
  
  graph G(n*n);
  edge_adder adder(G);
  
  for(int i = 0; i < n; i++){
    for(int j = 0; j < n; j++){
      if(chessboard[i][j] == 1 && (i+j)%2 == 0){
        if(i >= 1 && j >= 2 && chessboard[i-1][j-2] == 1){
          adder.add_edge(idx(i,j,n), idx(i-1,j-2,n), 1);
        }
        if(i >= 1 && j < n-2 && chessboard[i-1][j+2] == 1){
          adder.add_edge(idx(i,j,n), idx(i-1,j+2,n), 1);
        }
        if(i < n-1 && j >= 2 && chessboard[i+1][j-2] == 1){
          adder.add_edge(idx(i,j,n), idx(i+1,j-2,n), 1);
        }
        if(i < n-1 && j < n-2 && chessboard[i+1][j+2] == 1){
          adder.add_edge(idx(i,j,n), idx(i+1,j+2,n), 1);
        }
        if(i >= 2 && j >= 1 && chessboard[i-2][j-1] == 1){
          adder.add_edge(idx(i,j,n), idx(i-2,j-1,n), 1);
        }
        if(i >= 2 && j < n-1 && chessboard[i-2][j+1] == 1){
          adder.add_edge(idx(i,j,n), idx(i-2,j+1,n), 1);
        }
        if(i < n-2 && j >= 1 && chessboard[i+2][j-1] == 1){
          adder.add_edge(idx(i,j,n), idx(i+2,j-1,n), 1);
        }
        if(i < n-2 && j < n-1 && chessboard[i+2][j+1] == 1){
          adder.add_edge(idx(i,j,n), idx(i+2,j+1,n), 1);
        }
      }
    }
  }
  
  const vertex_desc v_source = boost::add_vertex(G);
  const vertex_desc v_sink = boost::add_vertex(G);
  for(int i = 0; i < n; i++){
    for(int j = 0; j < n; j++){
      if((i+j)%2 == 0)
        adder.add_edge(v_source, idx(i,j,n), 1);
      else
        adder.add_edge(idx(i,j,n), v_sink, 1);
    }
  }
  //In a bipartite graph, the number of edges in a maximum matching is equal to the number of
  //vertices in a minimum vertex cover.
  //holes are part of the MaxIS
  
  long flow = boost::push_relabel_max_flow(G, v_source, v_sink);
  
  cout << n*n - holes - flow << endl;
}

int main(){
  ios_base::sync_with_stdio(false);
  int t; cin >> t;
  for(int i = 0; i < t; i++)
    testcase();
    
  return 0;
}