/**
 * @link   https://github.com/kth-competitive-programming/kactl/blob/main/content/graph/BellmanFord.h
 * @brief  Bellman-Ford algorithm
 * @tparam dist_t $ \ge n^2 * \max{w} $
 * @tparam edge_t {u, v, w}
 * @param  n      # of vertices
 * @param  edges  edges
 * @param  s      source
 * @note   $ O(n |edges|) $
 * @return the distances from source
 *         ignore the second element
 *         let inf = numeric_limits<dist_t>::max();
 *             if dist ==  inf -> unreachable
 *             if dist == -inf -> reachable through negative-weight cycles
 */
template <typename dist_t, typename edge_t>
vector<pair<dist_t, int>> bellman_ford(int n, vector<edge_t>& edges, int s) {
    const dist_t inf = numeric_limits<dist_t>::max();

    vector nodes(n, pair(inf, -1));
    nodes[s].first = 0;

    sort(edges.begin(), edges.end(), [&](const auto& lhs, const auto& rhs) {
        return (lhs.u < lhs.v ? lhs.u : ~lhs.u) < (rhs.u < rhs.v ? rhs.u : ~rhs.u);
    });

    const int lim = n / 2 + 2;
    for (int i = 0; i < lim; ++i)
        for (const auto& e : edges) {
            auto &cur = nodes[e.u], &dest = nodes[e.v];
            if (abs(cur.first) == inf) continue;
            if (T d = cur.first + e.w; d < dest.first) {
                dest.second = e.u;
                dest.first = (i == lim - 1 ? -inf : d);
            }
        }

    for (int i = 0; i < lim; ++i)
        for (const auto& e : edges)
            if (nodes[e.u].first == -inf)
                nodes[e.v].first = -inf;

    return nodes;
}