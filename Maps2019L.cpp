#include <bits/stdc++.h>
using namespace std;

#define all(foo) foo.begin(), foo.end()

#define sc(a) scanf("%d", &a)
#define sc2(a,b) scanf("%d%d", &a, &b)
#define sc3(a,b,c) scanf("%d%d%d", &a, &b, &c)
#define pri(x) printf("%d\n", x)

#define db(x) cerr << #x << " == " << x << endl
#define dbs(x) cerr << x << endl
#define x first
#define y second

typedef long long ll;
typedef pair<int, int> ii;

const int inf = 0x3f3f3f3f;

int cnt[1001][1001];


int qry (int x1, int y1, int x2, int y2) {
  int ans = cnt[x2][y2];
  ans -= cnt[x1-1][y2];
  ans -= cnt[x2][y1-1];
  ans += cnt[x1-1][y1-1];
  return ans;
}

int qry (int a, int b, int m) {
  return qry(max(1, a-m), max(1, b-m), min(a+m, 999), min(b+m, 999));
}

int main () {
  int n;
  sc(n);
  vector<ii> v, u;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      char c;
      cin >> c;
      if (c == 'S') v.push_back(ii{i, j});
      if (c == 'H') u.push_back(ii{i, j});
    }
  }
  
  for (int i = 0; i < u.size(); i++) {
    cnt[u[i].x+u[i].y+1][u[i].x-u[i].y+101]++;
  }
  for (int i = 1; i < 1000; i++) {
    for (int j = 1; j < 1000; j++) {
      cnt[i][j] += cnt[i-1][j]+cnt[i][j-1]-cnt[i-1][j-1];
    }
  }
  int ans = 0;
  for (int i = 0; i < v.size(); i++) {
    int lo = 0, hi = 400;
    int a = v[i].x+v[i].y+1, b = v[i].x-v[i].y+101;
    while (hi-lo > 1) {
      int m = lo+hi>>1;
      if(qry(a, b, m)) hi = m;
      else lo = m;
    }
    ans = max(ans, qry(a, b, lo) ? lo : hi);
  pri(ans);
}
