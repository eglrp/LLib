#ifndef _LL_LINESEGMENT3_H_
#define _LL_LINESEGMENT3_H_

#include "vectype.h"

namespace LLib
{
    template<typename VecType>
    class lineSegment3
    {
        private:
        	VecType p0;
        	VecType p1;

        public:
            lineSegment3(const VecType &p0_, const VecType &p1_);

        	const VecType &getP0() const;
        	const VecType &getP1() const;

    };  // class lineSegment3

    template <typename VecType>
    std::ostream &operator<<(std::ostream &os, const lineSegment3<VecType> &l)
    {
        os << l.getP0() << ", " << l.getP1() << std::endl;
        return os;
    }

    /*
            lineSegment3 Implementation
    */ 

    template<typename VecType>
    inline lineSegment3<VecType>::lineSegment3(const VecType &p0_, const VecType &p1_)
    {
        p0 = p0_;
        p1 = p1_;
    }

    template<typename VecType>
    inline const VecType &lineSegment3<VecType>::getP0() const
    {
        return p0;
    }

    template<typename VecType>
    inline const VecType &lineSegment3<VecType>::getP1() const
    {
        return p1;
    }

    /*
            lineSegment2 Defination
    */ 
    typedef lineSegment3<vec3f> lineSegment3f;
    typedef lineSegment3<vec3d> lineSegment3d;

}  // namespace LLib

#endif  // _LL_LINESEGMENT3D_H_