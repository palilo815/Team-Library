/**
 * @author  palilo
 * @brief   simple cycle detection algorithm. implemented as non-reculsive way.
 * @return  vector of vertices on cycle
 * @warning first and last vertex are repeated
 *          i.e. cycle.front() == cycle.back()
 */
vector<int> find_cycle(vector<vector<int>>& adj) {
    vector<char> colour(adj.size());
    vector<int> cycle, eid;
    cycle.reserve(adj.size());
    eid.reserve(adj.size());
    auto dfs = [&](int u) -> void {
        colour[u] = 'g';
        cycle.emplace_back(u);
        eid.emplace_back(0);
        while (!cycle.empty()) {
            for (auto &u = cycle.back(), &i = eid.back();; ++i) {
                if (i == int(adj[u].size())) {
                    colour[u] = 'b';
                    cycle.pop_back();
                    eid.pop_back();
                    break;
                } else if (!colour[adj[u][i]]) {
                    colour[adj[u][i]] = 'g';
                    cycle.emplace_back(adj[u][i]);
                    eid.emplace_back(0);
                    break;
                } else if (colour[adj[u][i]] == 'g') {
                    cycle.emplace_back(adj[u][i]);
                    return;
                }
            }
        }
    };
    for (int i = 0; i < int(adj.size()); ++i) {
        if (!colour[i]) {
            dfs(i);
            if (!cycle.empty()) {
                cycle.erase(cycle.begin(), find(cycle.begin(), cycle.end(), cycle.back()));
                return cycle;
            }
        }
    }
    return {};
};