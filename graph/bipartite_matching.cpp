/**
 * @brief
 *      fast Kuhn's algorithm
 * 
 * @param n size of  left group
 * @param m size of right group
 * 
 * @warning
 *      `minimum_vertex_cover` must be called after `maximum_matching`
 * 
 * @note 
 *      `maximum_matching`      $ O(n^2 m) $	-> place small group to left!
 *      `minimum_vertex_cover`  $ O(n + m) $
 * 			
 * @return
 *      `maximum_matching`      # of maximum matching
 *      `minimum_vertex_cover`	ids of vertices
 *                              if id >= 0 -> vertex id in L
 *                              if id < 0 -> vertex ~id in R
 */
class bipartite_matching {
public:
    bipartite_matching(int _n, int _m) : n(_n), m(_m),
                                         adj(n), match(n, -1), rev(m, -1), visited(n) {}

    void add_edge(int u, int v) {
        assert(0 <= u and u < n and 0 <= v and v < m);
        adj[u].emplace_back(v);
    }
    int maximum_matching() {
        for (bool update = true; update;) {
            fill(visited.begin(), visited.end(), false);
            update = false;

            for (int i = 0; i < n; ++i)
                if (match[i] == -1 && dfs(i))
                    update = true;
        }
        return n - count(match.begin(), match.end(), -1);
    }
    vector<int> minimum_vertex_cover() {
        vector<bool> check(m);
        auto bfs = [&](int src) {
            queue<int> q;
            q.emplace(src);
            visited[src] = true;

            while (!q.empty()) {
                const auto u = q.front();
                q.pop();

                for (const auto& v : adj[u])
                    if (~rev[v] && !visited[rev[v]] && match[u] != v) {
                        check[v] = true;
                        visited[rev[v]] = true;
                        q.emplace(rev[v]);
                    }
            }
        };

        fill(visited.begin(), visited.end(), false);
        for (int i = 0; i < n; ++i)
            if (match[i] == -1 && !visited[i])
                bfs(i);

        vector<int> ret;
        ret.reserve(n - count(match.begin(), match.end(), -1));

        for (int i = 0; i < n; ++i)
            if (!visited[i])
                ret.emplace_back(i);
        for (int i = 0; i < m; ++i)
            if (check[i])
                ret.emplace_back(~i);

        return ret;
    }

private:
    const int n, m;
    vector<vector<int>> adj;
    vector<int> match, rev;
    vector<bool> visited;

    bool dfs(int u) {
        visited[u] = true;
        for (const auto& v : adj[u]) {
            if (rev[v] == -1 || (!visited[rev[v]] && dfs(rev[v]))) {
                match[u] = v, rev[v] = u;
                return true;
            }
        }
        return false;
    }
};