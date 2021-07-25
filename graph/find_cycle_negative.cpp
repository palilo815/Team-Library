/**
 * @link    https://cp-algorithms.com/graph/finding-negative-cycle-in-graph.html
 * @brief   negative cycle detection algorithm based on Bellman-Ford algorithm
 * @return  vector of vertices on negative cycle
 * @warning first and last vertex are repeated
 *          i.e. cycle.front() == cycle.back()
 */
template <typename dist_t, typename edge_t>
vector<int> find_negative_cycle(int n, vector<edge_t>& edges) {
    vector<dist_t> d(n);
    vector<int> p(n, -1);
    int x = -1;
    for (int i = 0; i < n; ++i) {
        x = -1;
        for (const auto& [u, v, w] : edges) {
            if (d[v] > d[u] + w) {
                d[v] = d[u] + w;
                p[v] = u;
                x = v;
            }
        }
    }
    if (x == -1) return {};
    for (int i = n; i--; x = p[x]) {
        ;
    }
    vector cycle = {x};
    for (int v = p[x];; v = p[v]) {
        cycle.emplace_back(v);
        if (v == x) break;
    }
    reverse(cycle.begin(), cycle.end());
    return cycle;
}