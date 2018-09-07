#ifndef _LL_GEOMETRY_HEADER_H_
#define _LL_GEOMETRY_HEADER_H_

#include "AxisAngle.h"
#include "EulerAngle.h"
#include "Quaternion.h"
#include "RotationMatrix.h"
#include "TransformMatrix.h"

#include "convert.h"

typedef  LLib::AxisAngle<int>           AxisAngleI;
typedef  LLib::AxisAngle<float>         AxisAngleF;
typedef  LLib::AxisAngle<double>        AxisAngleD;
typedef  LLib::EulerAngle<int>          EulerAngleI;
typedef  LLib::EulerAngle<float>        EulerAngleF;
typedef  LLib::EulerAngle<double>       EulerAngleD;
typedef  LLib::Quaternion<int>          QuaternionI;
typedef  LLib::Quaternion<float>        QuaternionF;
typedef  LLib::Quaternion<double>       QuaternionD;
typedef  LLib::RotationMatrix<int>      RotationMatrixI;
typedef  LLib::RotationMatrix<float>    RotationMatrixF;
typedef  LLib::RotationMatrix<double>   RotationMatrixD;
typedef  LLib::TransformMatrix<int>     TransformMatrixI;
typedef  LLib::TransformMatrix<float>   TransformMatrixF;
typedef  LLib::TransformMatrix<double>  TransformMatrixD;

#endif // _LL_GEOMETRY_HEADER_H_