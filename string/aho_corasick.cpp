class aho_corasick {
    // change this!
    enum {
        alpha = 26,
        first = 'a'
    };
    struct node {
        array<int, alpha> next;
        int back, start = -1, end = -1;
        // int nmatches = 0; // (nmatches is optional)
        node(int v) { next.fill(-1); }
    };

public:
    aho_corasick(vector<string>& pat) : nodes(1, -1) {
        for (int i = 0; i < int(pat.size()); ++i) {
            insert(pat[i], i);
        }
        nodes[0].back = nodes.size();
        nodes.emplace_back(0);
        queue<int> q;
        for (q.emplace(0); !q.empty(); q.pop()) {
            auto n = q.front(), prev = nodes[n].back;
            for (int i = 0; i < alpha; ++i) {
                auto &ed = nodes[n].next[i], y = nodes[prev].next[i];
                if (ed == -1) ed = y;
                else {
                    nodes[ed].back = y;
                    (nodes[ed].end == -1 ? nodes[ed].end : backp[nodes[ed].start]) = nodes[y].end;
                    // nodes[ed].nmatches += nodes[y].nmatches;
                    q.emplace(ed);
                }
            }
        }
    }
    vector<int> find(const string& word) {
        int n = 0;
        vector<int> res;
        // ll count = 0;
        for (const auto& c : word) {
            n = nodes[n].next[c - first];
            res.emplace_back(nodes[n].end);
            // count += nodes[n].nmatches;
        }
        return res;
    }
    vector<vector<int>> findAll(const vector<string>& pat, const string& word) {
        vector<int> r = find(word);
        vector<vector<int>> res(word.size());
        for (int i = 0; i < int(word.size()); ++i) {
            auto ind = r[i];
            while (ind != -1) {
                res[i - int(pat[ind].size()) + 1].emplace_back(ind);
                ind = backp[ind];
            }
        }
        return res;
    }

private:
    vector<node> nodes;
    vector<int> backp;

    void insert(string& s, int j) {
        assert(!s.empty());
        int n = 0;
        for (const auto& c : s) {
            auto& m = nodes[n].next[c - first];
            if (m == -1) {
                n = m = nodes.size();
                nodes.emplace_back(-1);
            } else {
                n = m;
            }
        }
        if (nodes[n].end == -1) nodes[n].start = j;
        backp.emplace_back(nodes[n].end);
        nodes[n].end = j;
        // nodes[n].nmatches++;
    }
};