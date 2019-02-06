//HLD + Euler Tour by adamant http://codeforces.com/blog/entry/53170

vector<int> g[ms];
int sz[ms], par[ms], h[ms];
int t, in[ms], out[ms], rin[ms], nxt[ms];

void dfs_sz (int v = 0, int p = -1) {
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

void hld (int v = 0, int p = -1) {
  in[v] = t++;
  rin[in[v]] = v;
  for (auto &u : g[v]) {
    nxt[u] = u == g[v][0] ? nxt[v] : u;
    hld(u, v);
  }
  out[v] = t;
}

int up (int v) {
  return (nxt[v] != v) ? nxt[v] : (~par[v] ? par[v] : v);
}

int getLCA (int a, int b) {
  while (nxt[a] != nxt[b]) {
    if (h[a] == 0 || h[up(a)] < h[up(b)]) swap(a, b);
    a = up(a);
  }
  return h[a] < h[b] ? a : b;
}

vector< pair<int, int> > getPathtoAncestor (int a, int p = 0) {
  vector< pair<int, int> > ans;
  while (nxt[a] != nxt[p]) {
    ans.push_back({in[nxt[a]], in[a]});
    a = par[nxt[a]];
  }
  return ans;
}
