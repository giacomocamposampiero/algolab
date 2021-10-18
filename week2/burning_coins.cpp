#include <iostream>
#include <vector>

int max_int(std::vector<std::vector<int>> &MEM, std::vector<int> &V, int i, int j) {
  // termination cases
  if(i==j) return V[i];
  if(j-i==1) { if(V[i]>V[j]) return V[i]; else return V[j]; }
  if(MEM[i][j]!=-1) return MEM[i][j];
  
  // comparable max guaranteed values from the two possible moves
  int ci, cj;
  
  int ci1 = V[i]+max_int(MEM, V,i+2,j);
  int ci2 = V[i]+max_int(MEM, V,i+1,j-1);
  
  ci = (ci1 < ci2)? ci1 : ci2;

  int cj1 = V[j]+max_int(MEM, V,i,j-2);
  int cj2 = V[j]+max_int(MEM, V,i+1,j-1);
  cj = (cj1 < cj2)? cj1 : cj2;

  if(ci > cj) {MEM[i][j]=ci; return ci;}
  {MEM[i][j]=cj; return cj;}
}

void testcase() {
  int n; std::cin >> n;
  std::vector<int> V(n);
  
  // read coin values
  for(int k=0; k<n; k++) std::cin >> V[k];
  
  int i = 0, j = n-1;
  // memoization
  std::vector<std::vector<int>> MEM(n, std::vector<int>(n, -1));
  
  // recursive function call
  int prize = max_int(MEM, V, i, j);
  
  // output
  std::cout << prize << std::endl;
}

int main() {
  int t; std::cin >> t;
  for(int i=0; i<t; i++) testcase();
}
