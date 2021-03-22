/**
 * basic
 */
struct disjoint_set {
    vector<int> par;
    disjoint_set(int n) : par(n, -1) {}
    int find(int u) {
        return par[u] < 0 ? u : par[u] = find(par[u]);
    }
    bool merge(int u, int v) {
        u = find(u), v = find(v);
        if (u == v) return false;

        if (par[u] > par[v]) swap(u, v);
        par[u] += par[v];
        par[v] = u;
        return true;
    }
};

/**
 * merge and split
 */
struct disjoint_set {
    // todo...
}

/**
 * offline dynamic connectivity
 */
struct disjoint_set {
    vector<int> par;
    vector<pair<int, int>> stk;

    disjoint_set(int n) : par(n, -1) {}
    int find(int u) {
        while (par[u] >= 0) u = par[u];
        return u;
    }
    bool merge(int u, int v) {
        u = find(u), v = find(v);
        if (u == v) return false;

        if (par[u] > par[v]) swap(u, v);
        stk.emplace_back(v, par[v]);
        par[u] += par[v];
        par[v] = u;
        return true;
    }
    void roll_back(size_t check_point) {
        for (; stk.size() != check_point; stk.pop_back()) {
            const auto& [u, sz] = stk.back();
            par[par[u]] -= sz, par[u] = sz;
        }
    }
};