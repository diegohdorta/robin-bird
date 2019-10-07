/* Copyright 2019 NXP Semiconductors
 *   
 * SPDX-License-Identifier: MIT
 * Diego Dorta <diego.dorta@nxp.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:

 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.

 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */
#include "robin-image.h"

std::vector<double> readImage(const char *filename)
{
    int height = 32;
    int width = 32;
    int r = 0;
    int g = 0;
    int b = 0;
    int p = 0;
    int i;
    int j;

    png::image<png::rgb_pixel> image(filename);
    assert(image.get_width() == width && image.get_height() == height);

    std::vector<double> v(height * width);
    for (i = 0; i < height; i++) {
        for (j = 0; j < width; j++) {
            r = (int) image[i][j].red;
            g = (int) image[i][j].green;
            b = (int) image[i][j].blue;
            if (r == 255 && g == 255 && b == 255)
                v[p++] = 0.0;
            else
                v[p++] = 1.0;
        }
    }
    return v;
}
