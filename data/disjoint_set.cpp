/**
 * @author  palilo
 * @brief   Disjoint Set Union (a.k.a Union-Find)
 * @warning no `assert`
 *          dsu is so simple, we do not need such a error handler. isn't it?
 */
class disjoint_set {
    const int n;
    vector<int> par;

public:
    disjoint_set(int _n) : n(_n), par(n, -1) {}
    int find(int u) {
        return par[u] < 0 ? u : par[u] = find(par[u]);
    }
    bool unite(int u, int v) {
        u = find(u), v = find(v);
        if (u == v) return false;
        if (par[u] > par[v]) swap(u, v);
        par[u] += par[v];
        par[v] = u;
        return true;
    }
    int size_of(int u) { return -par[find(u)]; }
    bool is_same(int u, int v) { return find(u) == find(v); }
    int num_components() const {
        return count_if(par.begin(), par.end(), [&](const auto& x) { return x < 0; });
    }
};