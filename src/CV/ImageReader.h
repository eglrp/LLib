#ifndef _LL_IMAGEREADER_H_
#define _LL_IMAGEREADER_H_

#include <string>

#include "../../thirdparty/CImg.h"


// https://stackoverflow.com/questions/1005476/how-to-detect-whether-there-is-a-specific-member-variable-in-class
#include <type_traits>

template <typename T, typename = int>
struct HasDim : std::false_type { };

template <typename T>
struct HasDim <T, decltype((void) T::dim, 0)> : std::true_type { };

namespace LLib
{
    class ImageReader
    {
        template <typename T> 
        BaseImage<T> read(std::string img_file){
            cimg_library::CImg<T> cimg(img_file);
            BaseImage<T> baseimg(cimg.width(), cimg.height());

            cimg2baseimg(cimg, baseimg);

            return baseimg;
        }

        template <typename T>
        void cimg2baseimg(const cimg_library::CImg<T> &cimg, BaseImage<T> &baseimg){
            if(cimg.width() != baseimg.width() || cimg.height() != baseimg.height()) baseimg.resize(cimg.width(), cimg.height());

            int width = baseimg.width();
            int height = baseimg.height();
            int depth = 0;
            int channel = HasDim<T>::value ? T::dim : 1;

            #pragma omp for
            for(int i = 0; i < height; i++) for(int j = 0; j < width; j++){
                for(int c = 0; c < channel; c++)
                    baseimg(i, j)[c] = cimg(i, j, depth, c);
            }

        }
    };  // class ImageReader

}  // namespace LLib

#endif // _LL_IMAGEREADER_H_