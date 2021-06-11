/**
 * @author
 *      palilo
 * @brief
 *      determine whether the two objects are intersected
 * @warning
 *      precision in `sign(cross)`. it can be greater than `EPS`
 */
namespace geo::intersected {
template <typename T>
bool segment_segment(const pair<point2D<T>, point2D<T>>& u, const pair<point2D<T>, point2D<T>>& v) {
    if (sign(u.first.cross(u.second, v.first)) * sign(u.first.cross(u.second, v.second)) < 0 &&
        sign(v.first.cross(v.second, u.first)) * sign(v.first.cross(v.second, u.second)) < 0)
        return true;
    return point_in::segment(u.first, v) || point_in::segment(u.second, v) ||
           point_in::segment(v.first, u) || point_in::segment(v.second, u);
}

template <typename T>
bool line_line(const pair<point2D<T>, point2D<T>>& u, const pair<point2D<T>, point2D<T>>& v) {
    return (u.second - u.first).cross(v.second - v.frst) || u.first.side_of(v.first, v.second) == 0;
}
}; // namespace geo::intersected