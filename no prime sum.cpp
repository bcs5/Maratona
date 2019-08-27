#include <bits/stdc++.h>
using namespace std;

const int mx = 3123;

const int ms = 3e3; // Quantidade maxima de vertices
const int me = 1e6; // Quantidade maxima de arestas

int adj[ms], to[me], ant[me], wt[me], z, n;
int copy_adj[ms], fila[ms], level[ms];

void clear() { // Lembrar de chamar no main
  memset(adj, -1, sizeof adj);
  z = 0;
}

void add(int u, int v, int k) {
  to[z] = v;
  ant[z] = adj[u];
  wt[z] = k;
  adj[u] = z++;
  swap(u, v);
  to[z] = v;
  ant[z] = adj[u];
  wt[z] = 0; // Lembrar de colocar = 0
  adj[u] = z++;
}

int bfs(int source, int sink) {
  memset(level, -1, sizeof level);
  level[source] = 0;
  int front = 0, size = 0, v;
  fila[size++] = source;
  while(front < size) {
    v = fila[front++];
    for(int i = adj[v]; i != -1; i = ant[i]) {
      if(wt[i] && level[to[i]] == -1) {
      level[to[i]] = level[v] + 1;
      fila[size++] = to[i];
      }
    }
  }
  return level[sink] != -1;
}

int dfs(int v, int sink, int flow) {
  if(v == sink) return flow;
  int f;
  for(int &i = copy_adj[v]; i != -1; i = ant[i]) {
    if(wt[i] && level[to[i]] == level[v] + 1 && 
      (f = dfs(to[i], sink, min(flow, wt[i])))) {
      wt[i] -= f;
      wt[i ^ 1] += f;
      return f;
    }
  }
  return 0;
}

const int SOURCE = 2001, SINK = 2002;
int maxflow(int source, int sink) {
  int ret = 0, flow;
  while(bfs(source, sink)) {
    memcpy(copy_adj, adj, sizeof adj);
    while((flow = dfs(source, sink, 1 << 30))) {
      ret += flow;
    }
  }
  return ret;
}

vector<int> coverU, U, coverV, V; // ITA - Partição U LEFT, partição V RIGHT, 1 indexed
bool Zu[mx], Zv[mx];
int pairU[mx], pairV[mx];
void getreach(int u) {
  if (u == 0 || Zu[u]) return;
  Zu[u] = true;
  for (int i = adj[u]; ~i; i = ant[i]) {
    int v = to[i];
    if (v == SOURCE || v == pairU[u]) continue;
    Zv[v] = true;
    getreach(pairV[v]);
  }
}

void minimumcover () {
  for (auto i : U) {
    for (int j = adj[i]; ~j; j = ant[j]) {
      if (!(j&1) && !wt[j]) {
        pairU[i] = to[j], pairV[to[j]] = i;
      }
    }
  }
  memset(&Zu, 0, sizeof Zu);
  memset(&Zv, 0, sizeof Zv);
  for (auto u : U) {
    if (pairU[u] == 0) getreach(u);
  }
  coverU.clear(), coverV.clear();
  for (auto u : U) {
    if (!Zu[u]) coverU.push_back(u);
  }
  for (auto v : V) {
    if (Zv[v]) coverV.push_back(v);
  }
}

bool isp[212345];
int main () {
  memset(isp, 1, sizeof isp);
  for (int i = 2; i < 212345; i++) {
    if(!isp[i]) continue;
    for (int j = 2*i; j < 212345; j += i) isp[j] = 0;
  }
  int n;
  cin >> n;
  int v[n+1];
  clear();
  for (int i = 1; i <= n; i++) {
    cin >> v[i];
    for (int j = 1; j < i; j++) {
      if (isp[v[i] + v[j]]) {
        if (v[i]&1) add(i, j, 1);
        else add(j, i, 1);
      }
    }
    if (v[i]&1) add(SOURCE, i, 1), U.push_back(i);
    else add(i, SINK, 1), V.push_back(i);
  }
  cout << maxflow(SOURCE, SINK) << endl;
  minimumcover();
  vector<int> ans;
  for (auto u: coverU) ans.push_back(u);
  for (auto u: coverV) ans.push_back(u);
  for (int i = 0; i < ans.size(); i++) {
    cout << v[ans[i]] << " \n"[i+1 == ans.size()];
  }
}
