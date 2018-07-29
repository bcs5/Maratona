#include <bits/stdc++.h>

using namespace std;

const int N = 11234;

int k, adj[N], ant[2*N], to[2*N], weight[2*N];

void add(int a, int b, int w, bool f = 1){
	ant[k] = adj[a], adj[a] = k, to[k] = b, weight[k] = w;
	k++;
	if(f) add(b, a, w, 0);
}

int par[N], dpar[N], big[N], sz[N], h[N];

void dfs(int v, int p, int w, int hght){
	par[v] = p;
	dpar[v] = w;
	big[v] = -1;
	sz[v] = 1;
	h[v] = hght;
	for(int i = adj[v]; ~i; i = ant[i]){
		if(to[i] != p){
			dfs(to[i], v, weight[i], hght+1);
			sz[v] += sz[to[i]];
			if(big[v] == -1 || sz[to[i]] > sz[big[v]]){
				big[v] = to[i];
			}
		}
	}
}

int chain[N], chainL[N], ind[N], chainNo, head[1000];
vector<int> st;
vector<int> tree[1000];

void build(vector<int> &tree) {  // build the tree
	int n = tree.size()>>1;
	for(int i = n - 1; i > 0; --i) tree[i] = max(tree[i<<1], tree[(i<<1)|1]);
}

void upd(int p, int value, vector<int> &tree) {  // set value at position p
	int n = tree.size()>>1;
	for(tree[p += n] = value; p > 1; p >>= 1) tree[p>>1] = max(tree[p], tree[p^1]);
}

int rmq(int l, int r, vector<int> &tree) {  // sum on interval [l, r)
	int res = 0;
	int n = tree.size()>>1;
	for(l += n, r += n; l < r; l >>= 1, r >>= 1) {
		if(l&1) res = max(res, tree[l++]);
		if(r&1) res = max(res, tree[--r]);
	}
	return res;
}
void HLD(int v, int p, int cInd){
	if(cInd == 0) head[chainNo] = v;
	chain[v] = chainNo;
	ind[v] = cInd;
	
	st.push_back(v);
	
	if(~big[v]){
		HLD(big[v], v, cInd+1);
	}else{
		chainL[chainNo] = st.size();
		tree[chainNo].resize(chainL[chainNo]<<1);
		int n = chainL[chainNo];
		for(int i = n-1; ~i; i--){
			tree[chainNo][i+n] = dpar[st[i]];
			st.pop_back();
		}
		build(tree[chainNo]);
		chainNo++;
	}
	for(int i = adj[v]; ~i; i = ant[i]){
		if(to[i] != p && to[i] != big[v]){
			HLD(to[i], v, 0);
		}
	}
}

int up(int v){
	return (head[chain[v]] != v) ? head[chain[v]] : (par[v] != -1 ? par[v] : v);
}
int LCA(int a, int b){
	while(chain[a] != chain[b]){
		if(par[a] == -1 || h[up(a)] < h[up(b)]) swap(a, b);
		a = up(a);
	}
	return h[a] < h[b] ? a : b;
}

int query_up(int a, int b){
	int curr, ans = 0;
	while(chain[a] != chain[b]){
		curr = chain[a];
		ans = max(ans, rmq(ind[head[curr]], ind[a]+1, tree[curr]));
		a = par[head[curr]];
	}
	curr = chain[a];
	ans = max(ans, rmq(ind[b]+1, ind[a]+1, tree[curr]));
	return ans;
}
int a[N], b[N];
int main(){
	int t;
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin >> t;
	while(t--){
		int n;
		cin >> n;
		memset(adj, -1, sizeof adj);
		k = 0;
		for(int i = 0; i < n-1; i++){
			int w;
			cin >> a[i] >> b[i] >> w;
			add(a[i], b[i], w);
		}
		dfs(1, -1, 0, 0);
		HLD(1, -1, 0);
		string s;
		while(cin >> s){
			if(s[0] == 'D') break;
			int x, y;
			cin >> x >> y;
			if(s[0] == 'Q'){
				int z = LCA(x, y);
				cout << max(query_up(x, z), query_up(y, z)) << endl;
			}else{
				x--;
				int z = h[a[x]] > h[b[x]] ? a[x] : b[x];
				upd(ind[z], y, tree[chain[z]]);
			}
		}
	}
}
