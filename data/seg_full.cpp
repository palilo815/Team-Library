/**
 * @author  palilo 
 *
 *
 * segment tree (full binary tree, i.e. # of nodes = 2^k-1)
 */
template <class T, class F>
class SegTree {
    const size_t n;
    const T e;
    const F f;
    const size_t size;
    std::vector<T> tree;

public:
    SegTree(size_t n, T e, F f) : n(n), e(e), f(f), size(1 << (n ? std::__lg(n - 1) + 1 : 0)), tree(size << 1, e) {}

    auto operator[](size_t i) -> T& { return tree[size | i]; }

    auto build() {
        for (size_t i = size; i--;) {
            pull(i);
        }
    }

    auto set(size_t i, T val) {
        assert(i < n);
        tree[i |= size] = val;
        while (i >>= 1) pull(i);
    }

    [[nodiscard]] auto prod(size_t l, size_t r) const {
        assert(l <= r and r <= n);
        T lval = e, rval = e;
        for (l += size, r += size; l != r; l >>= 1, r >>= 1) {
            if (l & 1) lval = f(lval, tree[l++]);
            if (r & 1) rval = f(tree[--r], rval);
        }
        return f(lval, rval);
    }

private:
    auto pull(size_t i) {
        tree[i] = f(tree[i << 1], tree[i << 1 | 1]);
    }
};
