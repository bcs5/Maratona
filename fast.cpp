#include <bits/stdc++.h>
using namespace std;
#define all(foo) foo.begin(), foo.end()
const int mx = 112345;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
vector<pair<vector<int>, int>> v;
vector<pair<vector<int>, int>> u;

int par[mx];

map<string, int> mp;
int t;

int main () {
  int n; 
  for (int i = 0; i < n; i++) {
    char o;
    int k;
    cin >> o >> k;
    pair<vector<int>, int> a;
    for (int j = 0; j < k; j++) {
      string s;
      cin >> s;
      if (!mp.count(s)) mp[s] = t++;
      a.first.push_back(mp[s]);
    }
    if (o == 'H') u.push_back(a);
    else v.push_back(a);
  }
  memset(par, -1, sizeof par);
  shuffle(v.begin(), v.end(), rng);
  for (int i = 0; i < v.size()/2; i+=2) {
    copy(all(v[i+1].first), back_inserter(v[i].first));
    sort(all(v[i].first));
    v[i].first.erase(unique(all(v[i].first)), v[i].first.end());
    par[v[i].second] = v[i+1].second;
    u.push_back(v[i]);
  }
  
}

























