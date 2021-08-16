/**
 * @author  palilo
 * @brief   disjoint-set-union (a.k.a. union-find)
 * @warning no `assert`
 *          dsu is so simple, we do not need such a error handler. isn't it?
 */
class disjoint_set {
    const size_t n;
    vector<int> par;

public:
    disjoint_set(size_t n) : n(n), par(n, -1) {}

    int find(size_t u) {
        return par[u] < 0 ? u : par[u] = find(par[u]);
    }
    bool unite(size_t u, size_t v) {
        u = find(u), v = find(v);
        if (u == v) return false;
        if (par[u] > par[v]) swap(u, v);
        par[u] += par[v];
        par[v] = u;
        return true;
    }
    int size_of(size_t u) { return -par[find(u)]; }
    bool are_same(size_t u, size_t v) { return find(u) == find(v); }
    int num_components() const {
        return count_if(par.begin(), par.end(), [&](const auto& x) { return x < 0; });
    }
};