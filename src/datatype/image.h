#ifndef _LL_IMAGE_H_
#define _LL_IMAGE_H_

#include "vectype.h"

namespace LLib
{

    // Row-major
    template <typename T>
    class image
    {
        public:
            image(int h_, int w_): h(h_), w(w_) { data = new T[h*w]; }
            ~image() { delete []data; }

            T *getData() { return data; }
            const T *getData() const { return data; }

            int getH() const { return h; }
            int getW() const { return w; }
            int getRow() const { return h; }
            int getCol() const { return w; }

            T &operator[](int index) { return data[index]; }
            const T &operator[](int index) const { return data[index]; }

            T &operator()(int h_, int w_) { return data[h_*w + w_]; }
            const T &operator()(int h_, int w_) const { return data[h_*w + w_]; }

        private:
            T *data;

            int h;
            int w;
    };  // class image

    using image1f = image<float>;
    using image1d = image<double>;
    using image3f = image<vec3f>;
    using image3d = image<vec3d>;


}   // namespace LLib

#endif  // _LL_IMAGE_H_