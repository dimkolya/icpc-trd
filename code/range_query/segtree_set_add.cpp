struct st {
  st(ll n) {
    while (p < n) p *= 2;
    data.resize(2 * p, 0);
    set_actual.resize(2 * p, false);
    add_actual.resize(2 * p, false);
    set_data.resize(2 * p, 0);
    add_data.resize(2 * p, 0);
  }
  void set(ll l, ll r, ll value) {
    set(l, r, value, 1, 0, p);
  }
  void add(ll l, ll r, ll value) {
    add(l, r, value, 1, 0, p);
  }
  ll sum(ll l, ll r) {
    return sum(l, r, 1, 0, p);
  }
private:
  ll p = 1;
  vector<ll> data;
  vector<bool> set_actual;
  vector<ll> set_data;
  vector<bool> add_actual;
  vector<ll> add_data;
  void push(ll i, ll tl, ll tr) {
    ll tm = (tl + tr) / 2;
    if (set_actual[i]) {
      data[2 * i] = (tm - tl) * set_data[i];
      set_data[2 * i] = set_data[i];
      add_data[2 * i] = 0;
      add_actual[2 * i] = false;
      set_actual[2 * i] = true;

      data[2 * i + 1] = (tr - tm) * set_data[i];
      set_data[2 * i + 1] = set_data[i];
      add_data[2 * i + 1] = 0;
      add_actual[2 * i + 1] = false;
      set_actual[2 * i + 1] = true;

      set_data[i] = 0;
      set_actual[i] = false;
    }
    if (add_actual[i]) {
      data[2 * i] += (tm - tl) * add_data[i];
      if (set_actual[2 * i]) {
        set_data[2 * i] += add_data[i];
      } else {
        add_data[2 * i] += add_data[i];
        add_actual[2 * i] = true;
      }
      data[2 * i + 1] += (tr - tm) * add_data[i];
      if (set_actual[2 * i + 1]) {
        set_data[2 * i + 1] += add_data[i];
      } else {
        add_data[2 * i + 1] += add_data[i];
        add_actual[2 * i + 1] = true;
      }
      add_data[i] = 0;
      add_actual[i] = false;
    }
  }
  void pop(ll i) {
    data[i] = data[2 * i] + data[2 * i + 1];
  }
  void set(ll l, ll r, ll value, ll i, ll tl, ll tr) {
    if (tr <= l || r <= tl) return;
    if (l <= tl && tr <= r) {
      data[i] = (ll) (tr - tl) * value;
      set_data[i] = value;
      add_data[i] = 0;
      add_actual[i] = false;
      set_actual[i] = true;
      return;
    }
    push(i, tl, tr);
    ll tm = (tl + tr) / 2;
    set(l, r, value, 2 * i, tl, tm);
    set(l, r, value, 2 * i + 1, tm, tr);
    pop(i);
  }
  void add(ll l, ll r, ll value, ll i, ll tl, ll tr) {
    if (tr <= l || r <= tl) return;
    if (l <= tl && tr <= r) {
      data[i] += (ll) (tr - tl) * value;
      if (set_actual[i]) {
        set_data[i] += value;
      } else {
        add_data[i] += value;
        add_actual[i] = true;
      }
      return;
    }
    push(i, tl, tr);
    ll tm = (tl + tr) / 2;
    add(l, r, value, 2 * i, tl, tm);
    add(l, r, value, 2 * i + 1, tm, tr);
    pop(i);
  }

  ll sum(ll l, ll r, ll i, ll tl, ll tr) {
    if (tr <= l || r <= tl) return 0;
    if (l <= tl && tr <= r) return data[i];
    push(i, tl, tr);
    ll tm = (tl + tr) / 2;
    ll temp = sum(l, r, 2 * i, tl, tm)
              + sum(l, r, 2 * i + 1, tm, tr);
    pop(i);
    return temp;
  }
};