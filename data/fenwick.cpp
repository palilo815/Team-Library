template <typename T>
class BIT {
    BIT(int _n) : n(_n), tree(_n + 1) {}
    void update(int i, T val) {
        for (++i; i <= n; i += i & -i)
            tree[i] += val;
    }
    T query(int i) {
        T ret = 0;
        for (; i; i &= i - 1)
            ret += tree[i];
        return ret;
    }
    T query(int l, int r) {
        return query(r) - query(l);
    }

private:
    const int n;
    vector<T> tree;
};