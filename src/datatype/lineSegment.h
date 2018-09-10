#ifndef _LL_LINESEGMENT_H_
#define _LL_LINESEGMENT_H_

#include "vectype.h"

namespace LLib
{

    template<typename VecType>
    class lineSegment
    {

    	using FloatType = typename VecType::Scalar;

        private:
        	VecType p0;
        	VecType p1;

        public:
            lineSegment() {}
            lineSegment(const VecType &p0_, const VecType &p1_): p0(p0_), p1(p1_) {}

        	const VecType &getP0() const { return p0;}
        	const VecType &getP1() const { return p1;}

    };  // class lineSegment

    template <typename VecType>
    std::ostream &operator<<(std::ostream &os, const lineSegment<VecType> &l)
    {
        os << l.getP0() << ", " << l.getP1() << std::endl;
        return os;
    }

    using lineSegment2f = lineSegment<vec2f>;
    using lineSegment2d = lineSegment<vec2d>;
    using lineSegment3f = lineSegment<vec3f>;
    using lineSegment3d = lineSegment<vec3d>;

}  // namespace LLib

#endif  // _LL_LINESEGMENT2_H_