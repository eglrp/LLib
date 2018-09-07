#ifndef _LL_LINE_H_
#define _LL_LINE_H_

#include <cmath>

// Bresenham's Line Algorithm
void draw_line(int x1, int y1, int const x2, int const y2, unsigned char *img, int width, int val = 255)
{
    int delta_x(x2 - x1);
    // if x1 == x2, then it does not matter what we set here
    signed char const ix((delta_x > 0) - (delta_x < 0));
    delta_x = std::abs(delta_x) << 1;
 
    int delta_y(y2 - y1);
    // if y1 == y2, then it does not matter what we set here
    signed char const iy((delta_y > 0) - (delta_y < 0));
    delta_y = std::abs(delta_y) << 1;
 
    img[x1 + y1*width] = val;
    img[x1 + y1*width + 1] = 0;
    img[x1 + y1*width + 2] = 0;
 
    if (delta_x >= delta_y)
    {
        // error may go below zero
        int error(delta_y - (delta_x >> 1));
 
        while (x1 != x2)
        {
            // reduce error, while taking into account the corner case of error == 0
            if ((error > 0) || (!error && (ix > 0)))
            {
                error -= delta_x;
                y1 += iy;
            }
            // else do nothing
 
            error += delta_y;
            x1 += ix;
 
            img[x1 + y1*width] = val;
            img[x1 + y1*width + 1] = 0;
            img[x1 + y1*width + 2] = 0;
        }
    }
    else
    {
        // error may go below zero
        int error(delta_x - (delta_y >> 1));
 
        while (y1 != y2)
        {
            // reduce error, while taking into account the corner case of error == 0
            if ((error > 0) || (!error && (iy > 0)))
            {
                error -= delta_y;
                x1 += ix;
            }
            // else do nothing
 
            error += delta_x;
            y1 += iy;
 
            img[x1 + y1*width] = val;
            img[x1 + y1*width + 1] = 0;
            img[x1 + y1*width + 2] = 0;
        }
    }
}

#endif  // _LL_LINE_H_