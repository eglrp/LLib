#ifndef _LL_BASEIMAGE_H_
#define _LL_BASEIMAGE_H_

#include "../Utility/common.h"

namespace LLib
{
    template <typename T>
    class BaseImage
    {
    public:
        typedef T ValueType;

    private:
        unsigned int _width;
        unsigned int _height;
        unsigned long int _pixelnum;

        T *data;

        void create(unsigned int width, unsigned int height){
            _width = width;
            _height = height;
            _pixelnum = width*height;
            
            SAFE_FREE(data)
            if(_pixelnum) {
                data = malloc(sizeof(T) * _pixelnum);
                memset(data, 0, sizeof(T) * pixelnum);
            }
        }

    public:

        BaseImage(){
            create(0, 0);
        };

        BaseImage(unsigned int size){
            create(size, size);
        }

        BaseImage(unsigned int width_, unsigned int height_){
            create(width_, height_);
        }

        BaseImage(const BaseImage &other){
            create(other.width(), other.height());
            memcpy(data, other.getData(), sizeof(T) * pixelnum);
        }

        ~BaseImage(){
            create(0, 0);
        }

        unsigned int width() const {
            return _width;
        }

        unsigned int height() const {
            return _height;
        }
        
        unsigned long int pixelnum() const {
            return _pixelnum;
        }

        T *getData() const {
            return data;
        }


        T &operator[](unsigned int i){
            assert(i < pixelnum);
            return data[i];
        }

        const T operator[](unsigned int i) const {
            assert(i < pixelnum);
            return data[i];
        }

        T operator()(unsigned int i, unsigned int j){
            assert(i < _height && j < _width);
            return data[i*_width + j];
        }

        const T operator()(unsigned int i, unsigned int j) const {
            assert(i < _height && j < _width);
            return data[i*_width + j];
        }

        T &at(unsigned int i, unsigned int j){
            assert(i < height && j < width);
            return data[i*_width + j];
        }

        const T at(unsigned int i, unsigned int j) const {
            assert(i < height && j < width);
            return data[i*_width + j];
        }

        BaseImage operator=(const BaseImage &other){
            create(other.width(), other.height());
            memcpy(data, other.getData(), sizeof(T) * pixelnum);
        }

        // clear all data
        void resize(unsigned int width_, unsigned int height_){
            create(width_, height_);
        }

        void fill(T x){
            memset(data, x, sizeof(T) * pixelnum);
        }

    }; // class Base

    typedef BaseImage<float> Image1f;
    typedef BaseImage<vec2f> Image2f;
    typedef BaseImage<vec3f> Image3f;
    typedef BaseImage<vec4f> Image4f;

    typedef BaseImage<int> Image1i;
    typedef BaseImage<vec2i> Image2i;
    typedef BaseImage<vec3i> Image3i;
    typedef BaseImage<vec4i> Image4i;

    typedef BaseImage<unsigned char> Image1uc;
    typedef BaseImage<vec4<unsigned char>> Image2uc;

    typedef BaseImage<bool> Image1b;

} // namespace LLib

#endif // _LL_BASEIMAGE_H_