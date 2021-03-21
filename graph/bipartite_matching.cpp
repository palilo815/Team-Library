#include <bits/stdc++.h>
using namespace std;

/**
 * @brief 정점이 두 그룹(L, R)으로 나뉘는 이분 그래프일 때 최대 매칭과, 최소 점 덮개를 구함.
 * @example bipartite_matching solver(n, m);
 *          
 *          cout << solver.maximum_matching() << endl;
 *          
 *          vector<int> vtx = solver.minimum_vertex_cover;
 *          for (const auto& id : vtx) {
 *              if (id >= 0)
 *                  cout << id << " in L" << endl;
 *              else
 *                  cout << ~id << " in R" << endl;
 *          }
 */
struct bipartite_matching {
    /**
     * @param _n size of (L)
     * @param _m size of (R)
     */
    bipartite_matching(int _n, int _m) : n(_n), m(_m),
                                         adj(n), match(n, -1), rev(m, -1), visited(n) {}

    /**
     * @brief add edge from $u(\in L)$ to $v(\in R)$
     */
    void add_edge(int u, int v) {
        assert(0 <= u and u < n and 0 <= v and v < m);
        adj[u].emplace_back(v);
    }
    /**
     * @note $O(n^2 m)$
     * @return # of maximum matching
     */
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
    /**
     * @warning MUST BE USED AFTER `maximum_matching`
     * 
     * @note $O(n + m)$
     * @return ids of vertices
     *         if id >= 0 -> vertex id in L
     *         if id < 0 -> vertex ~id in R
     */
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

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef home
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
}