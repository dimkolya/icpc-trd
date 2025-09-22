struct graph {
  graph() {
    ll m;
    cin >> n >> m;
    g.resize(n), gr.resize(n);
    while (m--) {
      ll b, e;
      cin >> b >> e;
      g[b - 1].push_back(e - 1);
      gr[e - 1].push_back(b - 1);
    }
  }
  void solve() {
    vector<bool> used(n, false);
    vector<ll> t;
    for (ll i = 0; i < n; ++i)
      if (!used[i])
        dfs1(i, used, t);
    std::reverse(t.begin(), t.end());
    ll k = 0;
    vector<ll> comp(n, -1);
    for (ll v : t)
      if (comp[v] == -1)
        dfs2(v, k++, comp);
    // vector<ll> ts; topsort of new vertices->
    // vector<bool> f(k);
    // for (ll i : t) {
    //   if (f[comp[i]])
    //     continue;
    //   f[comp[i]] = true;
    //   ts.push_back(comp[i]);
    // } ts.reverse<-
    set<pair<ll, ll>> edges;
    for (ll v = 0; v < n; ++v)
      for (ll u : g[v])
        if (comp[v] != comp[u])
          edges.emplace(comp[v], comp[u]);
    // return edges;
  }
private:
  ll n;
  vector<vector<ll>> g, gr;
  void dfs1(ll v, vector<bool> &used, vector<ll> &t) {
    used[v] = true;
    for (ll u : g[v])
      if (!used[u])
        dfs1(u, used, t);
    t.push_back(v);
  }
  void dfs2(ll v, ll k, vector<ll> &comp) {
    comp[v] = k;
    for (ll u : gr[v])
      if (comp[u] == -1)
        dfs2(u, k, comp);
  }
};