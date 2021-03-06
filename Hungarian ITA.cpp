#define MAXN 2009
#define MAXM 2009
#define INF 0x3f3f3f3f

int n, m;
int pu[MAXN], pv[MAXN], cost[MAXN][MAXM];
int pairV[MAXN], way[MAXM], minv[MAXM];
bool used[MAXM];

void clear () {
  memset(pu, 0, sizeof pu);
  memset(pv, 0, sizeof pv);
  memset(way, 0, sizeof way);
}

void hungarian () {
  memset(pairV, 0, sizeof pairV);
  for (int i = 1, j0 = 0; i <=n; i++) {
    pairV[0] = i;
    memset(minv, INF, sizeof minv);
    memset(used, false, sizeof used);
    do {
      used[j0] = true;
      int i0 = pairV[j0], delta = INF, j1;
      for (int j = 1; j <= m; j++) {
        if (used[j]) continue;
        int cur = cost[i0][j] - pu[i0] - pv[j];
        if (cur < minv[j])
          minv[j] = cur, way[j] = j0;
        if (minv[j] < delta)
          delta = minv[j], j1=j;
      }
      for (int j = 0; j <= m; j++) {
        if (used[j])
          pu[pairV[j]] += delta, pv[j] -= delta;
        else minv[j] -= delta;
      }
      j0 = j1;
    } while (pairV[j0] != 0);
    do {
      int j1 = way[j0];
      pairV[j0] = pairV[j1];
      j0 = j1;
    } while (j0);
  }
}
