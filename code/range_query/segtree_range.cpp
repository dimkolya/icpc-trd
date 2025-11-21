struct st {
  ll p = 1;
  vector<ll> data, add_data;
  st(ll n) {
    while (p < n) p *= 2;
    data.resize(p * 2);
    add_data.resize(p * 2);
  }
  void upd(ll l,ll r,ll v,ll i=1,ll tl=0,ll tr=-1) {
    if (tr == -1) tr = p;
    if (tr <= l || r <= tl) return;
    if (l <= tl && tr <= r) {
      data[i] += (tr - tl) * v;
      add_data[i] += v;
      return;
    }
    ll tm = (tl + tr) / 2;
    push(i, tl, tm, tr);
    upd(l, r, v, i * 2, tl, tm);
    upd(l, r, v, i * 2 + 1, tm, tr);
    data[i] = data[2 * i] + data[2 * i + 1];
  }
  ll get(ll l,ll r,ll i=1,ll tl=0,ll tr=-1) {
    if (tr == -1) tr = p;
    if (r <= tl || tr <= l) return 0;
    if (l <= tl && tr <= r) return data[i];
    ll tm = (tl + tr) / 2;
    push(i, tl, tm, tr);
    return get(l, r, 2 * i, tl, tm)
           + get(l, r, 2 * i + 1, tm, tr);
  }
  void push(ll i, ll tl, ll tm, ll tr) {
    data[2 * i] += add_data[i] * (tm - tl);
    data[2 * i + 1] += add_data[i] * (tr - tm);
    add_data[2 * i] += add_data[i];
    add_data[2 * i + 1] += add_data[i];
    add_data[i] = 0;
  }
};