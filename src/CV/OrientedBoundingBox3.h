#ifndef _LL_ORIENTEDBOUNDINGBOX_H_
#define _LL_ORIENTEDBOUNDINGBOX_H_

namespace LLib
{
    template <typename T>
    class OrientedBoundingBox3
    {
    private:
        vec3<T>	_anchor;
        vec3<T>	_axesScaled[3];	//these axes are not normalized; they are scaled according to the extent

    public:

    };  // class OrientedBoundingBox

}  // namespace LLib

#endif // _LL_ORIENTEDBOUNDINGBOX_H_