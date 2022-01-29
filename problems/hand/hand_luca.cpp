#include <bits/stdc++.h>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Triangulation_vertex_base_with_info_2.h>
#include <boost/pending/disjoint_sets.hpp>

using namespace std;

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Triangulation_vertex_base_with_info_2<int,K> Vb;
typedef CGAL::Triangulation_face_base_2<K> Fb;
typedef CGAL::Triangulation_data_structure_2<Vb,Fb> Tds;
typedef CGAL::Delaunay_triangulation_2<K,Tds> Triangulation;
typedef Triangulation::Vertex_handle VH;
typedef K::Point_2 P;
typedef tuple<long,VH,VH> TLV;
typedef boost::disjoint_sets_with_storage<> Uf;

int clusters(vector<int> &size, int k){
  switch(k){
    case 1:{
      return size[4] + size[3] + size[2] + size[1];
    }
    case 2:{
      return size[4] + size[3] + size[2] + size[1]/2;
    }
    case 3:{
      int match2with1 = min(size[2], size[1]);
      int rem2 = size[2] - match2with1; //one of them will
      int rem1 = size[1] - match2with1; //be zero
      return size[4] + size[3] + match2with1 + rem2/2 + rem1/3;
    }
    case 4:{
      int match3with1 = min(size[3], size[1]);
      int rem3 = size[3] - match3with1;
      int rem1 = size[1] - match3with1;
      int num2 = size[2] + rem3;
      return size[4] + match3with1 + num2/2 + ((num2%2)*2 + rem1)/4;
    }
  }
  
  return -1;
}

void testcase(){
  int n, k, f0;
  long s0;
  cin >> n >> k >> f0 >> s0;
  
  vector<pair<P,int>> tents;
  int x, y;
  for(int i = 0; i < n; i++){
    cin >> x >> y;
    tents.push_back(make_pair(P(x,y), i));
  }
  
  Triangulation t;
  t.insert(tents.begin(), tents.end());
  
  vector<TLV> edges;
  for(auto e: t.finite_edges()){
    VH v1 = e.first->vertex((e.second + 1) % 3);
    VH v2 = e.first->vertex((e.second + 2) % 3);
    
    edges.push_back(TLV(CGAL::squared_distance(v1->point(), v2->point()), v1, v2));
  }
  
  sort(edges.begin(), edges.end());
  
  vector<int> components(n, 1);
  vector<int> size(5, 0);
  size[1] = n;
  int ncomp = n;
  long f = n, s = 0;
  Uf sets(n);
  
  for(auto e: edges){
    long dist = get<0>(e);
    if(clusters(size, k) == f0)
      s = dist;
    
    VH v1 = get<1>(e);
    VH v2 = get<2>(e);
    if(sets.find_set(v1->info()) != sets.find_set(v2->info())){
      int c1 = components[sets.find_set(v1->info())];
      int c2 = components[sets.find_set(v2->info())];
      int tot = min(4, c1+c2);
      
      size[c1]--;
      size[c2]--;
      size[tot]++;
      
      sets.union_set(sets.find_set(v1->info()), sets.find_set(v2->info()));
      components[sets.find_set(v1->info())] = tot;
      
      if(dist < s0)
        f = clusters(size, k);
      
      ncomp--;
      if(ncomp == 1)  break;
    }
  }
  
  cout << s << " " << f << endl;
}

int main(){
  ios_base::sync_with_stdio(false);
  int t; cin >> t;
  for(int i = 0; i < t; i++)
    testcase();
  
  return 0;
}