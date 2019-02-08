int num[ms], low[ms], timer;
int art[ms], bridge[me], rch;
int bc[ms], nbc;
stack<int> st;
bool f[me];

void generateBc (int v) {
  ++nbc;
  while (!st.empty()) {
    int u = st.top();
    st.pop();
    bc[u] = nbc;
    if (v == u) break;
  }
}

void dfs (int v, int p) {
  st.push(v);
  low[v] = num[v] = ++timer;
  for (int i = adj[v]; i != -1; i = ant[i]) {
    if (f[i] || f[i^1]) continue;
    f[i] = 1;
    int u = to[i];
    if (num[u] == -1) {
      dfs(u, v);
      if (low[u] > num[v]) bridge[i] = bridge[i^1] = 1;
      art[v] |= p != -1 && low[u] >= num[v];
      if (p == -1 && rch > 1) art[v] = 1;
      else rch ++;
      low[v] = min(low[v], low[u]);
    } else {
      low[v] = min(low[v], num[u]);
    }
  }
  if (low[v] == num[v]) generateBc(v);
}

void biCon (int n) {
  memset(num, -1, sizeof num);
  for (int i = 0; i < n; i++) {
    if (num[i] == -1) dfs(i, 0);
  }
}
