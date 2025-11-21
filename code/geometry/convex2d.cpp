struct point {
  ld x, y;
  ld operator*(const point&p) const {
    return x * p.y - y * p.x;}
  point &operator-=(const point &p) {
    x -= p.x; y -= p.y;
    return *this;}
  point &operator+=(const point &p) {
    x += p.x; y += p.y;
    return *this;}
  bool operator==(const point &p) const {
    return x == p.x && y == p.y;}
  bool operator!=(const point &p) const {
    return x != p.x || y != p.y;}
  bool operator<(const point &p) const {
    return x < p.x || (x == p.x && y < p.y);}
};
point operator-(point a, const point &b) {
  return a -= b;}
point operator+(point a, const point &b) {
  return a += b;}
vector<point> hull(vector<point> ps) {
  point p0 = ps[0];
  ll ind = 0;
  for (ll i = 0; i < ps.size(); ++i) {
    if (ps[i].x < p0.x
        || (ps[i].x == p0.x
            && ps[i].y < p0.y)) {
      p0 = ps[i];
      ind = i;
    }
  }
  ps.erase(ps.begin() + ind);
  sort(ps.begin(), ps.end(),
       [&p0](const point &a, const point &b) {
    return ((a - p0) ^ (b - p0)) > 0;
  });
  vector<point> hull;
  hull.emplace_back(p0);
  for (auto p : ps) {
    while (hull.size() >= 2) {
      point newp(p - hull.back());
      point lastp(hull.back()-hull[hull.size()-2]);
      if (newp ^ lastp > 0) hull.pop_back();
      else break;
    }
    hull.push_back(p);
  }
  return hull;
}
ld get_s(vector<point> &h) {
  h.push_back(h.front());
  ld s = 0;
  for (ll i = 0; i < h.size() - 1; ++i)
    s += h[i] ^ h[i + 1];
  h.pop_back();
  return abs(s) / 2;
}