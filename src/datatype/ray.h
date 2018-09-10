#ifndef _LL_RAY_H_
#define _LL_RAY_H_

#include "vectype.h"

namespace LLib
{

	template<typename VecType>
	class ray
	{
		using FloatType = typename VecType::Scalar;

		public:
		    ray(){}

			inline ray(const VecType &p_, const VecType &dir_): p(p_), dir(dir_) { dir /= dir.norm(); }

			inline VecType getHitPoint(FloatType t) const { return p + t * dir; }
			const VecType& getOrigin() const { return p; }
			const VecType& getDirection() const { return dir; }

			// TODO:
			// inline void transform(const mat44<FloatType>& m);
			// inline void rotate(const Matrix3x3<FloatType>& m);
			// inline void translate(const vec3<FloatType>& p);

		private:
			VecType dir;
			VecType p;

	};


	using ray2f = ray<vec2f>;
	using ray2d = ray<vec2d>;
	using ray3f = ray<vec3f>;
	using ray3d = ray<vec3d>;

}  // namespace LLib

#endif  // _LL_RAY_H_