/**
 * @link    https://github.com/kth-competitive-programming/kactl/blob/main/content/graph/WeightedMatching.h
 * @brief   hungarian algorithm
 * @return  minimum cost matching in weighted bipartite graph
 *          (optional) ans[i] = where left[i] is matched with
 * @warning return type (int), infinity value (0x3f3f3f3f)
 */
int hungarian(const vector<vector<int>>& cost) {
    if (cost.empty()) return 0;
    const size_t n = cost.size() + 1, m = cost[0].size() + 1;
    vector<int> u(n), v(m), p(m);
    vector<int> dist(m), pre(m);
    vector<bool> done(m + 1);
    for (size_t i = 1; i != n; ++i) {
        p[0] = i;
        int j0 = 0;
        memset(dist.data(), 0x3f, sizeof(int) * dist.size());
        memset(pre.data(), -1, sizeof(int) * pre.size());
        fill(done.begin(), done.end(), false);
        do {
            done[j0] = true;
            int i0 = p[j0], j1 = -1, delta = INT_MAX;
            for (size_t j = 1; j != m; ++j) {
                if (done[j]) continue;
                auto cur = cost[i0 - 1][j - 1] - u[i0] - v[j];
                if (chmin(dist[j], cur)) pre[j] = j0;
                if (chmin(delta, dist[j])) j1 = j;
            }
            for (size_t j = 0; j != m; ++j) {
                done[j] ? (u[p[j]] += delta, v[j] -= delta) : (dist[j] -= delta);
            }
            j0 = j1;
        } while (p[j0]);
        while (j0) {
            const auto j1 = pre[j0];
            p[j0] = p[j1], j0 = j1;
        }
    }
    return -v[0];
}