/**
 * @author palilo 
 * @brief  maintain the maximum values of stack
 * @note   all operations are $ O(1) $
 */
template <typename T>
class max_stack {
    vector<T> stk;
    T mx;

public:
    max_stack() = default;

    T get_max() const {
        assert(!stk.empty());
        return mx;
    }
    T top() const {
        assert(!stk.empty());
        return stk.back() > mx ? mx : stk.back();
    }
    void push(T x) {
        if (stk.empty()) {
            mx = x;
            stk.emplace_back(x);
        } else if (x > mx) {
            stk.emplace_back(x * 2 - mx);
            mx = x;
        } else
            stk.emplace_back(x);
    }
    void pop() {
        assert(!stk.empty());
        if (stk.back() > mx)
            mx = 2 * mx - stk.back();
        stk.pop_back();
    }
};