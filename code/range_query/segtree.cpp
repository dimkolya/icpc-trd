struct segtree {
  ll n;
  vector<ll> data;
  segtree(const vector<ll> &a) {
    n = a.size();
    data.resize(2 * n);
    std::copy(a.begin(), a.end(), data.begin() + n);
    for (ll i = n - 1; i > 0; --i) {
      data[i] = data[2 * i] + data[2 * i + 1];
    }
  }
  void upd(ll i, ll v) { // a[i] += v
    data[i += n] = v;
    while (i > 1) {
      i /= 2;
      data[i] = data[2 * i] + data[2 * i + 1];
    }
  }
  ll get(ll l, ll r) { // [l, r)
    l += n, r += n;
    ll result = 0;
    while (l < r) {
      if (l & 1) result += data[l++];
      if (r & 1) result += data[--r];
      l /= 2, r /= 2;
    }
    return result;
  }
};