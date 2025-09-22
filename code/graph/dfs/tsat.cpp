struct tsat {
  tsat(ll n) : n(n) {
    ll m;
    cin >> m;
    g.resize(2 * n);
    gr.resize(2 * n);
    for (ll i = 0; i < m; ++i) {
      ll i1, e1, i2, e2;
      cin >> i1 >> e1 >> i2 >> e2;
      // i1--, i2--;
      i1 *= 2, i2 *= 2;
      i1 ^= (e1 == 0), i2 ^= (e2 == 0);
      g[i1 ^ 1].push_back(i2);
      g[i2 ^ 1].push_back(i1);
      gr[i2].push_back(i1 ^ 1);
      gr[i1].push_back(i2 ^ 1);
    }
  }
  void solve() {
    vector<bool> used(2 * n, false);
    vector<ll> t;
    for (ll i = 0; i < 2 * n; ++i)
      if (!used[i])
        dfs1(i, used, t);
    std::reverse(t.begin(), t.end());
    ll k = 0;
    vector<ll> comp(2 * n, -1);
    for (ll v : t)
      if (comp[v] == -1)
        dfs2(v, k++, comp);
    for (ll i = 0; i < n; ++i)
      if (comp[2 * i] == comp[2 * i + 1])
        return; // no solution
    vector<bool> solution(n, false);
    for (ll i = 0; i < n; ++i)
      if (comp[2 * i] > comp[2 * i + 1])
        solution[i] = true;
    for (bool i : solution)
      cout << i;
    cout << '\n';
  }
private:
  ll n;
  vector<vector<ll>> g;
  vector<vector<ll>> gr;
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