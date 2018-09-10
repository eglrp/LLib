#ifndef _LL_IMAGE_H_
#define _LL_IMAGE_H_

namespace LLib
{

namespace DataStructure
{

    // Row-major
    template <typename T>
    class Image
    {
        public:
            Image(int width_, int height_, int channel_): width(width_), height(height_), channel(channel_) 
                { data = new T[width*height*channel]; }

            ~Image() { delete []data; }

            T *get_data() { return data; }
            T *get_data() const { return data; }

            int get_width() const { return width; }
            int get_height() const { return width; }
            int get_channel() const { return channel; }

        private:
            T *data;

            int width;
            int height;
            int channel;
    };  // class Image

}   // DataStructure

}   // namespace LLib

#endif  // _LL_IMAGE_H_