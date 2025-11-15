struct hsh {
  hsh(const string &s, ll b, ll m) : m(m) {
    ll n = s.size();
    h.resize(n + 1);
    p.resize(n + 1);
    p[0] = 1;
    for (ll i = 1; i <= n; ++i)
      p[i] = p[i - 1] * b % m;
    for (ll i = 0; i < n; ++i)
      h[i + 1] = (h[i] * b + s[i]) % m;
  }
  ll get(ll l, ll r) { // [l, r)
    return ((h[r] - h[l] * p[r - l]) % m + m) % m;
  }
private:
  ll m;
  vector<ll> h, p;
};