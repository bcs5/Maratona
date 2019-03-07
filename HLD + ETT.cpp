//HLD + Euler Tour by adamant http://codeforces.com/blog/entry/53170

struct hld_t {
  vector<vector<int>> g;
  vector<int> sz, par;  
  vector<int> h, in, rin, out, nxt;
  int t, n;
  
  hld_t (int _n) : n(_n) {
    h.resize(n);
    in.resize(n);
    rin.resize(n);
    out.resize(n);
    par.resize(n);
    sz.resize(n);
    g.resize(n);
    nxt.resize(n);
    t = 0;
  }
  
  void build (int v) {
    dfs_sz(v, v);
    hld(v, v);
  }
  
  void add(int x, int y) {
    g[x].push_back(y);
    g[y].push_back(x);
  }

  void dfs_sz (int v, int p) {
    sz[v] = 1, par[v] = p;
    for (int i = 0; i < g[v].size(); i++) {
      int &u = g[v][i];
      if (u == p) {
        swap(u, g[v].back());
        g[v].pop_back();
        i--;
      } else {
        h[u] = h[v]+1;
        dfs_sz(u, v);
        sz[v] += sz[u];
        if (sz[u] > sz[g[v][0]]) {
          swap(u, g[v][0]);
        }
      }
    }
  }

  void hld (int v, int p) {
    in[v] = t++;
    rin[in[v]] = v;
    for (auto &u : g[v]) {
      nxt[u] = u == g[v][0] ? nxt[v] : u;
      hld(u, v);
    }
    out[v] = t;
  }

  int lca (int u, int v) {
    while(!inSubtree(nxt[u], v)) u = par[nxt[u]];
    while(!inSubtree(nxt[v], u)) v = par[nxt[v]];
    return in[u] < in[v] ? u : v;
  }

  bool inSubtree (int u, int v) { // is v in the subtree of u?
    return in[u] <= in[v] && in[v] < out[u];
  }

  vector< pair<int, int> > getPathtoAncestor (int a, int p) {
    vector< pair<int, int> > ans;
    while (nxt[a] != nxt[p]) {
      ans.emplace_back(in[nxt[a]], in[a]);
      a = par[nxt[a]];
    }
    ans.emplace_back(in[p], in[a]);  // in[p]+1;
    return ans;
  }
  
  int dist (int a, int b) {
    return h[a] + h[b] - 2 * h[lca(a, b)];
  }
};
