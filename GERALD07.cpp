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

struct dsu {
  vector<int> hist, par, sz;
  vector<ii> changes;
  int n;
  dsu (int n) : n(n) {
    hist.assign(n, 1e9);
    par.resize(n);
    iota(par.begin(), par.end(), 0);
    sz.assign(n, 1);
  }
  
  int root (int x, int t) {
    if(hist[x] > t) return x;
    return root(par[x], t);
  }
  
  void join (int a, int b, int t) {
    a = root(a, t);
    b = root(b, t);
    if (a == b) { changes.emplace_back(-1, -1); return; }
    if (sz[a] > sz[b]) swap(a, b);
    par[a] = b;
    sz[b] += sz[a];
    hist[a] = t;
    changes.emplace_back(a, b);
    n--;
  }
  
  bool same (int a, int b, int t) {
    return root(a, t) == root(b, t);
  }
  
  void undo () {
    int a, b;
    tie(a, b) = changes.back();
    changes.pop_back();
    if (a == -1) return;
    sz[b] -= sz[a];
    par[a] = a;
    hist[a] = 1e9;
    n++;
  }
  
  int when (int a, int b) {
    while (1) {
      if (hist[a] > hist[b]) swap(a, b);
      if (par[a] == b) return hist[a];
      if (hist[a] == 1e9) return 1e9;
      a = par[a];
    }
  }
};

struct Q{
  int l, r, id;
  Q () {}
  Q (int l, int r, int id) : l(l), r(r), id(id) {}
};

vector<Q> block[700];
const int mx = 212345, magic = 300;
int ans[mx];

ii e[mx];

void solve (int n, int m, vector<Q> &q) {
  if (q.empty()) return;
  dsu a(n);
  sort(all(q), [&] (const Q &a, const Q &b) {
    return a.r < b.r;
  });
  int maxl = ((q[0].l/magic)+1)*magic;
  int t = 0;
  for (int i = 0, l = maxl; i < q.size(); i++) {
    while (l < m && l <= q[i].r) {
      a.join(e[l].x, e[l].y, t++), l++;
    }
    
    for (int j = q[i].l; j <= min(q[i].r, maxl-1); j++) {
      a.join(e[j].x, e[j].y, t++);
    }
    ans[q[i].id] = a.n;
    
    for (int j = q[i].l; j <= min(q[i].r, maxl-1); j++) a.undo(), t--;
  }
}

int main () {
  int n, m, q;
  int t;
  sc(t);
  while (t--) {
    sc3(n, m, q);
    for (int i = 0; i < m; i++) {
      sc2(e[i].x, e[i].y);
      e[i].x--, e[i].y--;
    }
    for (int i = 0; i < q; i++) {
      int x, y;
      sc2(x, y);
      x--, y--;
      block[x/magic].emplace_back(Q(x, y, i));
    }
    for (int i = 0; i <= m/magic; i++) {
      solve(n, m, block[i]);
      block[i].clear();
    }
    for (int i = 0; i < q; i++) {
      pri(ans[i]);
    }
  }
}
