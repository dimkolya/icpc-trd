struct ac {
  ac(const vector<string> &ss) {
    n = ss.size();
    t.emplace_back();
    lens.resize(n);
    for (int i = 0; i < n; ++i) {
      string s = ss[i];
      lens[i] = s.size();
      int cur = 0;
      for (char c : s) {
        if (t[cur].go[c - 'a'] == -1) {
          t[cur].go[c - 'a'] = t.size();
          t.emplace_back();
        }
        cur = t[cur].go[c - 'a'];
      }
      if (t[cur].fin == -1) {
        t[cur].fin = i;
      } else {
        dependencies.emplace_back(i, t[cur].fin);
      }
    }
    queue<int> q;
    for (char c = 'a'; c <= 'z'; ++c) {
      if (t[0].go[c - 'a'] == -1) {
        t[0].go[c - 'a'] = 0;
      } else {
        q.push(t[0].go[c - 'a']);
      }
    }
    while (!q.empty()) {
      int v = q.front(); q.pop();
      for (char c = 'a'; c <= 'z'; ++c) {
        int u = t[v].go[c - 'a'];
        if (u == -1) {
          t[v].go[c-'a']=v?t[t[v].suf].go[c-'a']:0;
        } else {
          t[u].suf = t[t[v].suf].go[c - 'a'];
          if (t[t[u].suf].fin != -1) {
            t[u].out = t[u].suf;
          } else {
            t[u].out = t[t[u].suf].out;
          }
          q.push(u);
        }
      }
    }
  }

  vector<vector<int>> check(const string &s) {
    vector<vector<int>> result(n);
    int cur = 0;
    for (int i = 0; i < s.size(); ++i) {
      cur = t[cur].go[s[i] - 'a'];
      int j = cur;
      while (j != 0) {
        int index = t[j].fin;
        if (index != -1) {
          result[index].push_back(i - lens[index] + 1);
        }
        j = t[j].out;
      }
    }
    for (auto [v, u] : dependencies) {
      result[v] = result[u];
    }
    return result;
  }
private:
  struct node {
    array<int, K> go;
    int fin = -1;
    int suf = 0, out = 0;
    node() { go.fill(-1); };
  };

  int n;
  vector<node> t;
  vector<pair<int, int>> dependencies;
  vector<int> lens;
};