struct dinitz {
    dinitz(int _n, int _src, int _sink) : src(_src), sink(_sink),
                                          adj(_n), level(_n), ptr(_n) {}

    void add_edge(int u, int v, int c) {
        adj[u].emplace_back(v, c, adj[v].size());
        adj[v].emplace_back(u, 0, adj[u].size() - 1);
    }
    int64_t flow() {
        int64_t ret = 0;
        for (int f; bfs();) {
            fill(ptr.begin(), ptr.end(), 0);
            while ((f = dfs(src, INT_MAX))) ret += f;
        }
        return ret;
    }

private:
    struct edge {
        int v, capa, rev;
        edge(int v, int capa, int rev) : v(v), capa(capa), rev(rev) {}
    };
    const int src, sink;
    vector<vector<edge>> adj;
    vector<int> level, ptr;

    int bfs() {
        fill(level.begin(), level.end(), 0);
        level[src] = 1;

        queue<int> q;
        q.emplace(src);

        while (!q.empty()) {
            const auto u = q.front();
            q.pop();

            for (const auto& [v, capa, _] : adj[u])
                if (capa && !level[v]) {
                    level[v] = level[u] + 1;
                    q.emplace(v);
                }
        }
        return level[sink];
    }
    int dfs(int u, int f) {
        if (u == sink) return f;
        for (int &i = ptr[u], sz = adj[u].size(); i < sz; ++i) {
            auto& [v, capa, rev] = adj[u][i];
            if (capa && level[u] + 1 == level[v])
                if (int d = dfs(v, min(f, capa)); d) {
                    capa -= d;
                    adj[v][rev].capa += d;
                    return d;
                }
        }
        return 0;
    }
};