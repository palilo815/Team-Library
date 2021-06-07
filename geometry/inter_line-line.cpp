template <typename T>
pair<int, point2D<T>> line_inter(const point2D<T>& s1, const point2D<T>& e1, const point2D<T>& s2, const point2D<T>& e2) {
    if (auto c = (e1 - s1).cross(e2 - s2); c)
        return {1, (s1 * s2.cross(e1, e2) + e1 * s2.cross(e2, s1)) / c};
    else
        return {-(s1.cross(e1, s2) == 0), point2D<T>(0, 0)};
}