//HLD + Euler Tour by adamant http://codeforces.com/blog/entry/53170

vector<int> g[ms];
int sz[ms], par[ms], h[ms];
int t, in[ms], out[ms], rin[ms], nxt[ms];

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
  out[v] = t-1;
}

int getLCA (int u, int v) {
  while(!inSubtree(nxt[u], v)) u = p[nxt[u]];
  while(!inSubtree(nxt[v], u)) v = p[nxt[v]];
  return in[u] < in[v] ? u : v;
}

bool inSubtree (int u, int v) { // is v in the subtree of u?
  return in[u] <= in[v] && in[v] <= out[u];
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
