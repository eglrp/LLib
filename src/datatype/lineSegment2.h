#ifndef _LL_LINESEGMENT2_H_
#define _LL_LINESEGMENT2_H_

#include "vectype.h"

namespace LLib
{

    template<typename VecType>
    class lineSegment2
    {
        private:
        	VecType p0;
        	VecType p1;

        public:
            lineSegment2(const VecType &p0_, const VecType &p1_);

        	const VecType &getP0() const;
        	const VecType &getP1() const;

    };  // class lineSegment2

    template <typename VecType>
    std::ostream &operator<<(std::ostream &os, const lineSegment2<VecType> &l)
    {
        os << l.getP0() << ", " << l.getP1() << std::endl;
        return os;
    }

    /*
            lineSegment2 Implementation
    */ 

    template<typename VecType>
    inline lineSegment2<VecType>::lineSegment2(const VecType &p0_, const VecType &p1_)
    {
        p0 = p0_;
        p1 = p1_;
    }

    template<typename VecType>
    inline const VecType &lineSegment2<VecType>::getP0() const
    {
        return p0;
    }

    template<typename VecType>
    inline const VecType &lineSegment2<VecType>::getP1() const
    {
        return p1;
    }

    /*
            lineSegment2 Defination
    */ 
    typedef lineSegment2<vec2f> lineSegment2f;
    typedef lineSegment2<vec2d> lineSegment2d;

}  // namespace LLib

#endif  // _LL_LINESEGMENT2D_H_