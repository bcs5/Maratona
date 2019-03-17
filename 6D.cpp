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

const int mx = 112345;

int pt[mx][6], pv[mx][1<<6];

int main () {
  int n, d;
  sc2(n, d);
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < d; j++) sc(pt[i][j]);
  }
  for (int i = 0; i < (1<<d); i++) {
    bool comb[d];
    for (int j = 0; j < d; j++) {
      comb[j] = !!((i>>j) & 1);
    }
    for (int j = 0; j < n; j++) {
      for (int k = 0; k < d; k++) {
        pv[j][i] += (1 - 2*comb[k])*pt[j][k];
      }
    }
  }
  int pvmax[1<<d];
  memset(pvmax, -1, sizeof pvmax);
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < (1<<d); j++) {
      if (pvmax[j] == -1 || pv[pvmax[j]][j] < pv[i][j])
        pvmax[j] = i;
    }
  }
  int ans = 0;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < (1<<d); j++) {
      ans = max(ans, abs(pv[pvmax[j]][j] - pv[i][j]));
    }
  }
  pri(ans);
}



