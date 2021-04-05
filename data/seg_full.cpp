template <typename node_t>
struct segtree {
    segtree(int _n) : n(_n), height(__lg(_n - 1) + 1), size(1 << height),
                      tree(size << 1, e) {}

    node_t& operator[](int i) { return tree[size + i]; }
    void build() {
        for (int i = size - 1; i; --i)
            pull(i);
    }
    void set(int idx, node_t val) {
        assert(0 <= idx and idx < n);

        tree[idx += size] = val;
        while (idx >>= 1) pull(idx);
    }
    node_t prod(int l, int r) {
        assert(0 <= l and l <= r and r <= n);

        node_t lval = e, rval = e;
        for (l += n, r += n; l != r; l >>= 1, r >>= 1) {
            if (l & 1) lval = op(lval, tree[l++]);
            if (r & 1) rval = op(tree[--r], rval);
        }
        return op(lval, rval);
    }

private:
#define lson (i << 1)
#define rson (i << 1 | 1)
    const node_t e = node_t {};
    const int n, height, size;
    vector<node_t> tree;

    inline int get_index(node_t& node) { return &node - tree.data(); }
    inline int get_depth(node_t& node) { return __lg(get_index(node)); }
    inline int get_height(node_t& node) { return height - get_depth(node); }
    inline int get_length(node_t& node) { return 1 << get_height(node); }
    inline int get_first(node_t& node) {
        int idx = get_index(node);
        int dep = __lg(idx);
        int len = 1 << height - dep;
        return len * (idx ^ 1 << dep);
    }

    void pull(int i) {
        tree[i] = op(tree[lson], tree[rson]);
    }
    node_t op(node_t lhs, node_t rhs) {
        assert(true);
        return node_t {};
    }
#undef lson
#undef rson
};