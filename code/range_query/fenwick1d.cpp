struct fenwick {
  vector<ll> t;
  fenwick(ll n) { t.resize(n + 1); }
  void upd(ll i, ll v) {// a[i] += v
    ++i;
    for (; i < t.size(); i += i & -i)
      t[i] += v;
  }
  ll pre(ll i) {// sum [0, i)
    ll res = 0;
    for (; i > 0; i -= i & -i) res += t[i];
    return res;
  }
  ll get(ll l, ll r) {// [l, r)
    return pre(r) - pre(l);
  }
  ll lower_bound(ll v) {// sum [0, pos] >= v
    ll sum = 0, pos = 0;
    for (ll i = __lg(t.size()); i >= 0; --i) {
      if (pos + (1 << i) < t.size()
          && sum + t[pos + (1 << i)] < v) {
        sum += t[pos + (1 << i)];
        pos += (1 << i);
      }
    }
    return pos;
  }
};