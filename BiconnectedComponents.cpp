int num[ms], low[ms], timer, rch;
//int art[ms], bridge[me];
int bc[ms], nbc;
int st[ms], top;
bool f[me];

void generateBc (int v) {
  ++nbc;
  while (top) {
    int u = st[--top];
    bc[u] = nbc;
    if (v == u) break;
  }
}

void dfs (int v, int p) {
  st[top++] = v;
  low[v] = num[v] = ++timer;
  for (int i = adj[v]; i != -1; i = ant[i]) {
    if (f[i] || f[i^1]) continue;
    f[i] = 1;
    int u = to[i];
    if (num[u] == -1) {
      dfs(u, v);
      //if (low[u] > num[v]) bridge[i] = bridge[i^1] = 1;
      //art[v] |= p != -1 && low[u] >= num[v];
      //if (p == -1 && rch > 1) art[v] = 1;
      //else rch ++;
      low[v] = min(low[v], low[u]);
    } else {
      low[v] = min(num[v], low[u]);
    }
  }
  if (low[v] == num[v]) generateBc(v);
}
