#ifndef _LL_POLYGEN_H_
#define _LL_POLYGEN_H_

namespace LLib
{
    template <typename T>
    class Ploygen
    {
        // TODO
        // static Polygon<T> clip(const Polygon<T> &sourcePoly, const Polygon<T> &clipPoly);
        // static Polygon<T> clip(const Polygon<T> &sourcePoly, const Line2<T> &clipLine, const vec2<T> &clipCentroid);

        std::vector< vec2<T> > points;

        std::vector< LineSegment2<T> > segments() const {
            std::vector< LineSegment2<T> > result;
            if (points.size() <= 1)
                return result;
            for (UINT pointIndex = 0; pointIndex < points.size() - 1; pointIndex++)
                result.push_back(LineSegment2<T>(points[pointIndex], points[pointIndex + 1]));
            result.push_back(LineSegment2<T>(points.back(), points[0]));
            return result;
        }
    
        vec2<T> centroid() const {
            vec2<T> result;
            for (const auto &p : points)
                result += p;
            return result / (T)points.size();
        }
    
        void translate(const vec2<T> &v) {
            for (vec2<T> &p : points)
                p += v;
        }
    
        void scale(float s) {
            for (vec2<T> &p : points)
                p *= s;
        }
    
        T convexArea() const {
            if (points.size() <= 2)
                return 0.0;
            T sum = 0.0;
            for (size_t v1 = 1; v1 < points.size() - 1; v1++)
                sum += ((points[v1] - points[0])^(points[v1+1] - points[0])).length()*0.5;
            return sum;
        }

    };  // class Polygen

    typedef Polygon<float> Polygonf;
    typedef Polygon<double> Polygond;

}  // namespace LLib

#endif  // _LL_POLYGEN_H_