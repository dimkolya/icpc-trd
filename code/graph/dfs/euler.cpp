ll n;
vector<vector<pair<ll,ll>>> g; // vertex, edge_index
vector<bool> used; // size=m
vector<ll> first; // size=n
vector<pair<ll,ll>> ans;
bool check() {
  ll odd = 0;
  for (ll i = 0; i < n; ++i)
    odd += g[i].size() % 2;
  if (odd > 2) return false;
  vector<bool> used(n);
  for (ll i = 0; i < n; ++i)
    if (g[i].size() > 0)
      dfs(i, used);
  for (ll i = 0; i < n; ++i)
    if (g[i].size() > 0 && !used[i])
      return false;
  return true;
}
// cycle if all even
// path if starts at odd
void euler(ll v){
  while(first[v] < g[v].size()){
    auto [u,i] = g[v][first[v]];
    ++first[v];
    if(!used[i]){
      used[i] = true;
      euler(u);
      ans.emplace_back(v,u);
    }
  }
}