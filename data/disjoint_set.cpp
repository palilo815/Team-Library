/**
 * @brief 
 *      Disjoint Set Union (a.k.a Union-Find)
 */
class disjoint_set {
public:
    disjoint_set(int _n) : n(_n), par(n, -1) {}

    int find(int u) {
        assert(0 <= u and u < n);
        return par[u] < 0 ? u : par[u] = find(par[u]);
    }
    bool unite(int u, int v) {
        assert(0 <= u and u < n and 0 <= v and v < n);
        u = find(u), v = find(v);
        if (u == v) return false;

        if (par[u] > par[v]) swap(u, v);
        par[u] += par[v];
        par[v] = u;
        return true;
    }
    int size_of(int u) {
        assert(0 <= u and u < n);
        return -par[find(u)];
    }
    bool is_same(int u, int v) {
        assert(0 <= u and u < n and 0 <= v and v < n);
        return find(u) == find(v);
    }

private:
    const int n;
    vector<int> par;
};