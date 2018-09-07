#ifndef _LL_CONVERT_H_
#define _LL_CONVERT_H_

#include "geometry_header.h"

// The convert between euler, axis-angle, quaternion and matrix.

namespace LLib
{
    // ***************************************************************************
    // *****************************  Euler Convert  *****************************
    // ***************************************************************************

    // euler to axis-angle
    // http://www.euclideanspace.com/maths/geometry/rotations/conversions/eulerToAngle/index.htm
    // @para[in]  e:      euler angle in radians
    // @para[out] result: normalized axis-angle
    template <typename T>
    AxisAngle<T> euler2aa(const EulerAngle<T> &e){
        AxisAngle<T> result;

        double halfyaw = e.yaw()/2;
        double halfpitch = e.pitch()/2;
        double halfroll = e.roll()/2;

        double c1 = cos(halfyaw);
        double c2 = cos(halfpitch);
        double c3 = cos(halfroll);
        double s1 = sin(halfyaw);
        double s2 = sin(halfpitch);
        double s3 = sin(halfroll);

        vec3d axis;
        axis.x = s1*s2*c3 + c1*c2*s3;
        axis.y = s1*c2*c3 + c1*s2*s3;
        axis.z = c1*s2*c3 - s1*c2*s3;

        double angle = 2*acos(c1*c2*c3 - s1*s2*s3);

        double length = axis.length();

        // when all euler angles are zero angle =0 so we can set axis to anything to avoid divide by zero
        if (length < EPS) { 
            axis.x = 1;
            axis.y = axis.z = 0;
        } else {
            axis.normalize();
        }

        result.setAngle(static_cast<T>(angle));
        result.setAxis(axis.toType<T>());

        return result;
    }

    // euler to quaternion
    // http://www.euclideanspace.com/maths/geometry/rotations/conversions/eulerToQuaternion/index.htm
    template <typename T>
    Quaternion<T> euler2quaternion(const EulerAngle<T> &e){
        Quaternion<T> result;

        // Method 1
        double halfyaw = e.yaw()/2;
        double halfpitch = e.pitch()/2;
        double halfroll = e.roll()/2;

        double c1 = cos(halfyaw);
        double c2 = cos(halfpitch);
        double c3 = cos(halfroll);
        double s1 = sin(halfyaw);
        double s2 = sin(halfpitch);
        double s3 = sin(halfroll);

        vec3d Imag;
        Imag.x = s1*s2*c3 + c1*c2*s3;
        Imag.y = s1*c2*c3 + c1*s2*s3;
        Imag.z = c1*s2*c3 - s1*c2*s3;

        double Real = c1*c2*c3 - s1*s2*s3;

        result.setImag(Imag.toType<T>());
        result.setReal(static_cast<T>(Real));

        // Method 2
        // worse than Method 1
        // T C1 = cos(yaw);
        // T C2 = cos(pitch);
        // T C3 = cos(roll);
        // T S1 = sin(yaw);
        // T S2 = sin(pitch);
        // T S3 = sin(roll);

        // result.w = sqrt(1.0 + C1*C2 + C1*C3 - S1*S2*S3 + C2*C3)/2;
        // result.x = (C2*S3 + C1*S3 + S1*S2*C3)/(4.0*result.w);
        // result.y = (S1*C2 + S1*C3 + C1*S2*S3)/(4.0*result.w);
        // result.z = (-S1*S3 + C1*S2*C3 + S2)/(4.0*result.w);

        return result;
    }
    
    // euler to matrix
    // http://www.euclideanspace.com/maths/geometry/rotations/conversions/eulerToMatrix/index.htm
    template <typename T>
    RotationMatrix<T> euler2rotationmatrix(const EulerAngle<T> &e){
        RotationMatrix<T> result;

        mat33d R;
        double sy = sin(e.yaw());
        double cy = cos(e.yaw());
        double sp = sin(e.pitch());
        double cp = cos(e.pitch());
        double sr = sin(e.roll());
        double cr = cos(e.roll());

        R(0,0) = cy*cp;
        R(0,1) = -cy*sp*cr + sy*sr;
        R(0,2) = cy*sp*sr + sy*cr;
        R(1,0) = sp;
        R(1,1) = cp*cr;
        R(1,2) = cp*cr;
        R(1,2) = -cp*sr;
        R(2,0) = -sy*cp;
        R(2,1) = sy*sp*cr + cy*sr;
        R(2,2) = -sy*sp*sr + cy*cr;

        result.setR(R.toType<T>());
        
        return result;
    }

    // ***************************************************************************
    // *************************  Axis-Angle Convert  ****************************
    // ***************************************************************************

    // axis-angle to euler
    // http://www.euclideanspace.com/maths/geometry/rotations/conversions/angleToEuler/index.htm
    // para[in]  aa :    normalized axis-angle
    // para[out] result: euler angle
    template <typename T>
    EulerAngle<T> aa2euler(const AxisAngle<T> &aa){
        EulerAngle<T> result;

        double s = sin(aa.angle());
        double c = cos(aa.angle());
        double t = 1 - c;

        vec3d axis = aa.getNormalizeAxis();

        vec3d euler;

        if ((axis.x*axis.y*t + axis.z*s) > 0.998) { // north pole singularity detected
            euler.yaw = 2*atan2(axis.x*sin(aa.angle()/2),cos(aa.angle()/2));
            euler.pitch = PI/2;
            euler.roll = 0;
            result.set(euler.toType<T>());
            return result;
        }
        if ((axis.x*axis.y*t + axis.z*s) < -0.998) { // south pole singularity detected
            euler.yaw = -2*atan2(axis.x*sin(aa.angle()/2),cos(aa.angle()/2));
            euler.pitch= -PI/2;
            euler.roll = 0;
            result.set(euler.toType<T>());
            return result;
        }
        euler.yaw = atan2(axis.y*s - axis.x*axis.z*t, 1 - (axis.y*axis.y+ axis.z*axis.z)*t);
        euler.pitch = asin(axis.x*axis.y*t + axis.z*s) ;
        euler.roll = atan2(axis.x*s - axis.y*axis.z*t, 1 - (axis.x*axis.x + axis.z*axis.z)*t);

        result.set(euler.toType<T>());

        return result;
    }

    // axis-angle to quaternion
    // http://www.euclideanspace.com/maths/geometry/rotations/conversions/angleToQuaternion/index.htm
    // para[in]  aa :    normalized axis-angle
    // para[out] result: normalized quaternion
    template <typename T>
    Quaternion<T> aa2quaternion(const AxisAngle<T> &aa){
        Quaternion<T> result;
        AxisAngle<T> naa = aa.getNormalize();
        double halftheta = naa.angle()/2;
        double s = sin(halftheta);

        vec3d Imag;
        Imag.x = static_cast<T>(naa.x()*s);
        Imag.y = static_cast<T>(naa.y()*s);
        Imag.z = static_cast<T>(naa.z()*s);
        
        double Real= static_cast<T>(cos(halftheta));

        result.setImag(Imag.toType<T>());
        result.setReal(static_cast<T>(Real));
        return result;
    }

    // axis-angle to matrix
    // http://www.euclideanspace.com/maths/geometry/rotations/conversions/angleToMatrix/index.htm
    // para[in]  aa :    normalized axis-angle
    // para[out] result: roatation matrix
    template <typename T>
    RotationMatrix<T> aa2rotationmatrix(const AxisAngle<T> &aa){
        RotationMatrix<T> result;

        AxisAngle<T> naa = aa.getNormalize();
        double c =cos(naa.angle());
        double s = sin(naa.angle());
        double t = 1 - c;

        double xx = naa.x()*naa.x();
        double yy = naa.y()*naa.y();
        double zz = naa.z()*naa.z();
        double xy = naa.x()*naa.y();
        double xz = naa.x()*naa.z();
        double yz = naa.y()*naa.z();

        mat33d R;
        
        R(0,0) = t*xx + c;
        R(0,1) = t*xy - naa.z()*s;
        R(0,1) = t*xz + naa.y()*s;
        R(1,0) = t*xy + naa.z()*s;
        R(1,1) = t*yy + c;
        R(1,2) = t*yz - aa.x()*s;
        R(2,0) = t*xz - aa.y()*s;
        R(2,1) = t*yz + aa.x()*s;
        R(2,2) = t*zz + c;

        result.setR(R);
        
        return result;
    }

    // ***************************************************************************
    // *************************  Quaternion Convert  ****************************
    // ***************************************************************************

    // quaternion to euler
    // http://www.euclideanspace.com/maths/geometry/rotations/conversions/quaternionToEuler/index.htm
    // para[in]  q :    normalized quaternion
    // para[out] result: euler angle
    template <typename T>
    EulerAngle<T> quaternion2euler(const Quaternion<T> &q){
        EulerAngle<T> result;

        Quaternion<double> nq = q.getNormalize();

        vec3d euler;

        double test = nq.x()*nq.y() + nq.z()*nq.w();
        if (test > 0.499) { // singularity at north pole
            euler.yaw = 2*atan2(nq.x(),nq.w());
            euler.pitch = PI/2;
            euler.roll = 0;
            result.set(euler.toType<T>());
            return result;
        }

        if (test < -0.499) { // singularity at south pole
            euler.yaw = -2*atan2(nq.x(),nq.w());
            euler.pitch = -PI/2;
            euler.roll = 0;
            result.set(euler.toType<T>());
            return result;
        }

        double xx = nq.x()*nq.x();
        double yy = nq.y()*nq.y();
        double zz = nq.z()*nq.z();

        euler.yaw = atan2(2*nq.y()*nq.w() - 2*nq.x()*nq.z(), 1 - 2*yy - 2*zz);
        euler.pitch = asin(2*test);
        euler.roll = atan2(2*nq.x()*nq.w() - 2*nq.y()*nq.z(), 1 - 2*xx - 2*zz);

        result.set(euler.toType<T>());

        return result;
    }

    // // quaternion to axis-angle
    // // http://www.euclideanspace.com/maths/geometry/rotations/conversions/quaternionToAngle/index.htm
    template <typename T>
    AxisAngle<T> quaternion2aa(const Quaternion<T> &q){
        AxisAngle<T> result;

        // if w>1 acos and sqrt will produce errors, this cant happen if quaternion is normalised
        Quaternion<double> nq = q.getNormalize();

        double angle = 2 * acos(nq.w());

        vec3d axis;
        double s = sqrt(1 - nq.w()*nq.w()); // assuming quaternion normalised then w is less than 1, so term always positive.
        if (s < EPS) { // test to avoid divide by zero, s is always positive due to sqrt
          // if s close to zero then direction of axis not important
          axis.x = nq.x(); // if it is important that axis is normalised then replace with x=1; y=z=0;
          axis.y = nq.y();
          axis.z = nq.z();
        } else {
          axis.x = nq.x() / s; // normalise axis
          axis.y = nq.y() / s;
          axis.z = nq.z() / s;
        }

        result.setAngle(angle);
        result.setAxis(axis);

        return result;
    }

    // quaternion to matrix
    // http://www.euclideanspace.com/maths/geometry/rotations/conversions/quaternionToMatrix/index.htm
    // para[in]  q :    normalized quaternion
    // para[out] result: roatation matrix
    template <typename T>
    RotationMatrix<T> quaternion2rotationmatrix(const Quaternion<T> &q){
        RotationMatrix<T> result;

        Quaternion<double> nq = q.getNormalize();

        double xx = nq.x()*nq.x();
        double yy = nq.y()*nq.y();
        double zz = nq.z()*nq.z();
        double xy = nq.x()*nq.y();
        double xz = nq.x()*nq.z();
        double xw = nq.z()*nq.w();
        double yz = nq.y()*nq.z();
        double yw = nq.y()*nq.w();
        double zw = nq.z()*nq.w();

        mat33d R;

        R(0,0) = 1 - 2*(yy + zz);
        R(0,1) =     2*(xy - zw);
        R(0,2) =     2*(xz + yw);
        R(1,0) =     2*(xy + zw);
        R(1,1) = 1 - 2*(xx + zz);
        R(1,2) =     2*(yz - xw);
        R(2,0) =     2*(xz - yw);
        R(2,1) =     2*(yz + xw);
        R(2,2) = 1 - 2*(xx + yy);

        result.setR(R);

        return result;
    }


    // ***************************************************************************
    // ****************************  Matrix Convert  *****************************
    // ***************************************************************************

    // matrix to euler
    // http://www.euclideanspace.com/maths/geometry/rotations/conversions/matrixToEuler/index.htm
    template <typename T>
    EulerAngle<T> rotationmatrix2euler(const RotationMatrix<T> &m){
        EulerAngle<T> result;

        mat33<T> rm = m.R();

        vec3d euler;
        if (rm(1,0) > 0.998) { // singularity at north pole
            euler.yaw = atan2(rm(0,2), rm(2,2));
            euler.pitch = PI/2;
            euler.roll = 0;
            result.set(euler.toType<T>());
            return result;
        }
        if (rm(1,0) < -0.998) { // singularity at south pole
            euler.yaw = atan2(rm(0,2), rm(2,2));
            euler.pitch = -PI/2;
            euler.roll = 0;
            result.set(euler.toType<T>());
            return result;
        }
        euler.yaw = atan2(-rm(2,0),rm(0,0));
        euler.roll = atan2(-rm(1,2),rm(1,1));
        euler.pitch = asin(rm(1,0));

        result.set(euler.toType<T>());
        return result;
    }

    // // matrix to axis-angle
    // // http://www.euclideanspace.com/maths/geometry/rotations/conversions/matrixToAngle/index.htm
    // // TODO : rewrite
    // template <typename T>
    // AxisAngle<T> matrix2aa(const mat33<T> &m){
    //     AxisAngle<T> result;

    //     double angle,x,y,z; // variables for result
    //     double epsilon = 0.01; // margin to allow for rounding errors
    //     double epsilon2 = 0.1; // margin to distinguish between 0 and 180 degrees
    //     // optional check that input is pure rotation, 'isRotationMatrix' is defined at:
    //     // https://www.euclideanspace.com/maths/algebra/matrix/orthogonal/rotation/
    //     assert isRotationMatrix(m) : "not valid rotation matrix" ;// for debugging
    //     if ((Math.abs(m[0][1]-m[1][0])< epsilon)
    //       && (Math.abs(m[0][2]-m[2][0])< epsilon)
    //       && (Math.abs(m[1][2]-m[2][1])< epsilon)) {
    //         // singularity found
    //         // first check for identity matrix which must have +1 for all terms
    //         //  in leading diagonaland zero in other terms
    //         if ((Math.abs(m[0][1]+m[1][0]) < epsilon2)
    //           && (Math.abs(m[0][2]+m[2][0]) < epsilon2)
    //           && (Math.abs(m[1][2]+m[2][1]) < epsilon2)
    //           && (Math.abs(m[0][0]+m[1][1]+m[2][2]-3) < epsilon2)) {
    //             // this singularity is identity matrix so angle = 0
    //             return new axisAngle(0,1,0,0); // zero angle, arbitrary axis
    //         }
    //         // otherwise this singularity is angle = 180
    //         angle = Math.PI;
    //         double xx = (m[0][0]+1)/2;
    //         double yy = (m[1][1]+1)/2;
    //         double zz = (m[2][2]+1)/2;
    //         double xy = (m[0][1]+m[1][0])/4;
    //         double xz = (m[0][2]+m[2][0])/4;
    //         double yz = (m[1][2]+m[2][1])/4;
    //         if ((xx > yy) && (xx > zz)) { // m[0][0] is the largest diagonal term
    //             if (xx< epsilon) {
    //                 x = 0;
    //                 y = 0.7071;
    //                 z = 0.7071;
    //             } else {
    //                 x = Math.sqrt(xx);
    //                 y = xy/x;
    //                 z = xz/x;
    //             }
    //         } else if (yy > zz) { // m[1][1] is the largest diagonal term
    //             if (yy< epsilon) {
    //                 x = 0.7071;
    //                 y = 0;
    //                 z = 0.7071;
    //             } else {
    //                 y = Math.sqrt(yy);
    //                 x = xy/y;
    //                 z = yz/y;
    //             }	
    //         } else { // m[2][2] is the largest diagonal term so base result on this
    //             if (zz< epsilon) {
    //                 x = 0.7071;
    //                 y = 0.7071;
    //                 z = 0;
    //             } else {
    //                 z = Math.sqrt(zz);
    //                 x = xz/z;
    //                 y = yz/z;
    //             }
    //         }
    //         return new axisAngle(angle,x,y,z); // return 180 deg rotation
    //     }
    //     // as we have reached here there are no singularities so we can handle normally
    //     double s = Math.sqrt((m[2][1] - m[1][2])*(m[2][1] - m[1][2])
    //         +(m[0][2] - m[2][0])*(m[0][2] - m[2][0])
    //         +(m[1][0] - m[0][1])*(m[1][0] - m[0][1])); // used to normalise
    //     if (Math.abs(s) < 0.001) s=1; 
    //         // prevent divide by zero, should not happen if matrix is orthogonal and should be
    //         // caught by singularity test above, but I've left it in just in case
    //     angle = Math.acos(( m[0][0] + m[1][1] + m[2][2] - 1)/2);
    //     x = (m[2][1] - m[1][2])/s;
    //     y = (m[0][2] - m[2][0])/s;
    //     z = (m[1][0] - m[0][1])/s;

    //     return result;
    // }

    // matrix to quaternion
    // http://www.euclideanspace.com/maths/geometry/rotations/conversions/matrixToQuaternion/index.htm
    // TODO : add
    template <typename T>
    Quaternion<T> matrix2quaternion(const mat33<T> &m){
        Quaternion<T> result;

        return result;
    }


} // namespace LLib

#endif // _LL_CONVERT_H_