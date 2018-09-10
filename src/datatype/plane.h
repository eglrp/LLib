#ifndef _LL_PLANE_H_
#define _LL_PLANE_H_

#include "vectype.h"

namespace LLib
{

	template<typename VecType>
	class plane
	{
		using FloatType = typename VecType::Scalar;
	
		private:
			VecType p;
	
		public:
			plane() {}
			plane(const VecType& p_) { p = p_; }
	
			VecType getNormal() const { return p/p.norm(); }
			FloatType getDistance() const { return p.norm(); }
	
			FloatType distanceToPoint(const VecType &point) const { return std::abs(p.norm() - std::abs(p.dot(point))); }
	
			// TODO:
			// VecType projectPointToPlane(const VecType &point) const { return point - p.dot(point)*p; }
	
	};
	
	using planef = plane<vec3f>;
	using planed = plane<vec3d>;

} //namespace LLib


#endif	// _LL_PLANE_H_