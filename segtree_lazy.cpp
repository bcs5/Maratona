int lazy[mx<<2], tree[mx<<2];

void apply (int p, int l, int r) {
    if (lazy[p] == 0) return;
    tree[p] += lazy[p] * (r-l+1);
    if (l != r) {
        int lc = p<<1, rc = lc|1;
        lazy[lc] += lazy[p]; lazy[rc] += lazy[p];
    }
    lazy[p] = 0;
}
 
void upd(int p, int l, int r, int i, int j, int val) {
    apply(p,l,r);
    if (l > j || r < i) return;
    if (l >= i && r <= j){ 
      lazy[p] = val; apply(p, l, r);
      return;
    }
    int lc = p<<1, rc = lc|1, m = (l+r)>>1;
    upd(lc, l, m, i, j, val), upd(rc, m+1, r, i, j, val);
    tree[p] = tree[lc] + tree[rc];
}

int query(int p, int l, int r, int i, int j) {
  if(l>j || r < i) return 0;
  apply(p, l, r);
  if(i<=l && r <=j) return tree[p];
  int lc = p<<1, rc = lc|1, m = (l+r)>>1;
  return query(lc, l, m, i, j) + query(rc, m+1, r, i, j);
}
