vector<int> s(n+1), p(n+1);
vector<bool> used(n+1);
auto dfs_sz = [&](int v, int v0, auto&& dfs_sz)->void{
  s[v] = 1;
  for(auto u : g[v]){
    if(u==v0 || used[u]) continue;
    dfs_sz(u, v, dfs_sz);
    s[v] += s[u];
  }
};
auto cen = [&](int v, int v0, int n, auto&& cen)->int{
  for(auto u : g[v]){
    if(u==v0 || used[u]) continue;
    if(s[u] > n/2)
      return cen(u, v, n, cen);
  }
  return v;
};
/*
vector<vector<pair<int,int>>> anc(n+1);
auto dfs_dist = [&](int v, int v0, int c,
      int cur, auto&& dfs_dist)->void{
  for(auto u : g[v]){
    if(u==v0 || used[u]) continue;
    dfs_dist(u, v, c, cur+1, dfs_dist);
  }
  anc[v].push_back({c, cur});
}; */
ll ans=0;
auto build = [&](int v, int c0, auto&& build)->void{
  dfs_sz(v, 0, dfs_sz);
  int c = cen(v, 0, s[v], cen);
  p[c] = c0;
  /* dfs_dist(c, 0, c, 0, dfs_dist); */
  used[c] = true;

  //Problem-specific stuff here

  for(auto u : g[c])
      if(!used[u])
          build(u, c, build);
};
build(1, 0, build);