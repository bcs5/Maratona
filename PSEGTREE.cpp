struct node {
  int v, l, r;
  node (): v(0),l(0),r(0){}
} tree[1123456];
int z = 1;

int upd (int p, int l, int r, int pos, int v) {
  if (pos < l || r < pos) return p; 
  if (l == r) {
    tree[z] = tree[p];
    tree[z].v += v;
    return z++;
  }
  int mid = (l+r)>>1, lc, rc;
  lc = upd(tree[p].l, l, mid, pos, v), rc = upd(tree[p].r, mid+1, r, pos, v);
  tree[z].v = tree[lc].v + tree[rc].v;
  tree[z].l = lc, tree[z].r = rc;
  return z++;
}
