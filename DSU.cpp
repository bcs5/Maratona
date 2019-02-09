struct dsu {
  vector<int> hist, par, sz;
  void init (int n) {
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
    if (a == b) return;
    if (sz[a] > sz[b]) swap(a, b);
    par[a] = b;
    sz[b] += sz[a];
    hist[a] = t;
  }
  bool same (int a, int b, int t) {
    return root(a, t) == root(b, t);
  }
};
