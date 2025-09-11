struct splay_tree {
    struct node {
        ll key;
        node *left;
        node *right;
        node *parent;
    };
    node *root = nullptr;
    static void rl(node *v) {
        node *p = v->parent;
        node *r = v->right;
        if (p) {
            if (p->left == v) p->left = r;
            else p->right = r;
        }
        node *temp = r->left;
        r->left = v;
        v->right = temp;
        v->parent = r;
        r->parent = p;
        if (v->right) v->right->parent = v;
    }
    static void rr(node *v) {
        node *p = v->parent;
        node *l = v->left;
        if (p) {
            if (p->right == v) p->right = l;
            else p->left = l;
        }
        node *temp = l->right;
        l->right = v;
        v->left = temp;
        v->parent = l;
        l->parent = p;
        if (v->left) v->left->parent = v;
    }
    void splay(node *v) {
        while (v->parent) {
            node *g = v->parent->parent;
            if (v == v->parent->left) {
                if (!g) {
                    rr(v->parent);
                } else if (v->parent == g->left) {
                    rr(g);
                    rr(v->parent);
                } else {
                    rr(v->parent);
                    rl(v->parent);
                }
            } else {
                if (!g) {
                    rl(v->parent);
                } else if (v->parent == g->right) {
                    rl(g);
                    rl(v->parent);
                } else {
                    rl(v->parent);
                    rr(v->parent);
                }
            }
        }
        root = v;
    }
    node *lower_bound(ll x) {
        node *v = root;
        node *result = nullptr;
        node *last = nullptr;
        while (v) {
            last = v;
            if (v->key >= x) result = v, v = v->left;
            else v = v->right;
        }
        if (last) splay(last);
        return result;
    }
    node *upper_bound(ll x) {
        node *v = root;
        node *result = nullptr;
        node *last = nullptr;
        while (v) {
            last = v;
            if (v->key > x) result = v, v = v->left;
            else v = v->right;
        }
        if (last) splay(last);
        return result;
    }
    node *under_bound(ll x) {
        node *v = root;
        node *result = nullptr;
        node *last = nullptr;
        while (v) {
            last = v;
            if (v->key < x) result = v, v = v->right;
            else v = v->left;
        }
        if (last) splay(last);
        return result;
    }
    // this.keys < r.keys
    void merge(splay_tree &r) {
        if (!root) {
            swap(*this, r);
            return;
        }
        if (!r.root) return;
        node *v = root;
        while (v->right) v = v->right;
        splay(v);
        root->right = r.root;
        r.root->parent = root;
        r.root = nullptr;
    }
    // [return <x, x<= this]
    splay_tree split(ll x) {
        node *v = lower_bound(x);
        if (!v) return splay_tree(nullptr);
        splay(v);
        node *l = v->left;
        if (l) l->parent = nullptr;
        v->left = nullptr;
        return splay_tree(l);
    }
    node *find(ll x) {
        node *v = root;
        node *last = nullptr;
        while (v && v->key != x) {
            last = v;
            if (v->key > x) v = v->left;
            else v = v->right;
        }
        if (v) splay(v);
        else if (last) splay(last);
        return v;
    }
    void insert(ll x) {
        if (!root) {
            root = new node{x};
            return;
        }
        node *v = root;
        node *p = nullptr;
        while (v) {
            p = v;
            if (x < v->key) v = v->left;
            else if (x > v->key) v = v->right;
            else { splay(v); return; }
        }
        v = new node{x, 0, 0, p};
        v->parent = p;
        if (x < p->key) p->left = v;
        else p->right = v;
        splay(v);
    }
    void erase(ll x) {
        node *v = find(x);
        if (!v) return;
        root = v->left;
        splay_tree r(v->right);
        if (root) root->parent = nullptr;
        if (r.root) r.root->parent = nullptr;
        merge(r);
        delete v;
    }
};