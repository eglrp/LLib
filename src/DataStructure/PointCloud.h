#ifndef _LL_POINTCLOUD_H_
#define _LL_POINTCLOUD_H_

#include <vector>

#include "Point.h"

namespace LLib
{
    template <typename T>
    class PointCloud2
    {
        public:
            void add_point(cPoint2<T> &p) { data.push_back(p); };
            int num() const { return data.size(); }
            Point2<T> &operator[](int id) { if(id < data.size()) return data[i]; }
            // TODO:
            int find();
        private:
            std::vector<Point2<T>> data;
    };  // class PointCloud2

    template <typename T>
    class PointCloud3
    {
        public:
            void add_point(cPoint2<T> &p) { data.push_back(p); };
            int num() const { return data.size(); }
            Point3<T> &operator[](int id) { if(id < data.size()) return data[i]; }
            // TODO:
            int find();
        private:
            std::vector<Point3<T>> data;
    };  // class PointCloudd


    using PointCloud2d = PointCloud2<double>;
    using PointCloud2f = PointCloud2<float>;
    using PointCloud2i = PointCloud2<int>;

    using PointCloud3d = PointCloud3<double>;
    using PointCloud3f = PointCloud3<float>;
    using PointCloud3i = PointCloud3<int>;
}   // namespace LLib

#endif  // _LL_POINTCLOUD_H_