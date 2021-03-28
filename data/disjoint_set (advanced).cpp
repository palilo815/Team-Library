/**
 * Editor War
 */
struct disjoint_set {
    vector<int> par, enemy;
    disjoint_set(int n) : par(n, -1), enemy(n, -1) {}
    int find(int u) {
        return par[u] < 0 ? u : par[u] = find(par[u]);
    }
    int merge(int u, int v) {
        if (u == -1) return v;
        if (v == -1) return u;

        u = find(u), v = find(v);
        if (u == v) return u;

        if (par[u] > par[v]) swap(u, v);
        par[u] += par[v];
        par[v] = u;
        return u;
    }
    bool ack(int u, int v) {
        u = find(u), v = find(v);
        if (enemy[u] == v) return false;

        int a = merge(u, v), b = merge(enemy[u], enemy[v]);
        enemy[a] = b;
        if (~b) enemy[b] = a;
        return true;
    }
    bool dis(int u, int v) {
        u = find(u), v = find(v);
        if (u == v) return false;

        int a = merge(u, enemy[v]), b = merge(v, enemy[u]);
        enemy[a] = b, enemy[b] = a;
        return true;
    }
};

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

/**
 * find maximum edge in path(u, v)
 */
struct disjoint_set {
    vector<int> par, dist;
    disjoint_set(int n) : par(n, -1), dist(n) {}
    int find(int u) {
        while (par[u] >= 0) u = par[u];
        return u;
    }
    void merge(int u, int v, int w) {
        u = find(u), v = find(v);
        if (u == v) return;

        if (par[u] > par[v]) swap(u, v);
        par[u] += par[v];
        par[v] = u;
        dist[v] = w;
    }
    int query(int u, int v) {
        assert(u != v);
        int ret;
        for (; u != v; u = par[u]) {
            if (dist[u] < dist[v]) swap(u, v);
            ret = dist[u];
        }
        return ret;
    }
};