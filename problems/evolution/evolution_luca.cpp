#include <bits/stdc++.h>
#include <boost/graph/adjacency_list.hpp>

using namespace std;

typedef boost::adjacency_list<boost::vecS,
                              boost::vecS,
                              boost::directedS> graph;
typedef boost::graph_traits<graph>::out_edge_iterator out_edge_it;
typedef pair<int,int> PI;
typedef tuple<int,int,int> TI;
typedef vector<vector<PI>> PIMAT;

int binary(vector<int> &path, vector<int> &ages, int b){
  int left = 0, right = path.size()-1;
  int best = -1;
  while(left <= right){
    int mid = (left+right)/2;
    if(ages[path[mid]] <= b)
      right = mid-1;
    else
      left = mid+1;
  }
  
  return path[right+1];
}

void DFS(graph &G, vector<int> &ages, PIMAT &queries, vector<int> &results, vector<int> &path, int start){
  path.push_back(start);
  for(int i = 0; i < queries[start].size(); i++){
    results[queries[start][i].second] = binary(path, ages, queries[start][i].first);
  }
  
  out_edge_it oe_beg, oe_end;
  for(boost::tie(oe_beg, oe_end) = boost::out_edges(start, G); oe_beg != oe_end; ++oe_beg){
    DFS(G, ages, queries, results, path, boost::target(*oe_beg, G));
  }
  
  path.pop_back();
}

void testcase(){
  int n; cin >> n;
  int q; cin >> q;
  
  map<string,int> species; //integer index
  vector<string> to_str;
  vector<int> ages;
  string s;
  int a;
  int maxidx = -1;
  int maxage = -1;
  for(int i = 0; i < n; i++){
    cin >> s >> a;
    species[s] = i;
    ages.push_back(a);
    to_str.push_back(s);
    if(a > maxage){
      maxage = a;
      maxidx = i;
    }
  }
  
  graph G(n);
  string p;
  for(int i = 0; i < n-1; i++){
    cin >> s >> p;
    int idxs = species[s];
    int idxp = species[p];
    boost::add_edge(idxp, idxs, G);
  }
  
  int b;
  //store for every node related queries
  vector<vector<PI>> queries(n, vector<PI>());
  vector<int> results(q);
  vector<int> path;
  for(int i = 0; i < q; i++){
    cin >> s >> b;
    int idxs = species[s];
    queries[idxs].push_back(PI(b, i));  //save original index for output
  }
  
  DFS(G, ages, queries, results, path, maxidx);
  
  for(int i = 0; i < q; i++)
    cout << to_str[results[i]] << " ";
  cout << endl;
}

int main(){
  ios_base::sync_with_stdio(false);
  int t; cin >> t;
  for(int i = 0; i < t; i++)
    testcase();
    
  return 0;
}