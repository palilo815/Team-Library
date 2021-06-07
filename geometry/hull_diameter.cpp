/**
 * @link 
 *      https://codeforces.com/blog/entry/48868
 * @warning
 *      ccw, no duplicate/collinear points
 * @return
 *      two points with max distance on a convex hull
 */
template <typename T>
pair<point2D<T>, point2D<T>> hull_diameter(vector<point2D<T>> hull) {
    pair ret(hull[0], hull[0]);
    T diameter = 0;

    int n = hull.size();
    for (int i = 0, j = n > 1; i < j; ++i) {
        for (;; j = j == n - 1 ? 0 : j + 1) {
            if (chmax(diameter, (hull[i] - hull[j]).dist2()))
                ret = {hull[i], hull[j]};
            if ((hull[(j + 1) % n] - hull[j]).cross(hull[i + 1] - hull[i]) >= 0)
                break;
        }
    }
    return ret;
}