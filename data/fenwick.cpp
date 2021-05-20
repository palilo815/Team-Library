/**
 * @brief 
 *      Binary Indexed Tree (a.k.a. Fenwick Tree)
 * 
 * @warning 
 *      `query(l, r)` and `get(i)`  must be used when inverse operation exists    
 * 
 * @note
 *      `lower_bound(k)`
 *          @return minimum i s.t. sum[0...i] >= k
 *      `upper_bound(k)`
 *          @return minimum i s.t. sum[0...i] > k
 */
template <typename T = int>
class BIT {
    const int n;
    vector<T> tree;

public:
    BIT(int _n) : n(_n), tree(_n + 1) {}

    void update(int i, T val) {
        assert(0 <= i and i < n);
        for (++i; i <= n; i += i & -i)
            tree[i] += val;
    }
    T query(int i) {
        assert(0 <= i and i <= n);
        T ret = 0;
        for (; i; i &= i - 1)
            ret += tree[i];
        return ret;
    }
    T query(int l, int r) {
        assert(0 <= l and l <= r and r <= n);
        return query(r) - query(l);
    }
    T get(int i) {
        assert(0 <= i and i < n);
        return i & 1 ? query(i, i + 1) : tree[i + 1];
    }
    int lower_bound(T k) {
        if (k <= 0) return -1;
        int x = 0;
        for (int pw = 1 << __lg(n); pw; pw >>= 1)
            if ((x | pw) <= n && tree[x | pw] < k)
                k -= tree[x |= pw];
        return x;
    }
    int upper_bound(T k) {
        if (k < 0) return -1;
        int x = 0;
        for (int pw = 1 << __lg(n); pw; pw >>= 1)
            if ((x | pw) <= n && tree[x | pw] <= k)
                k -= tree[x |= pw];
        return x;
    }
};