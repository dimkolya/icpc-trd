struct sptable {
  sptable(const vector<vector<node>> &a) {
    ll n = a.size(), m = a[0].size();
    ll H = __lg(n), W = __lg(m);
    for (ll i = 0; i < n; ++i) {
      for (ll j = 0; j < m; ++j)
        data[0][0][i][j] = a[i][j];
      for (ll w = 1; w <= W; ++w)
        for (ll j = 0; j + (1 << w) <= m; ++j)
          data[0][w][i][j] =
              combine(data[0][w-1][i][j],
                      data[0][w-1][i][j+(1<<(w-1))]);
    }
    for (ll h = 1; h <= H; ++h)
      for (ll i = 0; i + (1 << h) <= n; ++i)
        for (ll w = 0; w <= W; ++w)
          for (ll j = 0; j + (1 << w) <= m; ++j)
            data[h][w][i][j] =
                combine(data[h-1][w][i][j],
                        data[h-1][w][i+(1<<(h-1))][j]);
  }
  ll get(ll x1, ll y1, ll x2, ll y2) const {
    ll h = __lg(x2 - x1);
    ll w = __lg(y2 - y1);
    node r = combine(combine(combine(
        data[h][w][x1][y1],
        data[h][w][x1][y2 - (1 << w)]),
        data[h][w][x2 - (1 << h)][y1]),
        data[h][w][x2 - (1 << h)][y2 - (1 << w)]);
    // return something
  }
private:
  node data[7][7][127][127];
  static node combine(const node &a, const node &b) {
    // do something
  }
};