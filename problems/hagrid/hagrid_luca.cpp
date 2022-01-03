///2
#include <bits/stdc++.h>
#include <boost/graph/adjacency_list.hpp>

using namespace std;

typedef boost::adjacency_list<
                              boost::vecS,
                              boost::vecS,
                              boost::directedS,
                              boost::no_property, // no vertex property
                              boost::property<boost::edge_weight_t, int> // edge property (interior)
                              > graph;
typedef boost::graph_traits<graph>::out_edge_iterator out_edge_it;
typedef pair<int,int> PI;
typedef tuple<PI,int,int> TI;

int calc_time(graph &G, vector<int> &duration, int start, int last){
  auto w_map = boost::get(boost::edge_weight, G); // new!
  out_edge_it oe_beg, oe_end;
  int sum = 0;
  for(boost::tie(oe_beg, oe_end) = boost::out_edges(start, G); oe_beg != oe_end; ++oe_beg) {
    sum += calc_time(G, duration, boost::target(*oe_beg, G), w_map[*oe_beg]) + w_map[*oe_beg];
  }
  
  duration[start] = last + sum;
  return sum;
}

int countR(graph &G, vector<int> &counts, int start){
  out_edge_it oe_beg, oe_end;
  int sum = 0;
  for(boost::tie(oe_beg, oe_end) = boost::out_edges(start, G); oe_beg != oe_end; ++oe_beg) {
    sum += 1+countR(G, counts, boost::target(*oe_beg, G));
  }
  
  counts[start] = sum+1;
  return sum;
}

long DFS(graph &G, vector<PI> &both, vector<int> &galleons, int start, int last, int &tempo){
  long res = 0;
  if(start != 0)
    res = galleons[start] - tempo;
  
  auto w_map = boost::get(boost::edge_weight, G); // new!
  out_edge_it oe_beg, oe_end;
  vector<TI> children;
  for(boost::tie(oe_beg, oe_end) = boost::out_edges(start, G); oe_beg != oe_end; ++oe_beg) {
    int new_start = boost::target(*oe_beg, G);
    children.push_back(TI(both[new_start], new_start, w_map[*oe_beg]));
  }
  
  sort(children.begin(), children.end(), [](const TI& t1, const TI &t2)-> bool {
    PI pr1 = get<0>(t1);
    PI pr2 = get<0>(t2);
    long d1 = pr1.first, d2 = pr2.first;
    long c1 = pr1.second, c2 = pr2.second;
    return d1*c2 < d2*c1;
  });
  
  for(auto it = children.begin(); it != children.end(); it++){
    tempo += get<2>(*it);
    res += DFS(G, both, galleons, get<1>(*it), get<2>(*it), tempo);
  }
  
  tempo += last;
  return res;
}

void testcase(){
  int n; cin >> n;
  
  graph G(n+1);
  
  vector<int> galleons(n+1);
  int g;
  for(int i = 1; i <= n; i++){
    cin >> g;
    galleons[i] = g;
  }
  
  int u, v, l;
  for(int i = 0; i < n; i++){
    cin >> u >> v >> l;
    boost::add_edge(u, v, l, G);
  }
  
  vector<int> duration(n+1, -1);
  vector<int> counts(n+1, -1);
  vector<PI> both(n+1, PI(-1,-1));
  calc_time(G, duration, 0, 0);
  countR(G, counts, 0);
  for(int i = 0; i <= n; i++)
    both[i] = PI(duration[i], counts[i]);

  int tempo = 0;
  long res = DFS(G, both, galleons, 0, 0, tempo);
  
  cout << res << endl;
}

int main(){
  ios_base::sync_with_stdio(false);
  int t; cin >> t;
  for(int i = 0; i < t; i++)
    testcase();
  
  return 0;
}