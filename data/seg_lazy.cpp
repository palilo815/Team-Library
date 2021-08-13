/**
 * @author  palilo
 * @brief   segment tree with lazy propagation 
 * @todo    `node_t` and `tag_t` <- define type
 *          `e` and `off`        <- set identity element
 *          `op`                 <- unite two nodes
 *          `mapping`            <- apply tag to node
 *          `composition`        <- unite two tags
 * @warning be careful for setting value `e`, it will used for... 
 *          1. dummy nodes (out of range)
 *          2. initial value in `prod` and `op`
 *          cannot use `bool` as `node_t` or `tag_t` (i use l-value reference)
 */
class lazy_segtree {
    // change this (1/2)
    using node_t = int;
    using tag_t = int;

    const node_t e = node_t {};
    const tag_t off = tag_t {};
    // change this (1/2)
    const size_t n, height, size;
    vector<node_t> tree;
    vector<tag_t> lazy;

public:
    lazy_segtree(size_t n) : n(n), height(n ? __lg(n - 1) + 1 : 0), size(1 << height),
                             tree(size << 1, e), lazy(size, off) {}

    node_t& operator[](size_t i) { return tree[size + i]; }
    void build() {
        for (size_t i = size; i--;) {
            pull(i);
        }
    }
    void apply(size_t l, size_t r, tag_t f) {
        apply(l, r, f, 0, size, 1);
    }
    node_t prod(size_t l, size_t r) {
        return prod(l, r, 0, size, 1);
    }

private:
#define lson (i << 1)
#define rson (i << 1 | 1)
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
    void apply(size_t ql, size_t qr, tag_t f, size_t l, size_t r, size_t i) {
        if (qr <= l || r <= ql) return;
        if (ql <= l && r <= qr) {
            all_apply(i, f);
            return;
        }
        if (lazy[i] != off) push(i);

        const auto m = (l + r) >> 1;
        apply(ql, qr, f, l, m, lson), apply(ql, qr, f, m, r, rson);
        pull(i);
    }
    node_t prod(size_t ql, size_t qr, size_t l, size_t r, size_t i) {
        if (qr <= l || r <= ql) return e;
        if (ql <= l && r <= qr) return tree[i];
        if (lazy[i] != off) push(i);

        const auto m = (l + r) >> 1;
        return op(prod(ql, qr, l, m, lson), prod(ql, qr, m, r, rson));
    }
    void pull(size_t i) {
        tree[i] = op(tree[lson], tree[rson]);
    }
    void push(size_t i) {
        all_apply(lson, lazy[i]);
        all_apply(rson, lazy[i]);
        lazy[i] = off;
    }
    void all_apply(size_t i, tag_t f) {
        mapping(tree[i], f);
        if (i < size) composition(lazy[i], f);
    }
    // change this (2/2)
    node_t op(node_t lhs, node_t rhs) {
        assert(false);
        return node_t {};
    }
    void mapping(node_t& node, tag_t f) {
        assert(false);
    }
    void composition(tag_t& tag, tag_t f) {
        assert(false);
    }
    // change this (2/2)
#undef lson
#undef rson
};