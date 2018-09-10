#ifndef _LL_LINE2D_H_
#define _LL_LINE2D_H_

#include "vectype.h"

namespace LLib
{

    template<typename VecType>
    class line2
    {
        private:
        	VecType p;
        	VecType dir;

        public:
            line2(const VecType &p0, const VecType &p1);

        	const VecType & getP() const;
        	const VecType & getDir() const;

    };  // class Line2

    template <typename VecType>
    std::ostream &operator<<(std::ostream &os, const line2<VecType> &l)
    {
        os << l.getP() << ", " << l.getDir() << std::endl;
        return os;
    }

    /*
            Line2 Implementation
    */
    template<typename VecType>
    inline line2<VecType>::line2(const VecType &p0, const VecType &p1)
    {
        assert(p0 != p1);

        p = p0;
        dir = p1 - p0;
        dir /= dir.norm();
	}

    template<typename VecType>
	inline const VecType &line2<VecType>::getP() const
    {
        return p;
	}

    template<typename VecType>
	inline const VecType &line2<VecType>::getDir() const
    {
        return dir;
	}

    /*
            Line2 Defination
    */
    typedef line2<vec2f> line2f;
    typedef line2<vec2d> line2d;

}  // namespace LLib

#endif  // _LL_LINE2D_H_