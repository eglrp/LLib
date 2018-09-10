#ifndef CORE_GRAPHICS_POLYGON_H_
#define CORE_GRAPHICS_POLYGON_H_

namespace ml {

template<class T>
struct Polygon
{
    static Polygon<T> clip(const Polygon<T> &sourcePoly, const Polygon<T> &clipPoly);
    static Polygon<T> clip(const Polygon<T> &sourcePoly, const Line2<T> &clipLine, const vec2<T> &clipCentroid);

    vector< lineSegment<T> > segments() const
    {
        vector< lineSegment<T> > result;
        if (points.size() <= 1)
            return result;
        for (UINT pointIndex = 0; pointIndex < points.size() - 1; pointIndex++)
            result.push_back(lineSegment<T>(points[pointIndex], points[pointIndex + 1]));
        result.push_back(lineSegment<T>(points.back(), points[0]));
        return result;
    }

    vec2<T> centroid() const
    {
        vec2<T> result;
        for (const auto &p : points)
            result += p;
        return result / (T)points.size();
    }

    void translate(const vec2<T> &v)
    {
        for (vec2<T> &p : points)
            p += v;
    }

    void scale(float s)
    {
        for (vec2<T> &p : points)
            p *= s;
    }

    T convexArea() const
    {
        if (points.size() <= 2)
            return 0.0;
        T sum = 0.0;
        for (size_t v1 = 1; v1 < points.size() - 1; v1++)
            sum += math::triangleArea(points[0], points[v1], points[v1 + 1]);
        return sum;
    }

    vector< vec2<T> > points;
};

typedef Polygon<float> Polygonf;
typedef Polygon<double> Polygond;

//
// Sutherland-Hodgman Clipping
// http://gamedevelopment.tutsplus.com/tutorials/understanding-sutherland-hodgman-clipping-for-physics-engines--gamedev-11917
// http://www.cc.gatech.edu/grads/h/Hao-wei.Hsieh/Haowei.Hsieh/code2.html
//
template<class T>
Polygon<T> Polygon<T>::clip(const Polygon<T> &sourcePoly, const Line2<T> &clipLine, const vec2<T> &clipCentroid)
{
    Polygon<T> output;

    if (sourcePoly.points.size() == 0)
        return output;

    //
    // find the normal of the line segment pointing towards clipCentroid
    //
    vec2<T> normal = clipLine.dir();
    normal = vec2<T>(-normal.y, normal.x);
    if (((clipCentroid - clipLine.p0()) | normal) < 0.0f)
        normal = -normal;

    auto sideTest = [&](const vec2<T> &pt)
    {
        return ((pt - clipLine.p0()) | normal) >= 0.0f;
    };

    vec2<T> startPoint = sourcePoly.points.back();
    for (const vec2<T> &endPoint : sourcePoly.points)
    {
        bool startSide = sideTest(startPoint);
        bool endSide = sideTest(endPoint);

        if (startSide && endSide)
        {
            output.points.push_back(endPoint);
        }
        if (startSide && !endSide)
        {
            vec2<T> intersection = startPoint;
            intersection::intersectLine2Line2(clipLine, Line2<T>(startPoint, endPoint), intersection);
            output.points.push_back(intersection);
        }
        if (!startSide && endSide)
        {
            vec2<T> intersection = startPoint;
            intersection::intersectLine2Line2(clipLine, Line2<T>(startPoint, endPoint), intersection);
            output.points.push_back(intersection);
            output.points.push_back(endPoint);
        }

        startPoint = endPoint;
    }

    return output;
}

template<class T>
Polygon<T> Polygon<T>::clip(const Polygon<T> &sourcePoly, const Polygon<T> &clipPoly)
{
    Polygon<T> output = sourcePoly;
    vec2<T> clipCentroid = clipPoly.centroid();

    for (const lineSegment<T> &clipSegment : clipPoly.segments())
        output = clip(output, Line2<T>(clipSegment), clipCentroid);

    return output;
}

}  // namespace ml

#endif  // CORE_GRAPHICS_POLYGON_H_