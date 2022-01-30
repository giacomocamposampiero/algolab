///5
#include <iostream>
#include <queue>
#include <map>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/cycle_canceling.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>
#include <boost/graph/successive_shortest_path_nonnegative_weights.hpp>
#include <boost/graph/find_flow_cost.hpp>

typedef boost::adjacency_list_traits<boost::vecS, boost::vecS, boost::directedS> traits;
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS, boost::no_property,
    boost::property<boost::edge_capacity_t, long,
        boost::property<boost::edge_residual_capacity_t, long,
            boost::property<boost::edge_reverse_t, traits::edge_descriptor,
                boost::property <boost::edge_weight_t, long> > > > > graph; // new! weightmap corresponds to costs

typedef boost::graph_traits<graph>::edge_descriptor             edge_desc;
typedef boost::graph_traits<graph>::out_edge_iterator           out_edge_it; // Iterator
typedef boost::graph_traits<graph>::vertex_descriptor           vertex_desc;
class edge_adder {
 graph &G;

 public:
  explicit edge_adder(graph &G) : G(G) {}
  void add_edge(int from, int to, long capacity, long cost) {
    //std::cout << "edge "<< from << " -- " <<to <<" cap "<<capacity <<  " ("<<cost<<")\n";
    auto c_map = boost::get(boost::edge_capacity, G);
    auto r_map = boost::get(boost::edge_reverse, G);
    auto w_map = boost::get(boost::edge_weight, G); // new!
    const edge_desc e = boost::add_edge(from, to, G).first;
    const edge_desc rev_e = boost::add_edge(to, from, G).first;
    c_map[e] = capacity;
    c_map[rev_e] = 0; // reverse edge has no capacity!
    r_map[e] = rev_e;
    r_map[rev_e] = e;
    w_map[e] = cost;   // new assign cost
    w_map[rev_e] = -cost;   // new negative cost
  }
};

struct booking {
  int source;
  int target;
  int d;
  int a;
  int revenue;
};

const long MAX_REV = 100;

void testcase() {
  
  int N, S; std::cin >> N >> S;
  
  std::vector<int> init(S, 0);
  for(int i=0; i<S; i++) std::cin >> init[i];
  
  int max_time = 0;
  std::vector<std::vector<int>> important_points(S);
  std::vector<booking> bs(N);
  
  for(int i=0; i<N; i++) {
    std::cin >> bs[i].source >> bs[i].target >> bs[i].d >> bs[i].a >> bs[i].revenue;
    important_points[bs[i].source-1].push_back(bs[i].d);
    important_points[bs[i].target-1].push_back(bs[i].a);
    max_time = std::max(max_time, bs[i].a);
  }
  
  std::unordered_map<long,long> idx_map;
  
  long idx=0;
  for(int i=0; i<S; i++)
    for(size_t j=0; j<important_points[i].size(); j++)
      idx_map.insert({important_points[i][j]*S + i, idx++});
  
  graph G(idx);
  edge_adder adder(G);
  
  const vertex_desc v_source = boost::add_vertex(G);
  const vertex_desc v_sink = boost::add_vertex(G);
  
  for(int i=0; i<S; i++) {
    int size = important_points[i].size();
    if(size > 0) {
      std::sort(important_points[i].begin(), important_points[i].end());
      adder.add_edge(v_source, idx_map[important_points[i][0]*S + i], init[i], MAX_REV*important_points[i][0]);
      for(int j=1; j<size; j++) {
        int starting = important_points[i][j-1];
        int ending = important_points[i][j];
        adder.add_edge(idx_map[starting*S + i], idx_map[ending*S + i], 1000, MAX_REV*(ending-starting));
      }
      adder.add_edge(idx_map[important_points[i][size-1]*S + i], v_sink, 1000, MAX_REV*(max_time - important_points[i][size-1]));
    }
  }
  
  for(int i=0; i<N; i++) {
    
    int source_station = bs[i].source-1;
    int target_station = bs[i].target-1;
    int source_node = idx_map[bs[i].d*S + source_station];
    int target_node = idx_map[bs[i].a*S + target_station];
    int diff = bs[i].a-bs[i].d;
    
    adder.add_edge(source_node, target_node, 1, MAX_REV*diff - bs[i].revenue);
  }
  
  long flow = boost::push_relabel_max_flow(G, v_source, v_sink);
  boost::successive_shortest_path_nonnegative_weights(G, v_source, v_sink);
  
  long profit = max_time*MAX_REV*flow - boost::find_flow_cost(G);
  std::cout << profit << std::endl;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  int t; std::cin >> t;
  while(t--) testcase();
}
