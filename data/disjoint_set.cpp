/**
 * @brief 
 *      Disjoint Set Union (a.k.a Union-Find)
 */
class disjoint_set {
    vector<int> par;

public:
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