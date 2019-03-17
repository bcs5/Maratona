class Solution {
public:
  const int mod = 1e9+7;
  vector<int> find (string s, string w) {   // kmp também serve
    long long hashkey1 = 0;
    long long pot256[w.size()+1];
    pot256[0] = 1;
    for (int i = 0; i < w.size(); i++) {
      hashkey1 = ((hashkey1<<8) + w[i]) % mod;
      pot256[i+1] = (pot256[i]<<8)%mod;
    }
    long long hashkey2 = 0;
    vector<int> res;
    for (int i = 0, l = 0; i < s.size(); i++) {
      hashkey2 = ((hashkey2<<8) + s[i]) % mod;
      if (i-l+1 > w.size()) {
        hashkey2 = (((hashkey2 - (s[l]*pot256[w.size()]%mod))+mod)%mod);
        l++;
      }
      if (i-l+1 == w.size() && hashkey1 == hashkey2) res.push_back(i);
    }
    return res;
  }
  
  bool wordBreak(string s, vector<string>& wordDict) {
    vector<int> pos[s.size()+1];
    for ( auto &w : wordDict) {
      auto res = find(s, w);
      for (auto i : res) pos[i+1].push_back(i+1-w.size());
    }
    vector<bool> dp(s.size()+1, 0); 
    dp[0] = 1;
    for (int i = 1; i <= s.size(); i++) {
      for (auto x : pos[i]) {
        dp[i] = dp[i] or dp[x];
      }
    }
    return dp[s.size()];
  }
};
