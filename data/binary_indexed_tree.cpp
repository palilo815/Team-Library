/**
 * @author  palilo
 * @brief   binary indexed tree (a.k.a. fenwick tree)  
 * @details `lower_bound(k)`
 *              @return minimum i s.t. sum[0...i] >= k
 *          `upper_bound(k)`
 *              @return minimum i s.t. sum[0...i] > k
 *          @see http://boj.kr/2761f0417b9e4126bfd4a02962fbe6dd
 */
template <typename T>
class binary_indexed_tree {
    const size_t n;
    vector<T> tree;

public:
    binary_indexed_tree(size_t n) : n(n), tree(n + 1) {}

    // a[i] += val
    void update(size_t i, T val) {
        assert(0 <= i and i <= n);
        for (++i; i <= n; i += i & -i)
            tree[i] += val;
    }
    // sum in range [0...i)
    T query(size_t i) const {
        assert(0 <= i and i <= n);
        T ret = 0;
        for (; i; i &= i - 1)
            ret += tree[i];
        return ret;
    }
    // sum in range [l, r)
    T query(size_t l, size_t r) const {
        return query(r) - query(l);
    }
    // a[i]
    T get(size_t i) const {
        assert(0 <= i and i < n);
        return i & 1 ? query(i, i + 1) : tree[i + 1];
    }
    size_t lower_bound(T k) const {
        size_t x = 0;
        for (size_t pw = 1 << __lg(n); pw; pw >>= 1)
            if ((x | pw) <= n && tree[x | pw] < k)
                k -= tree[x |= pw];
        return x;
    }
    size_t upper_bound(T k) const {
        size_t x = 0;
        for (size_t pw = 1 << __lg(n); pw; pw >>= 1)
            if ((x | pw) <= n && tree[x | pw] <= k)
                k -= tree[x |= pw];
        return x;
    }
};