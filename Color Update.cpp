struct range {
		range(int l = 0) { this->l = l; }
		range(int l, int r, int v) {
			this->l = l;
			this->r = r;
			this->v = v;
		}
		int l, r;
		int v;
		bool operator < (const range &b) const { return l < b.l; }
};

set<range> ranges;

void split (int x) {
  auto it = ranges.lower_bound(x);
  if (it == ranges.begin()) return;
  it--;
  if (it->r > x) {
    auto cur = *it;
    ranges.erase(it);
    ranges.insert(range(cur.l, x, cur.v));
    ranges.insert(range(x, cur.r, cur.v));
  }
}

vector<range> update (int l, int r, int v) { // open interval
  vector<range> ans;
  if (l >= r) return ans;
  split(l), split(r);
  for (auto it = ranges.lower_bound(l); it != ranges.end() && it->l < r; it++) {
    ans.push_back(*it);
  }
  ranges.erase(ranges.lower_bound(l), ranges.lower_bound(r));
  ranges.insert(range(l, r, v));
  return ans;
}

int query (int v) {
  auto it = ranges.upper_bound(v);
  if (it == ranges.begin()) {
    return -1;
  }
  it--;
  return it->r >= v ? it->v : -1;
}
