/**
 * @author
 *      palilo
 * @brief
 *      determine whether the two objects are intersected
 */
namespace geo::intersected {
template <typename T>
bool segment_segment(const pair<point2D<T>, point2D<T>>& u, const pair<point2D<T>, point2D<T>>& v) {
    if (u.first.side_of(v.first, v.second) * u.second.side_of(v.first, v.second) < 0 &&
        v.first.side_of(u.first, u.second) * v.second.side_of(u.first, u.second) < 0)
        return true;
    return point_in::segment(u.first, v) || point_in::segment(u.second, v) ||
           point_in::segment(v.first, u) || point_in::segment(v.second, u);
}

template <typename T>
bool line_line(const pair<point2D<T>, point2D<T>>& u, const pair<point2D<T>, point2D<T>>& v) {
    return (u.second - u.first).cross(v.second - v.frst) || u.first.side_of(v.first, v.second) == 0;
}
}; // namespace geo::intersected