/**
 * @brief 
 *      Binary Indexed Tree (a.k.a. Fenwick Tree)
 *
 * @warning 
 *      `query(l, r)` and `get(i)`  must be used when inverse operation exists
 * 
 *      `kth(k)`    the parameter `k` is 0-indexed
 *                  e.g. if (k == 0) : return first element's position
 *                          (k == 1) : return second ...      
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
    int kth(T k) {
        int l = 0;
        for (int len = 1 << __lg(n); len; len >>= 1)
            if ((l | len) <= n && k >= tree[l | len])
                k -= tree[l |= len];

        if (l == n + 1 || (l == n && k >= tree[l]))
            return n;
        return l;
    }
};