struct point {
  ld x, y, z;
  point operator-(const point &p) const {
    return {x - p.x,
            y - p.y,
            z - p.z};}
  point cross(const point &p) const {
    return {y * p.z - z * p.y,
            z * p.x - x * p.z,
            x * p.y - y * p.x};}
  ld dot(const point &p) const {
    return x * p.x + y * p.y + z * p.z;}
};
struct face {
  ll a, b, c;
  point q;
};
vector<face> hull(const vector<point> &p) {
  ll n = p.size();
  vector<face> f;
  vector<vector<bool>> dead(n,
    vector<bool>(n, true));
  auto add_face = [&](ll a, ll b, ll c) {
    f.push_back(
        {a, b, c,
         (p[b] - p[a]).cross(p[c] - p[a])});
    dead[a][b] = dead[b][c] = dead[c][a] = false;
  };
  add_face(0, 1, 2);
  add_face(0, 2, 1);
  for (ll i = 3; i < n; ++i) {
    vector<face> f2;
    for (face &cur: f) {
      if ((p[i] - p[cur.a]).dot(cur.q) > EPS)
        dead[cur.a][cur.b]
            = dead[cur.b][cur.c]
            = dead[cur.c][cur.a] = true;
      else
        f2.push_back(cur);
    }
    f.clear();
    for (face &cur: f2) {
      ll arr[3] = {cur.a, cur.b, cur.c};
      for (ll j = 0; j < 3; ++j) {
        ll a = arr[j], b = arr[(j + 1) % 3];
        if (dead[b][a])
          add_face(b, a, i);
      }
    }
    f.insert(f.end(), f2.begin(), f2.end());
  }
  return f;
}