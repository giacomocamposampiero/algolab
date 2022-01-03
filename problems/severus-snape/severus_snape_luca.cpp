#include <bits/stdc++.h>

using namespace std;

typedef pair<int,int> PI;
typedef vector<vector<vector<long>>> TRIMAT;

long fA(vector<PI> &A, TRIMAT &memo, int h, int picks, int start, int n){
  if(h <= 0)  h = 0;
  if(picks <= 0){
    if(h == 0)
      return 0;
    
    return -numeric_limits<long>::max();
  }
  if(start >= n)
    return -numeric_limits<long>::max();
  
  if(memo[h][picks][start] != -1) return memo[h][picks][start];
  long res = max(A[start].first + fA(A, memo, h-A[start].second, picks-1, start+1, n),
                fA(A, memo, h, picks, start+1, n));
  
  memo[h][picks][start] = res;
  return res;
}

int evaluate(vector<PI> &A, TRIMAT &memo, vector<int> &B, int P, int H, int W, int a, int b, int end, int n){
  int numB = 0;
  long sum = 0;
  for(int i = 0; i < end; i++){
    sum += B[i];
    numB++;
  }
  
  int numA = numeric_limits<int>::max();
  for(int picks = 1; picks <= n; picks++){
    long res = fA(A, memo, H, picks, 0, n);
    if(res >= P+(long)numB*b){
      numA = picks;
      break;
    }
  }
  
  if(sum - (long)numA*a >= W && numA < numeric_limits<int>::max())
    return numA+numB;
  
  return numeric_limits<int>::max();
}

void testcase(){
  int n, m; cin >> n >> m;
  int a, b; cin >> a >> b;
  int P, H, W; cin >> P >> H >> W;
  
  vector<PI> A;
  int pi, hi;
  for(int i = 0; i < n; i++){
    cin >> pi >> hi;
    A.push_back(PI(pi, hi));
  }
  
  vector<int> B;
  int wi;
  for(int i = 0; i < m; i++){
    cin >> wi;
    B.push_back(wi);
  }
  
  sort(B.begin(), B.end(), greater<int>());
  
  TRIMAT memo(H+1, vector<vector<long>>(n+1, vector<long>(n, -1)));
  
  int left = 0, right = m;
  int mid = m;
  int minval = numeric_limits<int>::max();
  while(left <= right){
    int res = evaluate(A, memo, B, P, H, W, a, b, mid, n);
    if(res <= minval){
      right = mid-1;
      minval = res;
    }
    else
      left = mid+1;
    
    mid = (left+right)/2;
  }
  
  if(minval == numeric_limits<int>::max())
    cout << -1 << endl;
  else
    cout << minval << endl;
}

int main(){
  ios_base::sync_with_stdio(false);
  int t; cin >> t;
  for(int i = 0; i < t; i++)
    testcase();
  
  return 0;
}