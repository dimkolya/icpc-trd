// given $n$ rectangles on a plane,find
// an area of their union.
struct SegTree{
  vector<pair<int,int>> t;
  vector<ll> tl;
  SegTree(int n){t.resize(4*n); tl.resize(4*n);}
  pair<int,int> comb(pair<int,int> a, pair<int,int> b){
    if(a.first == b.first) return {a.first,
                          a.second+b.second};
    else return min(a, b);
  }
  void build(int p, int l, int r, vector<int> &yd){
    if(r-l == 1){t[p].second = yd[l]; return;}
    int m = (l+r)/2;
    build(2*p+1, l, m, yd);
    build(2*p+2, m, r, yd);
    t[p] = comb(t[2*p+1], t[2*p+2]);
  }
  void push(int p, int l, int r){
    if(tl[p] == 0) return;
    int m = (l+r)/2;
    t[2*p+1].first += tl[p];
    tl[2*p+1] += tl[p];
    t[2*p+2].first += tl[p];
    tl[2*p+2] += tl[p];
    tl[p] = 0;
  }
  void upd(int p, int l, int r, int ql, int qr, int v){
    if(qr<=l || r<=ql) return;
    if(ql<=l && r<=qr){
        t[p].first += v;
        tl[p] += v;
        return;
    }
    push(p, l, r);
    int m = (l+r)/2;
    upd(2*p+1, l, m, ql, qr, v);
    upd(2*p+2, m, r, ql, qr, v);
    t[p] = comb(t[2*p+1], t[2*p+2]);
  }
  pair<int,int> get(int p, int l, int r, int ql, int qr){
    if(qr<=l || r<=ql) return {INF, 0};
    if(ql<=l && r<=qr) return t[p];
    push(p, l, r);
    int m = (l+r)/2;
    return comb(get(2*p+1, l, m, ql, qr),
                get(2*p+2, m, r, ql, qr));
  }
};
struct Event{
  int x,y1,y2,t;
};
void solve(){
  int n; cin >> n;
  vector<Event> event(2*n);
  vector<int> yc(2*n);
  for(int i=0; i<n; ++i){
    int x1,y1,x2,y2; cin >> x1 >> y1 >> x2 >> y2;
    event[2*i] = {x1,y1,y2,1};
    event[2*i+1] = {x2,y1,y2,-1};
    yc[2*i] = y1;
    yc[2*i+1] = y2;
  }
  sort(yc.begin(), yc.end());
  yc.resize(unique(all(yc)) - yc.begin());
  int m = yc.size();
  ll L = yc.back() - yc.front();
  vector<int> yd(m);
  for(int i=0; i<m-1; ++i) yd[i] = yc[i+1]-yc[i];
  sort(all(event), [](Event &a, Event &b){
    return (a.x<b.x || (a.x==b.x && a.t>b.t));
  });

  SegTree scan(m); scan.build(0,0,m,yd);
  ll ans = 0; int prv = 0;
  for(auto [x,y1,y2,t] : event){
      y1 = lower_bound(all(yc), y1) - yc.begin();
      y2 = lower_bound(all(yc), y2) - yc.begin();
      auto cur = scan.get(0,0,m,0,m);
      if(cur.first > 0) ans += L * (x-prv);
      else ans += (L - cur.second) * (x-prv);
      scan.upd(0,0,m,y1,y2,t);
      prv = x;
  }
  cout << ans << endl;
}