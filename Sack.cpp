int sz[ms];
int t, in[ms], out[ms], rin[ms];

void dfs_sz (int v = 0, int p = -1) {
  in[v] = t++;
  rin[in[v]] = v;
  sz[v] = 1;
  
  for (int i = 0; i < adj[v].size(); i++) {
    int &u = adj[v][i];
    if (u == p) continue;
    dfs_sz(u, v);
    sz[v] += sz[u];
    if (adj[v][0] == p || sz[u] > sz[adj[v][0]]) {
      swap(u, adj[v][0]);
    }
  }
  out[v] = t;
}

void solve (int v, int p, bool f) {
  for (int &u : adj[v]) {
    if (u == p || u == adj[v][0]) continue;
    solve(u, v, 0);
  }
  if (adj[v].size() > 1) solve(adj[v][0], v, 1);

  // add v
  // add smallest children
  for (auto &u : adj[v]) {
    if (u == p|| u == adj[v][0]) continue;
    for (int i = in[u]; i < out[u]; i++) {
      // add rin[i];
    }
  }

  // ans queries for v subtree

  // clear
  if (!f) {
    for (int i = in[v]; i < out[v]; i++) {
      // rem rin[i];
    }
  }
}
