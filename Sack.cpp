
void solve(int v, int par, bool f){
	int big = -1;
	for(auto &u : adj[v]){
		if(u != par && (big == -1 || Size[u] > Size[big])){
			big = u;
		}
	}
	for(auto &u : adj[v]){
		if(u == par || u == big) continue;
		solve(u, v, 0);
	}
	if(~big) solve(big, v, 1);
	
	// add curr info
	add(cnt[v[v]], -1);
	cnt[v[a]]++;
	add(cnt[v[v]], +1);
	
	//add smallest children
	for(auto &u : adj[v]){
		if(u == par|| u == big) continue;
		for(int i = st[u]; i < en[u]; i++){
			add(cnt[ett[i]], -1);
			cnt[ett[i]]++;
			add(cnt[ett[i]], +1);
		}
	}
	
	// ans queries for v subtree
	for(auto &q : Q[v]){
		ans[q.first] = query(mx-1)-query(q.second-1);
	}
	
	// clear
	if(!f){
		for(int i = st[v]; i < en[v]; i++){
			add(cnt[ett[i]], -1);
			cnt[ett[i]]--;
			add(cnt[ett[i]], +1);
		}
	}
}
