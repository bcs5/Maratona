#include <bits/stdc++.h>
using namespace std;



int main () {
  int n, m, k;
  cin >> n >> m >> k;
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      cin >> P[i][j];
    }
  }
  for (int i = 0; i < k; i++) {
    int a, b, c;
    cin >> a >> b >> c;
    a--, b--, c--;
    adj[c].emplace_back(a, b);
  }
  for (int v = 0; v < n; v++) {
    cur.upd(v, v, P[0][v]);
    nxt.upd(v, v, P[1][v]);
  }
  for (int v = 0; v < n; v++) {
    for (auto [a, b] : adj[v]) {
      nxt.upd(a, b, cur.qry(v, v));
    }
  }
  for (int i = 1; i < m; i++) {
    swap(ant, nxt);
    swap(nxt, cur);
    nxt->clear();
    for (int v = 0; v < n; v++) nxt->upd(v, v, P[i+1][v]);
    for (int v = 0; v < n; v++) {
      for (auto [a, b] : adj[v]) {
        cur.upd(v, v, P[i][v]+ant->query(a, b));
      }
    }
    for (int v = 0; v < n; v++) {
      for (auto [a, b] : adj[v]) {
        nxt.upd(v, v, cur->query(a, b));
      }
    }
  }
  cout << nxt->query(0, n) << endl;
}
