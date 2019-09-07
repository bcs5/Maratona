#include <bits/stdc++.h>
using namespace std;
#define x first
#define y second
const int mx = 112345;
typedef pair<int, int> ii;
  
const double inf = 1e100, eps = 1e-9;
  
int cmp (double a, double b = 0) {
  if (abs(a-b) < eps) return 0;
  return (a < b) ? -1 : +1;
}
  
struct PT {
  double x, y;
  PT (double x = 0, double y = 0) : x(x), y(y) {};
  PT operator + (const PT & p) { return PT(x+p.x, y+p.y);}
  PT operator - (const PT & p) { return PT(x-p.x, y-p.y);}
  PT operator * (const double c) { return PT(x*c, y*c);}
    bool operator <(const PT &p) const {
    if(cmp(x, p.x) != 0) return x < p.x;
    return cmp(y, p.y) < 0;
  }
};

double eval (double x, PT a, PT b) {
  double k =  (x-a.x)/(b.x-a.x);
  return (a + (b-a)*k).y;
}

int pg;
struct Line {
  PT a, b;
  int id;
  bool operator < (const Line &other) const {
    return cmp(eval(pg, a, b), eval(pg, other.a, other.b)) > 0;
  }
};
set<Line> s;
set<Line>::iterator line[mx];
map<int, vector<int>> ending;
int nxt[mx], final[mx];
  
int dfs (int id) {
  if (nxt[id] == id) return final[id];
  return dfs(nxt[id]);
}
  
int main () {
  ios::sync_with_stdio(0);
  cin.tie(0);
  int n;
  cin >> n;
  vector<Line> v;
  v.push_back(Line());
  vector<int> cx;
  vector<ii> ev;
  for (int i = 1; i <= n; i++) {
    int a, b, c, d;
    cin >> a >> b >> c >> d;
    PT e(a, b);
    PT f(c, d);
    if (f < e) swap(e, f);
    v.push_back(Line{e, f, i});
    ev.push_back({e.x, -i});
    ev.push_back({f.x, i});
    cx.push_back(a);
    cx.push_back(c);
    if (b < d) {
      ending[a].push_back(i);
      final[i] = a;
    } else {
      ending[c].push_back(i);
      final[i] = c;
    }
  }
  int Q;
  cin >> Q;
  final[0] = Q;
  cx.push_back(Q);
  sort(cx.begin(), cx.end());
  cx.erase(unique(cx.begin(), cx.end()), cx.end());
  sort(ev.begin(), ev.end());
  iota(nxt, nxt+n+1, 0);
  for (int i = 0, k = 0; i < cx.size(); i++) {
    pg = cx[i];
    ii cur(pg, 0);
    while (k < ev.size() && ev[k] <= cur) {
      line[-ev[k].y] = s.insert(v[-ev[k].y]).x;
      k++;
    }
    for (auto u : ending[cx[i]]) {
      if (next(line[u]) != s.end()) {
        nxt[u] = next(line[u])->id;
      }
    }
    if (pg == Q) {
      nxt[0] = s.begin()->id;
    }
    cur = ii(pg, 1e9);
    while (k < ev.size() && ev[k] <= cur) {
      s.erase(line[ev[k].y]);
      k++;
    }
  }
  cout << dfs(0) << endl;
}
