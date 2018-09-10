#ifndef _LL_LINE3D_H_
#define _LL_LINE3D_H_

#include "vectype.h"

namespace LLib
{

    template<typename VecType>
    class line3
    {
        private:
        	VecType p;
        	VecType dir;

        public:
            line3(const VecType &p0, const VecType &p1);

        	const VecType & getP() const;
        	const VecType & getDir() const;

    };  // class line3

    template <typename VecType>
    std::ostream &operator<<(std::ostream &os, const line3<VecType> &l)
    {
        os << l.getP() << ", " << l.getDir() << std::endl;
        return os;
    }

    /*
            line3 Implementation
    */
    template<typename VecType>
    inline line3<VecType>::line3(const VecType &p0, const VecType &p1)
    {
        assert(p0 != p1);

        p = p0;
        dir = p1 - p0;
        dir /= dir.norm();
	}

    template<typename VecType>
	inline const VecType &line3<VecType>::getP() const
    {
        return p;
	}

    template<typename VecType>
	inline const VecType &line3<VecType>::getDir() const
    {
        return dir;
	}

    /*
            line3 Defination
    */
    typedef line3<vec3f> line3f;
    typedef line3<vec3d> line3d;

}  // namespace LLib

#endif  // _LL_LINE3D_H_