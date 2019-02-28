class lca_t {
public:
  int n;
  int max_log, t;
  vector<int> h, in, out;
  vector<vector<int>> adj, up;

  lca_t(int _n) : n(_n) {
    max_log = 0;
    while ((1 << max_log) <= n)
      max_log++;
    h.resize(n);
    in.resize(n);
    out.resize(n);
    adj.resize(n);
    up.resize(n, vector<int>(max_log));
    t = 0;
  }

  bool anc(int x, int y) {
    return in[x] <= in[y] && out[x] >= out[y];
  }

  int lca(int x, int y) {
    if (anc(x, y))
      return x;
    if (anc(y, x))
      return y;
    for (int i = max_log - 1; i >= 0; i--)
      if (!anc(up[x][i], y))
        x = up[x][i];
    return up[x][0];
  }

  void add(int x, int y) {
    adj[x].push_back(y);
    adj[y].push_back(x);
  }
  
  void dfs (int v, int p) {
    in[v] = t++;
    up[v][0] = p;
    for (int i = 1; i < max_log; i++)
      up[v][i] = up[up[v][i - 1]][i - 1];
    for (int i = 0; i < (int) adj[v].size(); i++) {
      int u = adj[v][i];
      if (u == p)
        continue;
      h[u] = h[v] + 1;
      dfs(u, v);
    }
    out[v] = t - 1;
  };

  void set_root(int x) {
    int t = 0;
    h[x] = 0;
    dfs(x, x);
  }
};
