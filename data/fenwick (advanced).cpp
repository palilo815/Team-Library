/**
 * find kth element
 */
template <typename T>
struct BIT {
    BIT(int _n) : n(1 << __lg(_n - 1) + 1), tree(_n + 1) {}
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
        return query(r) - query(l);
    }
    int kth(T k) {
        if (k >= tree[n]) return n;
        int l = 0;
        for (int len = n >> 1; len; len >>= 1)
            if (k >= tree[l | len])
                k -= tree[l |= len];
        return l;
    }

private:
    const int n;
    vector<T> tree;
};