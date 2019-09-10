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
typedef pair<int, int> ii;
const int mx = 1123456;
int n, t[2 * mx];

void update(int v, int l, int r) {
  for(l += n, r += n+1; l < r; l >>= 1, r >>= 1) {
    if(l&1) t[l++] += v; // Merge
    if(r&1) t[--r] += v; // Merge
  }
}

int query(int p) {
  int res = 0;
  for(p += n; p > 0; p >>= 1) res += t[p]; // Merge
  return res;
}

void push() { // push modifications to leafs
  for(int i = 1; i < n; i++) {
    t[i<<1] += t[i]; // Merge
    t[i<<1|1] += t[i]; // Merge
    t[i] = 0;
  }
}

template <class T, class C = std::less<T>>
struct MaxQueue {
  MaxQueue() {
    clear();
  }

  void clear() {
    id = 0;
    q.clear();
  }

  void push(T x) {
    std::pair<int, T> nxt(1, x);
    while(q.size() > id && cmp(q.back().second, x)) {
      nxt.first += q.back().first;
      q.pop_back();
    }
    q.push_back(nxt);
  }

  T qry() {
    return q[id].second;
  }

  void pop() {
    q[id].first--;
    if(q[id].first == 0) {
      id++;
    }
  }
private:
  std::vector<std::pair<int, T>> q;
  int id;
  C cmp;
};
int v[mx];
int main () {
  ios::sync_with_stdio(0);
  cin.tie(0);
  int m, w;
  cin >> m >> w;
  n = w;
  for (int i = 0; i < m; i++) {
    int k;
    cin >> k;
    vector<ii> ev;
    set<int> cx;
    for (int j = 1; j <= k; j++) {
      cin >> v[j];
      ev.push_back({j-1, -j});
      ev.push_back({w-(k-(j-1)), j});
      //cout << j << " " << (w-(k-j)) << endl;
      cx.insert(j-1);
      cx.insert((w-(k-(j-1))));
    }
    /*if (w != k) {
      ev.push_back({0, w+1});
      ev.push_back({w-k-1, w+1});

      ev.push_back({w-1-(w-k), w+1});
      ev.push_back({w-1, w+1});
      cx.insert(w-k-1);
      cx.insert(w-1-(w-k));
      cx.insert(w-1);
    }*/
    sort(all(ev));
    multiset<int> s;
    int t = 0, last = -1;
    for (auto u : cx) {
      while (t < ev.size() && ev[t] <= ii{u, 0}) {
        s.insert(v[-ev[t++].y]);
      }
      cout << last+1 << " " << u << " " << *s.rbegin() << endl;
      update(last+1, u, *s.rbegin());
      while (t < ev.size() && ev[t] <= ii{u, 1e9}) {
        s.erase(s.find(v[ev[t].y]));
        cout << "rem " << v[ev[t].y] << endl;
        t++;
      }
      last = u;
    }
    cout << endl;
  }
  push();
  for (int i = 0; i < w; i++) {
    cout << query(i) << " \n"[i == w-1];
  }
}
