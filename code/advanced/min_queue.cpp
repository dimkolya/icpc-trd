struct min_queue {
  stack<pair<ll, ll>> a, b;
  void push(ll x) {
    auto y = a.empty() ? x : min(a.top().S, x);
    a.push({x, y});
  }
  void pop() {
    if (b.empty()) {
      while (!a.empty()) {
        ll x = a.top().first;
        a.pop();
        ll y = b.empty() ? x
               : min(b.top().second, x);
        b.push({x, y});
      }
    }
    b.pop();
  }
  ll get() {
    if (a.empty()) return b.top().second;
    if (b.empty()) return a.top().second;
    return min(a.top().S, b.top().second);
  }
  ll size() {
    return a.size() + b.size();
  }
};