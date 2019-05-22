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
#define pb push_back


typedef long long ll;
typedef pair<int, int> ii;

const double inf = 1e100, eps = 1e-9;
const double PI = acos(-1.0L);

struct PT {
  double x, y;
  PT(double x = 0, double y = 0) : x(x), y(y) {}
  PT operator + (const PT &p) const { return PT(x+p.x, y+p.y); }
  PT operator - (const PT &p) const { return PT(x-p.x, y-p.y); }
  PT operator * (double c) const { return PT(x*c, y*c); }
  PT operator / (double c) const { return PT(x/c, y/c); }
  
  bool operator <(const PT &p) const {
    if(abs(x - p.x) >= eps) return x < p.x;
    return abs(y - p.y) >= eps && y < p.y;
  }
  bool operator ==(const PT &p) const {
    return !(*this < p || p < *this);
  }
};

const int mx = 112345;

double getY (double x, PT a, PT b) {
  PT dir = (b-a);
  double k = (x-a.x) / dir.x;
  return a.y + k*dir.y;
}

set<pair<double, int>, greater<pair<double, int>> > f[mx];
PT a[mx], b[mx];
int fim[mx], in[mx], cnt[mx], ans[mx];
set<int> adj[mx];

int main () {
  int T;
  sc(T);
  while (T--) {
    int n;
    cin >> n;
    vector <int> cx;
    vector<pair<int, int>> ev;
    for (int i = 1; i <= n; i++) {
      int x1, y1, x2, y2;
      scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
      a[i] = PT(x1, y1);
      b[i] = PT(x2, y2);
      cx.pb(x1);
      cx.pb(x2);
      ev.pb({x1, -i});
      ev.pb({x2, +i});
      fim[i] = y1 < y2 ? x1 : x2;
      in[i] = 0, ans[i] = 0;
    }
    sort(all(cx));
    cx.erase(unique(all(cx)), cx.end());
    sort(all(ev));
    set<int> active;
    int k = 0;
    for(int i = 0; i < cx.size(); i++) {
      int curx = cx[i];
      while (k < ev.size() && ev[k].x <= curx && ev[k].y < 0) {
        active.insert(-ev[k++].y);
      }
      for (auto j : active) {
        f[i].insert({getY(curx, a[j], b[j]), j});
      }
      for (auto u = f[i].begin(); u != f[i].end(); u++) {
        if (fim[u->y] == curx) {
          if (next(u) != f[i].end()) {
            int t = next(u)->y;
            if (!adj[u->y].count(t)) {
              adj[u->y].insert(t);
              in[t]++;
            }
          }
        }
      }
      while (k < ev.size() && ev[k].x <= curx && ev[k].y > 0) {
        active.erase(ev[k++].y);
      }
    }
    // direct rain
    for (int i = 0; i < cx.size()-1; i++) {
      for ( auto t : f[i+1]) cnt[t.y]++;
      int cur = -1;
      for (auto t : f[i]) {
        if (cnt[t.y]) {
          cur = t.y;
          break;
        }
      }
      for (auto t : f[i+1]) cnt[t.y]--;
      if (~cur) {
        ans[cur] += cx[i+1]-cx[i];
      }
    }
    
    // rain down
    queue<int> q;
    for (int i = 1; i <= n; i++) {
      if (!in[i]) q.push(i);
    }
    while (!q.empty()) {
      int v = q.front();
      q.pop();
      for (auto u : adj[v]) {
        ans[u] += ans[v];
        if (--in[u] == 0) q.push(u);
        assert(in[u] >= 0);
      }
    }
    for (int i = 0; i < cx.size(); i++) f[i].clear();
    for (int i = 1; i <= n; i++) {
      pri(ans[i]);
      adj[i].clear();
    }
  }
}




