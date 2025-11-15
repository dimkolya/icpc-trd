mt19937_64 gen(time(0));

ll binpow(ll a, ll p, ll m) {
  if (p == 0) return 1;
  if (p % 2 == 1)
    return (__int128_t) a * binpow(a, p-1, m) % m;
  ll x = binpow(a, p / 2, m);
  return (__int128_t) x * x % m;
}

bool test(ll n) {
  if (n == 1) return false;
  ll a = 1 + gen() % (n - 1);
  if (gcd(a, n) != 1) return false;
  ll x = 0;
  ll m = n - 1;
  while (m % 2 == 0) {
    m /= 2;
    ++x;
  }
  ll cur = binpow(a, m, n);
  for (ll i = 0; i < x; ++i) {
    if (((__int128_t) cur * cur % n) == 1
        && cur != 1 && cur != n - 1) {
      return false;
    }
    cur = ((__int128_t) cur * cur % n);
  }
  return cur == 1;
}