#ifndef _LL_STBIMAGE_H_
#define _LL_STBIMAGE_H_

#define STB_IMAGE_IMPLEMENTATION
#include "helper/stb_image.h"

#define STB_IMAGE_RESIZE_IMPLEMENTATION
#include "helper/stb_image_resize.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "helper/stb_image_write.h"

namespace LLib
{
    class stbImage
    {
        public:
            inline static unsigned char *image_load(char const *filename, int *w, int *h, int *channels_in_file, int desired_channels = 0)
                { return stbi_load(filename, w, h, channels_in_file, desired_channels); }

            inline static int write_png(char const *filename, int w, int h, int comp, const void *data, int stride_in_bytes)
                { return stbi_write_png(filename, w, h, comp, data, stride_in_bytes); }
            inline static int write_bmp(char const *filename, int w, int h, int comp, const void *data)
                { return stbi_write_bmp(filename, w, h, comp, data); }
            inline static int write_tga(char const *filename, int w, int h, int comp, const void *data) 
                { return stbi_write_tga(filename, w, h, comp, data); }
            inline static int write_jpg(char const *filename, int w, int h, int comp, const void *data, int quality) 
                { return stbi_write_jpg(filename, w, h, comp, data, quality); }
            inline static int write_hdr(char const *filename, int w, int h, int comp, const float *data)
                { return stbi_write_hdr(filename, w, h, comp, data); }

            inline static void flip_vertically_on_write(int flag)
                { stbi_flip_vertically_on_write(flag); }


            inline static int resize_uint8(const unsigned char *input_pixels , int input_w , int input_h , int input_stride_in_bytes,
                             unsigned char *output_pixels, int output_w, int output_h, int output_stride_in_bytes,
                             int num_channels)
                {
                    return stbir_resize_uint8(input_pixels , input_w ,input_h ,input_stride_in_bytes,
                                              output_pixels, output_w, output_h, output_stride_in_bytes,
                                              num_channels);
                }

            inline static int resize_float(const float *input_pixels , int input_w , int input_h , int input_stride_in_bytes,
                             float *output_pixels, int output_w, int output_h, int output_stride_in_bytes,
                             int num_channels)
                {
                    return stbir_resize_float(input_pixels , input_w , input_h , input_stride_in_bytes,
                                              output_pixels, output_w, output_h, output_stride_in_bytes,
                                              num_channels);
                }

            inline static int resize_uint8_srgb(const unsigned char *input_pixels , int input_w , int input_h , int input_stride_in_bytes,
                                   unsigned char *output_pixels, int output_w, int output_h, int output_stride_in_bytes,
                                   int num_channels, int alpha_channel, int flags)
                {
                    return stbir_resize_uint8_srgb(input_pixels , input_w , input_h , input_stride_in_bytes,
                                                   output_pixels, output_w, output_h, output_stride_in_bytes,
                                                   num_channels, alpha_channel, flags);
                }


            inline static int resize_uint8_srgb_edgemode(const unsigned char *input_pixels , int input_w , int input_h , int input_stride_in_bytes,
                                           unsigned char *output_pixels, int output_w, int output_h, int output_stride_in_bytes,
                                           int num_channels, int alpha_channel, int flags,
                                           stbir_edge edge_wrap_mode)
                {
                    return stbir_resize_uint8_srgb_edgemode(input_pixels , input_w , input_h , input_stride_in_bytes,
                                                            output_pixels, output_w, output_h, output_stride_in_bytes,
                                                            num_channels, alpha_channel, flags,
                                                            edge_wrap_mode);
                }
    };
}   // namespace LLib

#endif  // _LL_STBIMAGE_H_