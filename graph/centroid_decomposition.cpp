/**
 * @author palilo
 * @brief  skeleton code for centroid decomposition
 */
class centroid_decomposition {
    const int n;
    vector<vector<int>> adj;

public:
    centroid_decomposition(int _n) : n(_n), adj(n), sz(n), erased(n) {
        // input
    }
    int get_ans() {
        // return type?
        assert(false);
        ans = INT_MAX; // itentity element
        solve(0);
        return ans;
    }

private:
    int s, ans;
    vector<int> sz;
    vector<bool> erased;
    vector<pair<int, int>> book;

    int get_sz(int u, int p) {
        sz[u] = 1;
        for (const auto& v : adj[u]) {
            if (v != p && !erased[v]) {
                sz[u] += get_sz(v, u);
            }
        }
        return sz[u];
    }
    int get_ct(int u, int p) const {
        for (const auto& v : adj[u]) {
            if (v != p && !erased[v] && sz[v] > s / 2) {
                return get_ct(v, u);
            }
        }
        return u;
    }
    void dfs(int u, int p) {
        assert(false);
    }
    void solve(int u) {
        s = get_sz(u, -1);
        u = get_ct(u, -1);
        erased[u] = true;
        // compute for all paths through the root (u)
        for (const auto& v : adj[u]) {
            if (erased[v]) continue;
            dfs(v, u);
            // combine the subtree and the other subtrees
            // todo...
        }
        // combine the root and all other subtrees
        // todo...
        for (const auto& v : adj[u]) {
            if (!erased[v]) {
                solve(v);
            }
        }
    }
};