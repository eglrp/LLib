#ifndef _LL_POINTCLOUD_H_
#define _LL_POINTCLOUD_H_

#include "vectype.h"

namespace LLib
{
    template <typename VecType>
    class pointcloud
    {
	    using FloatType = typename VecType::Scalar;

        public:
            pointcloud(int pointnum_): pointnum(pointnum_) { data = new VecType[pointnum]; }
            ~pointcloud() { delete []data; }

            int num() const { return pointnum; }

            VecType *getData() { return data; }
            const VecType *getData() const { return data; }

            VecType &operator[](int index) { return data[index]; }
            const VecType &operator[](int index) const { return data[index]; }

            VecType &operator()(int index) { return data[index]; }
            const VecType &operator()(int index) const { return data[index]; }

        private:
            int pointnum;
            VecType *data;
    };  // class pointcloud

    using pointcloud2f = pointcloud<vec2f>;
    using pointcloud2d = pointcloud<vec2d>;
    using pointcloud3f = pointcloud<vec3f>;
    using pointcloud3d = pointcloud<vec3d>;
}   // namespace LLib

#endif  // _LL_POINTCLOUD_H_