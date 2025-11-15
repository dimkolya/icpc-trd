struct fenwick {
  ll n, m;
  vector<vector<ll>> t;
  fenwick(ll n, ll m) : n(n), m(m) {
    t.resize(n + 1, vector<ll>(m + 1));
  }
  void upd(ll x, ll y, ll v) {// a[x][y] += v
    for (ll i = x + 1; i <= n; i += i & (-i))
      for (ll j = y + 1; j <= m; j += j & (-j))
        t[i][j] += v;
  }
  ll get(ll x, ll y) {// [0, x) [0, y)
    ll res = 0;
    for (ll i = x; i > 0; i -= i & (-i))
      for (ll j = y; j > 0; j -= j & (-j))
        res += t[i][j];
    return res;
  }
  ll get(ll lx,ll rx,ll ly,ll ry) {// [lx,rx) [ly,ry)
    return get(rx,ry)-get(lx,ry)-get(rx,lx)+get(lx,ly);
  }
};