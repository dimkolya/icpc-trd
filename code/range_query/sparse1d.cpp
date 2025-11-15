struct sptable {
  sptable(const vector<ll> &a) {
    ll n = a.size(), k = __lg(n);
    data.resize(k + 1); data[0].resize(n);
    for (ll i = 0; i < n; ++i) data[0][i] = a[i];
    for (ll j = 1; j <= k; ++j) {
      data[j].resize(n - (1 << j) + 1);
      for (ll i = 0; i <= n - (1 << j); ++i)
        data[j][i] = min(data[j-1][i],
                         data[j-1][i+(1<<(j-1))]);
    }
  }
  ll get(ll l, ll r) const {
    ll k = __lg(r - l);
    return min(data[k][l], data[k][r - (1 << k)]);
  }
private:
  vector<vector<ll>> data;
};