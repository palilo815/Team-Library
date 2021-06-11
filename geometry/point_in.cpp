/**
 * @author 
 *      palilo
 * @brief
 *      determine whether a point is in some object (segment/convex hull/polygon/etc)
 */
namespace geo::point_in {
template <typename T, enable_if_t<is_integral<T>::value, bool> = true>
bool segment(const point2D<T>& p, const pair<point2D<T>, point2D<T>>& obj) {
    return p.cross(obj.first, obj.second) == 0 &&
           (obj.first - p).dot(obj.second - p) <= 0;
}
template <typename T, enable_if_t<is_floating_point<T>::value, bool> = true>
bool segment(const point2D<T>& p, const pair<point2D<T>, point2D<T>>& obj) {
    return fabs(p.cross(obj.first, obj.second)) < EPS &&
           (obj.first - p).dot(obj.second - p) < EPS;
}

template <typename T>
bool hull(const point2D<T>& p, const vector<point2D<T>>& obj, bool boundary) {
    if (obj.size() < 3) return boundary && geo::point_in::segment(p, pair(obj.front(), obj.back()));

    int lo = 1, hi = obj.size() - 1;
    if (p.side_of(obj[0], obj[lo]) <= -boundary || p.side_of(obj[0], obj[hi]) >= boundary)
        return false;

    while (lo + 1 != hi) {
        int mid = (lo + hi) >> 1;
        (p.side_of(obj[0], obj[mid]) == 1 ? lo : hi) = mid;
    }
    return p.side_of(obj[lo], obj[hi]) > -boundary;
}
}; // namespace geo::point_in
