/**
 * @author  palilo
 * @brief   segment tree with lazy propagation
 */
template <typename T, typename U, typename F0, typename F1, typename F2>
class LazySeg {
    const size_t n;
    const T e;
    const U off;
    const F0 op;
    const F1 mapping;
    const F2 composition;
    const size_t size;
    std::vector<T> tree;
    std::vector<U> lazy;

public:
    LazySeg(size_t n, T e, U off, F0 op, F1 mapping, F2 composition)
        : n(n), e(e), off(off), op(op), mapping(mapping), composition(composition),
          size(1 << (n ? std::__lg(n - 1) + 1 : 0)), tree(size << 1, e), lazy(size, off) {}

    auto operator[](size_t i) -> T& { return tree[size | i]; }

    auto build() {
        for (auto i = size; i--;) {
            pull(i);
        }
    }
    auto apply(size_t l, size_t r, U f) {
        apply(l, r, f, 0, size, 1);
    }
    auto prod(size_t l, size_t r) {
        return prod(l, r, 0, size, 1);
    }
    [[nodiscard]] auto all_prod() const {
        return tree[1];
    }

private:
#define lson (i << 1)
#define rson (i << 1 | 1)
    auto apply(size_t ql, size_t qr, U f, size_t l, size_t r, size_t i) {
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
    auto prod(size_t ql, size_t qr, size_t l, size_t r, size_t i) {
        if (qr <= l || r <= ql) return e;
        if (ql <= l && r <= qr) return tree[i];
        if (lazy[i] != off) push(i);
        const auto m = (l + r) >> 1;
        return op(prod(ql, qr, l, m, lson), prod(ql, qr, m, r, rson));
    }
    auto pull(size_t i) {
        tree[i] = op(tree[lson], tree[rson]);
    }
    auto push(size_t i) {
        all_apply(lson, lazy[i]);
        all_apply(rson, lazy[i]);
        lazy[i] = off;
    }
    auto all_apply(size_t i, const U& f) {
        mapping(tree[i], f);
        if (i < size) composition(lazy[i], f);
    }
#undef lson
#undef rson
};
