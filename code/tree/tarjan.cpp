vector<int> anc(n+1), lca(Q);
vector<bool> used(n+1);
vector<vector<pair<int,int>>> q(n+1);
for(int i=0; i<Q; ++i){
  int v,u; cin >> v >> u;
  q[v].push_back({u,i});
  q[u].push_back({v,i});
}
auto dfs = [&](int v, int v0, auto&& dfs)->void{
  p[v] = v; s[v] = 1; anc[v] = v;
  for(auto u : g[v]){
    if(u==v0) continue;
    dfs(u,v,dfs);
    unite(v,u);
    anc[root(v,root)] = v;
  }
  used[v] = true;
  for(auto [u,i] : q[v])
    if(used[u])
      ans[i] = anc[root(u,root)];
};
dfs(1,0,dfs);
for(auto v : lca)
  cout << v << "\n";