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

const int magic = 113;


struct seg {
  int n;
  vector<pair<int, char>> t;
  void build(string &v) {
    n = v.size();
    t.resize(n<<1, {1e9-1, 0});
    for (int i = 0; i < n; i++) t[i+n].y = v[i];
  }

  void update(int l, int r, pair<int, char> value) {
    for(l += n, r += n; l < r; l >>= 1, r >>= 1) {
      if(l&1) t[l] = value, l++;
      if(r&1) --r, t[r] = value;
    }
  }

  void push() { // push modifications to leafs
    for(int i = 1; i < n; i++) {
      t[i<<1] = min(t[i], t[i<<1]);
      t[i<<1|1] = min(t[i<<1|1], t[i]);
      t[i] = {1e9, 0};
    }
  }
};

int main () {
  ios::sync_with_stdio(0);
  cin.tie(0);
  string s;
  cin >> s;
  int n = s.size(), q;
  cin >> q;
  vector<vector<string>> v(magic);
  vector<vector<vector<int>>> coord(magic);
  vector<vector<seg>> tree(magic);
  
  for (int i = 1; i < magic; i++) {
    v[i].resize(i);
    coord[i].resize(i);
    tree[i].resize(i);
    for (int j = 0; j < n; j++) {
      v[i][j % i].push_back(s[j]);
      coord[i][j % i].push_back(j);
    }
    for (int j = 0; j < i; j++) {
      tree[i][j%i].build(v[i][j%i]);
    }
    v[i].clear();
  }
  vector<pair<int, char>> ans(n);
  for (int i = 0; i < n; i++) {
    ans[i] = {q, s[i]};
  }
  int i, a, k;
  char c;
  while (q--) {
    cin >> i >> a >> k >> c;
    i--;
    if (a >= magic) {
      int R = i+a*k;
      for (int j = i; j <= R; j += a) {
        ans[j] = {q, c};
      }
    } else {
      int l = lower_bound(all(coord[a][i%a]), i) - coord[a][i%a].begin();
      int r = upper_bound(all(coord[a][i%a]), i+k*a) - coord[a][i%a].begin();
      tree[a][i%a].update(l, r, {q, c});
    }
  }
  for (int i = 1; i < magic; i++) {
    for (int j = 0; j < i; j++) {
      tree[i][j].push();
      int k = coord[i][j].size();
      for (auto u : coord[i][j]) {
        ans[u] = min(ans[u], tree[i][j].t[k]);
        k++;
      }
    }
  }
  for (int i = 0; i < n; i++) {
    s[i] = ans[i].y;
  }
  cout << s << endl;
}
