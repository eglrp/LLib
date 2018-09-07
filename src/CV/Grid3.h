#ifndef _LL_GRID_H_
#define _LL_GRID_H_

namespace LLib
{
    template <typename T>
    class Grid3
    {
    private:
        T *_data;
        union {
            unsigned int _dimX, _dimY, _dimZ;
            vec3<unsigned int> _dim;
        }



    };  // class Grid3

    typedef Grid3<float> Grid3f;
	typedef Grid3<double> Grid3d;
	typedef Grid3<int> Grid3i;
	typedef Grid3<unsigned int> Grid3ui;
	typedef Grid3<unsigned char> Grid3uc;


}  // namespace LLib

#endif  // _LL_GRID_H_