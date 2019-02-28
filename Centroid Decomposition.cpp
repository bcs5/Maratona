#include <bits/stdc++.h>

using namespace std;
template<typename T>
struct CentroidDecomposition {
  vector<int> sz, h, dad;
  vector<vector<int, T>> adj, dis;
  vector<bool> removed;
  
  
  CentroidDecomposition (int n) {
    sz.resize(n);
    h.resize(n);
    dis.resize(n, vector<int>(30));
    adj.resize(n);
    removed.resize(n, 0);
  }
  
  void dfsSize (int v, int par){
    sz[v] = 1;
    for (int u : adj[v]){
      if (u == par || removed[u]) continue;
      dfsSize(u, v);
      sz[v] += sz[u];
    }
  }
  
  int getCentroid (int v, int par, int tam){
    for (int u : adj[v]) {
      if (u == par || removed[u]) continue;
      if ((sz[u]<<1) > tam) return getCentroid(u, v, tam);
    }
    return v;
  }

  void setDis (int v, int par, int nv, long long d){
    dis[v][nv] = d;
    for (int u : adj[v]) {
      if (u == par || removed[u]) continue;
      setDis(u, v, nv, d + 1);
    }
  }

  void decompose (int v, int par = -1, int nv = 0){
    dfsSize(v, par);
    int c = getCentroid(v, par, sz[v]);
    dad[c] = par;
    removed[c] = 1;
    h[v] = nv;
    setDis(c, par, nv, 0);
    for (int u : adj[c]){
      if (!removed[u]){
        decompose(u, c, nv + 1);
      }
    }
  }
  
  int operator [] (const int idx) const {
    return dad[idx];
  }
  
  T dist (int ct, int v) {
    return dis[ct][h[ct]];
  }
};

