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
 * @author palilo
 * @brief  minimize maximum weight in path u -> v
 */
template <typename T, typename F = less<T>>
class disjoint_set {
    // change this (1/1)
    const T e = 0x3f3f3f3f;
    const F cmp {};
    // change this (1/1)
    const int n;
    vector<int> par;
    vector<T> weight;

public:
    disjoint_set(int n) : n(n), par(n, -1), weight(n, e) {}
    int find(int u) {
        while (par[u] >= 0) u = par[u];
        return u;
    }
    void unite(int u, int v, T w) {
        u = find(u), v = find(v);
        if (u == v) return;
        if (par[u] > par[v]) swap(u, v);
        par[u] += par[v];
        par[v] = u;
        weight[v] = w;
    }
    T query(int u, int v) {
        T ret = e;
        for (; u != v; u = par[u]) {
            if (cmp(weight[v], weight[u])) swap(u, v);
            ret = weight[u];
        }
        return ret;
    }
};