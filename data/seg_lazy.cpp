/**
 * @brief 
 *      Segment Tree with Lazy Propagation 
 * @todo 
 *      e, off       -> identity element
 *      op           -> unite two nodes
 *      mapping      -> apply tag to node
 *      composition  -> unite two tags
 * @warning
 *      cannot use `bool` as `node_t` or `tag_t`
 */
template <typename node_t, typename tag_t>
class lazy_seg {
    const node_t e = node_t {};
    const tag_t off = tag_t {};
    const int n, height, size;
    vector<node_t> tree;
    vector<tag_t> lazy;

public:
    lazy_seg(int _n) : n(_n), height(__lg(_n - 1) + 1), size(1 << height),
                       tree(size << 1, e), lazy(size, off) {}

    node_t& operator[](int i) { return tree[size + i]; }
    void build() {
        for (int i = size - 1; i; --i)
            pull(i);
    }
    void apply(int l, int r, tag_t f) {
        apply(l, r, f, 0, size, 1);
    }
    node_t prod(int l, int r) {
        return prod(l, r, 0, size, 1);
    }

private:
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

#define lson (i << 1)
#define rson (i << 1 | 1)
    void apply(int ql, int qr, tag_t f, int l, int r, int i) {
        if (qr <= l || r <= ql) return;
        if (ql <= l && r <= qr) {
            all_apply(i, f);
            return;
        }
        if (lazy[i] != off) push(i);

        int m = (l + r) >> 1;
        apply(ql, qr, f, l, m, lson), apply(ql, qr, f, m, r, rson);
        pull(i);
    }
    node_t prod(int ql, int qr, int l, int r, int i) {
        if (qr <= l || r <= ql) return e;
        if (ql <= l && r <= qr) return tree[i];
        if (lazy[i] != off) push(i);

        int m = (l + r) >> 1;
        return op(prod(ql, qr, l, m, lson), prod(ql, qr, m, r, rson));
    }
    void pull(int i) {
        tree[i] = op(tree[lson], tree[rson]);
    }
    void push(int i) {
        all_apply(lson, lazy[i]);
        all_apply(rson, lazy[i]);
        lazy[i] = off;
    }
    void all_apply(int i, tag_t f) {
        mapping(tree[i], f);
        if (i < size) composition(lazy[i], f);
    }
    node_t op(node_t lhs, node_t rhs) {
        assert(false);
    }
    void mapping(node_t& node, tag_t f) {
        assert(false);
    }
    void composition(tag_t& tag, tag_t f) {
        assert(false);
    }
#undef lson
#undef rson
};