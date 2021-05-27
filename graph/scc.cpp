/**
 * @brief 
 * 		Strongly Connected Component
 */
class SCC {
public:
    SCC(vector<vector<int>>& _adj) : adj(_adj), n(adj.size()), low(n), dis(n, -1) {}

    vector<vector<int>> grouping() {
        for (int i = 0; i < n; ++i)
            if (dis[i] == -1)
                dfs(i);
        return ret;
    }

private:
    const vector<vector<int>>& adj;
    const int n;

    vector<int> stk, low, dis;
    vector<vector<int>> ret;
    int t = 0;

    void dfs(int u) {
        low[u] = dis[u] = t++;
        stk.emplace_back(u);

        for (const auto& v : adj[u])
            if (dis[v] == -1) {
                dfs(v);
                low[u] = min(low[u], low[v]);
            } else
                low[u] = min(low[u], dis[v]);

        if (low[u] == dis[u]) {
            vector<int> group;
            for (;;) {
                int x = stk.back();
                stk.pop_back();
                dis[x] = n;
                group.emplace_back(x);
                if (x == u) break;
            }
            ret.emplace_back(group);
        }
    }
};