#ifndef _LL_QUATERNION_H_
#define _LL_QUATERNION_H_

#include "../Vec/vec_header.h"

namespace LLib
{
    template <typename T>
    class Quaternion
    {
    public:
        typedef T ValueType;

    private:
        union{

            struct{
                T _real;
                vec3<T> _imag;
            };

            struct{
                T _w;
                T _x, _y, _z;
            };

            vec4<T> _q;

        }; 

    public:
        // Constructor
        Quaternion() : _w(1), _x(0), _y(0), _z(0) {}

        Quaternion(const vec4<T> &q) : _q(q) {}

        Quaternion(T real, const vec3<T> &imag) : _real(real), _imag(imag) {}

        Quaternion(T w, T x, T y, T z) : _w(w), _x(x), _y(y), _z(z) {}

        Quaternion(const Quaternion<T> &other) : _real(other.real()), _imag(other.imag()) {}

        // TODO
        // template <typename T>
        // Quaternion(const AxisAngle<U> &aa){}

        // template <typename T>
        // Quaternion(const EulerAngle<U> &e){}

        // template <typename T>
        // Quaternion(const RotationMatrix<U> &rm){}

        // template <typename T>
        // Quaternion(const TransformMatrix<U> &tm)

        // //! Constructs a quaternion between a start and end point
		// Quaternion(const vec3<FloatType>& from, const vec3<FloatType>& to) {
		// 	//vec3<FloatType> vecHalf = (from + to).getNormalized();
		// 	//m_Real = vecHalf | to;
		// 	//m_Imag = vecHalf ^ to;

		// 	vec3<FloatType> v0 = from.getNormalized();
		// 	vec3<FloatType> v1 = to.getNormalized();

		// 	const FloatType d = v0 | v1;
		// 	if (d >= (FloatType)1.0) // If dot == 1, vectors are the same
		// 	{
		// 		setIdentity();
		// 		return;
		// 	}
		// 	else if (d <= (FloatType)-1.0) // exactly opposite
		// 	{
		// 		vec3<FloatType> axis(1.0, 0.0, 0.0);
		// 		axis = axis ^ v0;
		// 		if (axis.length()==0)
		// 		{
		// 			axis = vec3<FloatType>(0.0,1.0,0.0);
		// 			axis = axis ^ v0;
		// 		}
		// 		m_Imag = axis.getNormalized();
		// 		m_Real = 0;
		// 		normalize();
		// 		return;
		// 		//return set(axis.X, axis.Y, axis.Z, 0).normalize();
		// 	}

		// 	const FloatType s = sqrt( (1+d)*2 ); // optimize inv_sqrt
		// 	const FloatType invs = (FloatType)1.0 / s;
		// 	const vec3<FloatType> c = (v0^v1)*invs;
		// 	m_Imag = c;
		// 	m_Real = s*(FloatType)0.5;
		// 	normalize();
		// 	//return set(c.X, c.Y, c.Z, s * 0.5f).normalize();
		// }

        template <typename U>
        Quaternion<U> toType() const {
            return Quaternion<U>(static_cast<U>(_real), _imag.toType<U>());
        }

        // get
        const T &real() const {
            return _real;
        }

        const vec3<T> &imag() const {
            return _imag;
        }

        const T &x() const {
            return _x;
        }

        const T &y() const {
            return _y;
        }

        const T &z() const {
            return _z;
        }

        const T &w() const {
            return _w;
        }

        static Quaternion<T> Ideneity(){
            return Quaternion<T>();
        }

        // set
        void setIdentity(){
            _real = 1;
            _imag = vec3<T>(0, 0, 0);
        }

        void setReal(T real){
            _real = real;
        }

        void setImag(const vec3<T> &imag){
            _imag = imag;
        }

        // calculate
        // http://www.euclideanspace.com/maths/algebra/realNormedAlgebra/quaternions/arithmetic/index.htm
        Quaternion<T> &operator=(const Quaternion<T> &other){
            _real = other.real();
            _imag = other.imag();
            return *this;
        }

        bool operator==(const Quaternion<T> &other) const {
            return (_real == other.real() && _imag == other.imag());
        }

        bool operator!=(const Quaternion<T> &other) const {
            return (_real != other.real() && _imag != other.imag());
        }

        void operator+=(const Quaternion<T> &other){
            _real += other._real;
            _imag += other._imag;
        }

        friend Quaternion<T> operator+(const Quaternion<T> &lhs, const Quaternion<T> &rhs){
            Quaternion<T> result(lhs);
            result += rhs;
            return result;
        }

        void operator-=(const Quaternion<T> &other){
            _real -= other._real;
            _imag -= other._imag;
        }

        friend Quaternion<T> operator-(const Quaternion<T> &lhs, const Quaternion<T> &rhs){
            Quaternion<T> result(lhs);
            result -= rhs;
            return result;
        }

        void operator*=(T x){
            _real *= x;
            _imag *= x;
        }

        // rotate a point
        // http://www.euclideanspace.com/maths/algebra/realNormedAlgebra/quaternions/transforms/index.htm
        template <typename U>
        vec3<U> rotate(const vec3<U> &v) const {
            Quaternion<U> p_in = Quaternion<U>(0, v);
            Quaternion<U> p_out = (*this)*p_in*(this->getConj());
            return p_out._real; 
        }

        template <typename U>
        vec3<U> operator*(const vec3<U> &v) const {
            return this->rotate(v);
        }

        // http://www.euclideanspace.com/maths/algebra/realNormedAlgebra/quaternions/functions/index.htm
        Quaternion<T> &conj(){
            _imag = -_imag;
            return *this;
        }

        Quaternion<T> getConj() const {
            Quaternion<T> resut(*this);
            return result.conj();
        }

        Quaternion<T> &inv(){
            this->normalize();
            this->conj();
            return *this;
        }

        Quaternion<T> getInv() const {
            Quaternion<T> result(*this);
            return result.inv();
        }

        // i*i = j*j = k*k = -1
        // i*j = k,
        // j*i = -k
        // j*k = i,
        // k*j = -i
        // k*i = j,
        // i*k = -j

        //  (a + i b + j c + k d)*(e + i f + j g + k h)
        // =	
        // a*e - b*f - c*g - d*h
        // + i (b*e + a*f + c*h- d*g)
        // + j (a*g - b*h+ c*e + d*f)
        // + k (a*h + b*g - c*f + d*e)

        // (sa,va) * (sb,vb) = (sa*sb-va•vb,va × vb + sa*vb + sb*va)
        void operator*=(const Quaternion<T> &other){
            T realTmp = _real*other._real - dot(_imag, other._imag);
            vec3<T> imagTmp = _imag*other._real + _real*other._imag + cross(_imag, other._imag);
            _real = realTmp;
            _imag = imagTmp;
        }

        friend Quaternion<T> operator*(const Quaternion<T> &lhs, const Quaternion<T> &rhs){
            Quaternion result(lhs);
            result *= rhs;
            return result;
        }

        void operator/=(T x){
            assert(x != 0);
            _real /= x;
            _imag /= x;
        }

        Quaternion<T> operator/(T x) const {
            Quaternion<T> result(*this);
            result /= x;
            return result;
        }

        // normalize
        void normalize(){
           double l = _q.length();
            if(l < EPS){
                *this =  Quaternion<T>::Ideneity();
            } else {
                *this = Quaternion(_q/l);
            }
        }

        Quaternion<T> getNormalize() const {
            Quaternion result(*this);
            return result.normalize();
        }

        // length
        double lengthSq() const {
            return _q.lengthSq();
        }

        double length() const {
            return _q.length();
        }


        // TODO
        // void set(const AxisAngle<T> &aa){

        // }

        // void set(const EulerAngle<T> &e){

        // }

        // void set(const Quaternion<T> &other){
        //     *this = other;
        // }

        // void set(const RotationMatrix<T> &R){

        // }

        // void set(const TransformMatrix<T> &T){

        // }

        // // convert

        // AxisAngle<T> toAxisAngle() const {
        //     AxisAngle<T> result;
        //     return result;
        // }

        // EulerAngle<T> toEulerAngle() const {
        //     EulerAngle<T> result;
        //     return result;
        // }

        // RotationMatrix<T> toRotationMatrix() const {
        //     RotationMatrix<T> result;
        //     return result;
        // }

        // TransformMatrix<T> toTransformMatrix() const {
        //     TransformMatrix<T> result;
        //     return result;
        // }


        // slerp
        // http://www.euclideanspace.com/maths/algebra/realNormedAlgebra/quaternions/slerp/index.htm
        // generates a quaternion between two given quaternions in proportion to the variable t, 
        // if t=0 then result=lhs, if t=1 then result=rhs, if t is between them then qm will interpolate between them.
        friend Quaternion<T> slerp(const Quaternion<T> &lhs, const Quaternion &rhs, double t) {
            // quaternion to return
            Quaternion<T> result;
            // Calculate angle between them.
            double cosHalfTheta = dot(lhs._q, rhs._q);
            // if lhs=rhs or lhs=-rhs then theta = 0 and we can return lhs
            if (abs(cosHalfTheta) >= 1.0){
                result = lhs;
                return result;
            }
            // Calculate temporary values.
            double halfTheta = acos(cosHalfTheta);
            double sinHalfTheta = sqrt(1.0 - cosHalfTheta*cosHalfTheta);
            // if theta = 180 degrees then result is not fully defined
            // we could rotate around any axis normal to qa or qb
            if (fabs(sinHalfTheta) < EPS){ // fabs is floating point absolute
            result = (lhs + rhs)*0.5;
                return result;
            }
            double ratioA = sin((1 - t) * halfTheta) / sinHalfTheta;
            double ratioB = sin(t * halfTheta) / sinHalfTheta; 
            //calculate Quaternion.
            result = ratioA*lhs + ratioB*rhs;
            return result;
        }

        friend std::ostream &operator<<(std::ostream &out, const Quaternion &q){
            out << "(" << q._w << ", " << q._x << ", " << q._y << "; " << q._z << ")";
            return out;
        }

        friend std::istream &operator>>(std::istream &in, Quaternion &&q){
            in >> q._w >> q._x >> q._y >> q._z;
            return in;
        }

        friend bool floatEqual(const Quaternion &lhs, const Quaternion &rhs){
            using LLib::Math::floatEqual;
            return floatEqual(lhs._real, rhs._real) && floatEqual(lhs._imag, rhs._imag);
        }

    }; // class Quaternion
} // namespace LLib

#endif // _LL_QUATERNION_H_


//     /** \returns the dot product of \c *this and \a other
//     * Geometrically speaking, the dot product of two unit quaternions
//     * corresponds to the cosine of half the angle between the two rotations.
//     * \sa angularDistance()
//     */
//   template<class OtherDerived> EIGEN_DEVICE_FUNC inline Scalar dot(const QuaternionBase<OtherDerived>& other) const { return coeffs().dot(other.coeffs()); }


// /** \returns the angle (in radian) between two rotations
//   * \sa dot()
//   */
// template <class Derived>
// template <class OtherDerived>
// EIGEN_DEVICE_FUNC inline typename internal::traits<Derived>::Scalar
// QuaternionBase<Derived>::angularDistance(const QuaternionBase<OtherDerived>& other) const
// {
//   EIGEN_USING_STD_MATH(atan2)
//   Quaternion<Scalar> d = (*this) * other.conjugate();
//   return Scalar(2) * atan2( d.vec().norm(), numext::abs(d.w()) );
// }


//   /** \returns the quaternion which transform \a a into \a b through a rotation */
//   template<typename Derived1, typename Derived2>
//   EIGEN_DEVICE_FUNC Derived& setFromTwoVectors(const MatrixBase<Derived1>& a, const MatrixBase<Derived2>& b);


// /** Sets \c *this to be a quaternion representing a rotation between
//   * the two arbitrary vectors \a a and \a b. In other words, the built
//   * rotation represent a rotation sending the line of direction \a a
//   * to the line of direction \a b, both lines passing through the origin.
//   *
//   * \returns a reference to \c *this.
//   *
//   * Note that the two input vectors do \b not have to be normalized, and
//   * do not need to have the same norm.
//   */
// template<class Derived>
// template<typename Derived1, typename Derived2>
// EIGEN_DEVICE_FUNC inline Derived& QuaternionBase<Derived>::setFromTwoVectors(const MatrixBase<Derived1>& a, const MatrixBase<Derived2>& b)
// {
//   EIGEN_USING_STD_MATH(sqrt)
//   Vector3 v0 = a.normalized();
//   Vector3 v1 = b.normalized();
//   Scalar c = v1.dot(v0);

//   // if dot == -1, vectors are nearly opposites
//   // => accurately compute the rotation axis by computing the
//   //    intersection of the two planes. This is done by solving:
//   //       x^T v0 = 0
//   //       x^T v1 = 0
//   //    under the constraint:
//   //       ||x|| = 1
//   //    which yields a singular value problem
//   if (c < Scalar(-1)+NumTraits<Scalar>::dummy_precision())
//   {
//     c = numext::maxi(c,Scalar(-1));
//     Matrix<Scalar,2,3> m; m << v0.transpose(), v1.transpose();
//     JacobiSVD<Matrix<Scalar,2,3> > svd(m, ComputeFullV);
//     Vector3 axis = svd.matrixV().col(2);

//     Scalar w2 = (Scalar(1)+c)*Scalar(0.5);
//     this->w() = sqrt(w2);
//     this->vec() = axis * sqrt(Scalar(1) - w2);
//     return derived();
//   }
//   Vector3 axis = v0.cross(v1);
//   Scalar s = sqrt((Scalar(1)+c)*Scalar(2));
//   Scalar invs = Scalar(1)/s;
//   this->vec() = axis * invs;
//   this->w() = s * Scalar(0.5);

//   return derived();
// }

// /** \returns a random unit quaternion following a uniform distribution law on SO(3)
//   *
//   * \note The implementation is based on http://planning.cs.uiuc.edu/node198.html
//   */
// template<typename Scalar, int Options>
// EIGEN_DEVICE_FUNC Quaternion<Scalar,Options> Quaternion<Scalar,Options>::UnitRandom()
// {
//   EIGEN_USING_STD_MATH(sqrt)
//   EIGEN_USING_STD_MATH(sin)
//   EIGEN_USING_STD_MATH(cos)
//   const Scalar u1 = internal::random<Scalar>(0, 1),
//                u2 = internal::random<Scalar>(0, 2*EIGEN_PI),
//                u3 = internal::random<Scalar>(0, 2*EIGEN_PI);
//   const Scalar a = sqrt(1 - u1),
//                b = sqrt(u1);
//   return Quaternion (a * sin(u2), a * cos(u2), b * sin(u3), b * cos(u3));
// }


// /** Returns a quaternion representing a rotation between
//   * the two arbitrary vectors \a a and \a b. In other words, the built
//   * rotation represent a rotation sending the line of direction \a a
//   * to the line of direction \a b, both lines passing through the origin.
//   *
//   * \returns resulting quaternion
//   *
//   * Note that the two input vectors do \b not have to be normalized, and
//   * do not need to have the same norm.
//   */
// template<typename Scalar, int Options>
// template<typename Derived1, typename Derived2>
// EIGEN_DEVICE_FUNC Quaternion<Scalar,Options> Quaternion<Scalar,Options>::FromTwoVectors(const MatrixBase<Derived1>& a, const MatrixBase<Derived2>& b)
// {
//     Quaternion quat;
//     quat.setFromTwoVectors(a, b);
//     return quat;
// }
