// find minimal cover of [0,L] by segments
sort(seg.begin(), seg.end());
ll cnt=0, cur=0, best=-1;
for(auto x : seg){
  if(x.first > cur){
    if(best == -1) break;
    cur = best;
    ++cnt;
  }
  else{
    best = max(best, x.second);
  }
}
cout << cnt << endl;