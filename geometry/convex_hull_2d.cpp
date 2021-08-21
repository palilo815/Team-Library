/**
 * @link    https://codeforces.com/blog/entry/48868
 * @return  points of the hull in ccw order
 * @warning points on the edge of the hull will be ignored
 */
namespace geo {
template <typename T>
vector<point2D<T>> convex_hull(vector<point2D<T>>& pts) {
    if (pts.size() <= 1) return pts;
    sort(pts.begin(), pts.end());
    vector<point2D<T>> hull(pts.size() + 1);
    size_t s = 0, t = 0;
    for (const auto& p : pts) {
        while (t >= s + 2 && hull[t - 2].cross(hull[t - 1], p) <= 0) --t;
        hull[t++] = p;
    }
    s = --t;
    reverse(pts.begin(), pts.end());
    for (const auto& p : pts) {
        while (t >= s + 2 && hull[t - 2].cross(hull[t - 1], p) <= 0) t--;
        hull[t++] = p;
    }
    return {hull.begin(), hull.begin() + t - 1 - (t == 2 && hull[0] == hull[1])};
}
}; // namespace geo