/**
 * @author palilo
 * @brief  implement Tarjan's scc algorithm
 */
class scc {
    const int n;
    vector<vector<int>> adj;

public:
    int num_components = 0;
    vector<int> component_id;

    scc(int _n) : n(_n), adj(n), component_id(n, -1), dis(n, -1), low(n) {}

    void add_edge(int u, int v) {
        assert(0 <= u and u < n and 0 <= v and v < n);
        adj[u].emplace_back(v);
    }
    void run() {
        for (int i = 0; i < n; ++i)
            if (dis[i] == -1)
                dfs(i);
        assert(stk.empty());
    }

private:
    vector<int> stk, dis, low;
    int dfs_time = 0;

    void dfs(int u) {
        low[u] = dis[u] = dfs_time++;
        stk.emplace_back(u);

        for (const auto& v : adj[u])
            if (dis[v] == -1) {
                dfs(v);
                chmin(low[u], low[v]);
            } else
                chmin(low[u], dis[v]);

        if (low[u] == dis[u]) {
            int x;
            do {
                x = stk.back();
                stk.pop_back();
                dis[x] = INT_MAX;
                component_id[x] = num_components;
            } while (x != u);
            ++num_components;
        }
    }
};