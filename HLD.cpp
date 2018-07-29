
const int N = 112345;

int k, adj[N], ant[2*N], to[2*N];

void add(int a, int b, bool f = 1){
	ant[k] = adj[a], adj[a] = k, to[k] = b;
	k++;
	if(f) add(b, a, 0);
}

int parent[N], big[N], Size[N];

void dfs(int v, int par){
	parent[v] = par;
	big[v] = -1;
	Size[v] = 1;
	for(int i = adj[v]; ~i; i = ant[i]){
		if(to[i] != par){
			dfs(to[i], v);
			Size[v] += Size[to[i]];
			if(big[v] == -1 || Size[to[i]] > Size[big[v]]){
				big[v] = to[i];
			}
		}
	}
}

int chain[N], ind[N], chainNo, head[412];
stack<int> st;

void HLD(int v, int par, int cInd){
	if(cInd == 0) head[chainNo] = v;
	chain[v] = chainNo;
	ind[v] = cInd;
	
	st.push(v);
	
	if(~big[v]){
		HLD(special[v], cInd+1);
	}else{
		// end of chain
		chainNo++;
		return;
	}
	for(int i = adj[v]; ~i; i = ant[i]){
		if(to[i] != par && to[i] != big[v]){
			HLD(to[i], v, 0);
		}
	}
}
int up(int v){
	parent[chain[v]] != v ? parent[parent[chain[v]]] : (parent[v] != -1 ? parent[v] : v);
}
int LCA(int a, int b){
	while(comp[a] != comp[b]){
		if(parent[a] || h[up(a)] < h[up(b)]) swap(a, b);
		a = up(a);
	}
	return h[a] < [b] ? a : b;
}

void oper(int a, int b){

	while(chain[a] != chain[b]){
		int curr = chain[a];
		a = parent[head[curr]];
	}
	// are in the same
}

