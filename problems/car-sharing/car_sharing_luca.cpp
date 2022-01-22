#include <bits/stdc++.h>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/successive_shortest_path_nonnegative_weights.hpp>
#include <boost/graph/find_flow_cost.hpp>

using namespace std;

typedef boost::adjacency_list_traits<boost::vecS, boost::vecS, boost::directedS> traits;
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS, boost::no_property,
    boost::property<boost::edge_capacity_t, long,
        boost::property<boost::edge_residual_capacity_t, long,
            boost::property<boost::edge_reverse_t, traits::edge_descriptor,
                boost::property <boost::edge_weight_t, long> > > > > graph; // new! weightmap corresponds to costs

typedef boost::graph_traits<graph>::edge_descriptor             edge_desc;
typedef boost::graph_traits<graph>::vertex_descriptor             vertex_desc;
typedef boost::graph_traits<graph>::out_edge_iterator           out_edge_it; // Iterator
typedef tuple<int,int,int,int,int> TI;

class edge_adder {
 graph &G;

 public:
  explicit edge_adder(graph &G) : G(G) {}
  void add_edge(int from, int to, long capacity, long cost) {
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

void testcase(){
  int N; cin >> N;
  int S; cin >> S;
  
  const long MAXTIME = 100000;
  
  vector<int> initial;
  int l;
  int sum = 0;
  for(int i = 0; i < S; i++){
    cin >> l;
    sum += l;
    initial.push_back(l);
  }
  
  int s, t, d, a, p;
  vector<TI> bookings;
  vector<set<int>> times(S, set<int>());
  for(int i = 0; i < S; i++){
    times[i].insert(0);
    times[i].insert(MAXTIME);
  }
  for(int i = 0; i < N; i++){
    cin >> s >> t >> d >> a >> p;
    times[s-1].insert(d);
    times[t-1].insert(a);
    bookings.push_back(TI(s, t, d, a, p));
  }
  
  long size = 0;
  for(int i = 0; i < S; i++)
    size += times[i].size();
  
  graph G(size);
  edge_adder adder(G);
  
  int idx = 0;
  for(int i = 0; i < S; i++){
    for(auto it = times[i].begin(); it != prev(times[i].end()); it++){
      adder.add_edge(idx, idx+1, sum, (*next(it)-*it)*100);
      idx++;
    }
    idx++;  //this way I avoid linking last node with first of another set
  }
  
  const vertex_desc v_source = boost::add_vertex(G);
  const vertex_desc v_sink = boost::add_vertex(G);
  idx = 0;
  for(int i = 0; i < S; i++){
    adder.add_edge(v_source, idx, initial[i], 0);
    idx += (int)times[i].size();
  }
  
  idx = 0;
  for(int i = 0; i < S; i++){
    adder.add_edge(idx+times[i].size()-1, v_sink, sum, 0);
    idx += times[i].size();
  }
  
  for(int i = 0; i < N; i++){
    int s = get<0>(bookings[i]);
    int t = get<1>(bookings[i]);
    int d = get<2>(bookings[i]);
    int a = get<3>(bookings[i]);
    int p = get<4>(bookings[i]);
    int off1 = 0;
    for(int i = 0; i < s-1; i++)
      off1 += times[i].size();
    
    int off2 = 0;
    for(int i = 0; i < t-1; i++)
      off2 += times[i].size();
    
    int idx1 = off1 + distance(times[s-1].begin(), times[s-1].find(d));
    int idx2 = off2 + distance(times[t-1].begin(), times[t-1].find(a));
    
    adder.add_edge(idx1, idx2, 1, -p+(a-d)*100);
  }
  
  auto c_map = boost::get(boost::edge_capacity, G);
  auto rc_map = boost::get(boost::edge_residual_capacity, G);
  boost::successive_shortest_path_nonnegative_weights(G, v_source, v_sink);
  long cost = boost::find_flow_cost(G);
  long s_flow = 0;
  out_edge_it e_beg, e_end;
  for(boost::tie(e_beg, e_end) = boost::out_edges(boost::vertex(v_source,G), G); e_beg != e_end; ++e_beg)
    s_flow += c_map[*e_beg] - rc_map[*e_beg];
  
  cout << -(cost-s_flow*(long)100*MAXTIME) << endl;
}

int main(){
  ios_base::sync_with_stdio(false);
  int t; cin >> t;
  for(int i = 0; i < t; i++)
    testcase();
  
  return 0;
}