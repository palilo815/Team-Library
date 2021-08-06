/**
 * @author palilo
 * @brief  skeleton code of trie
 */
class trie {
    enum {
        alpha = 26,
        offset = 'a',
    };
    struct trie_node {
        array<int, alpha> child;
        trie_node() = default;
    };

public:
    trie() : tree(1) {}

    void add(const string& s) {
        int node = 0;
        for (const auto& c : s) {
            if (!tree[node].child[c - offset]) {
                tree[node].child[c - offset] = tree.size();
                tree.emplace_back();
            }
            node = tree[node].child[c - offset];
        }
        // todo...
        // check endpoint
    }
    int query(const string& s) const {
        int node = 0, ret = 0;
        for (const auto& c : s) {
            // todo...
            node = tree[node].child[c - offset];
        }
        return ret;
    }

private:
    vector<trie_node> tree;
};