#ifndef _LL_MAT_HEADER_H_
#define _LL_MAT_HEADER_H_

#include "../../Utility/utility.h"

#include "mat22.h"
#include "mat33.h"
#include "mat44.h"
#include "matX.h"

using mat22d  = LLib::mat22<double>;
using mat22f  = LLib::mat22<float>;
using mat22i  = LLib::mat22<int>;
using mat22ui = LLib::mat22<uint>;

using mat33d  = LLib::mat33<double>;
using mat33f  = LLib::mat33<float>;
using mat33i  = LLib::mat33<int>;
using mat33ui = LLib::mat33<uint>;

using mat44d  = LLib::mat44<double>;
using mat44f  = LLib::mat44<float>;
using mat44i  = LLib::mat44<int>;
using mat44ui = LLib::mat44<uint>;

#endif // _LL_MAT_HEADER_H_