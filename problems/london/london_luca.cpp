#include <bits/stdc++.h>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>

#define ALPHABET 26

using namespace std;

typedef boost::adjacency_list_traits<boost::vecS, boost::vecS, boost::directedS> traits;
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS, boost::no_property,
                              boost::property<boost::edge_capacity_t, long,
                              boost::property<boost::edge_residual_capacity_t, long,
                              boost::property<boost::edge_reverse_t, traits::edge_descriptor>>>> graph;
typedef traits::vertex_descriptor vertex_desc;
typedef traits::edge_descriptor edge_desc;

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

void testcase(){
  int h; cin >> h;
  int w; cin >> w;
  
  vector<int> needed(ALPHABET, 0);
  string crime;
  cin >> crime;
  int tot = crime.length();
  for(auto it = crime.begin(); it != crime.end(); it++)
    needed[*it - 'A']++;
  
  graph G(2*ALPHABET);
  edge_adder adder(G);
  
  const vertex_desc v_sink = boost::add_vertex(G);
  for(int i = 0; i < ALPHABET; i++){
    adder.add_edge(i+ALPHABET, v_sink, needed[i]);
  }
  
  vector<int> available(ALPHABET, 0);
  vector<vector<char>> front(h, vector<char>(w));
  vector<vector<int>> edges(ALPHABET, vector<int>(ALPHABET, 0));
  for(int i = 0; i < h; i++){
    char let;
    for(int j = 0; j < w; j++){
      cin >> let;
      available[let-'A']++;
      front[i][j] = let;
      edges[let-'A'][let-'A']++;
      //adder.add_edge(let-'A', ALPHABET+let-'A', 1);
    }
  }
  
  for(int i = 0; i < h; i++){
    char let;
    for(int j = 0; j < w; j++){
      cin >> let;
      char front_let = front[i][w-j-1];
      edges[front_let-'A'][let-'A']++;
      //adder.add_edge(front_let-'A', ALPHABET+let-'A', 1);
    }
  }
  
  for(int i = 0; i < ALPHABET; i++)
    for(int j = 0; j < ALPHABET; j++)
      if(edges[i][j] != 0)
        adder.add_edge(i, ALPHABET+j, edges[i][j]);
  
  const vertex_desc v_source = boost::add_vertex(G);
  for(int i = 0; i < ALPHABET; i++){
    adder.add_edge(v_source, i, available[i]);
  }
  
  long flow = boost::push_relabel_max_flow(G, v_source, v_sink);
  
  if(flow == tot)
    cout << "Yes" << endl;
  else
    cout << "No" << endl;
}

int main(){
  ios_base::sync_with_stdio(false);
  int t; cin >> t;
  for(int i = 0; i < t; i++)
    testcase();
  
  return 0;
}