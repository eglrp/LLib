#ifndef _LL_LINE_H_
#define _LL_LINE_H_

#include "vectype.h"

namespace LLib
{

    template<typename VecType>
    class line
    {
	    using FloatType = typename VecType::Scalar;

        private:
        	VecType p;
        	VecType dir;

        public:
            line() {}
            line(const VecType &p0, const VecType &p1) { assert(p0 != p1); p = p0; dir = p1 - p0; dir /= dir.norm(); }

        	const VecType & getP() const { return p; }
        	const VecType & getDir() const { return dir; }

    };  // class line

    template <typename VecType>
    std::ostream &operator<<(std::ostream &os, const line<VecType> &l)
    {
        os << l.getP() << ", " << l.getDir() << std::endl;
        return os;
    }

    using line2f = line<vec2f>;
    using line2d = line<vec2d>;
    using line3f = line<vec3f>;
    using line3d = line<vec3d>;

}  // namespace LLib

#endif  // _LL_LINE_H_