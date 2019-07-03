/* Copyright (c) 2019 NXP Semiconductors
 *   
 * SPDX-License-Identifier: GPL3
 * Diego Dorta <diego.dorta@nxp.com>
 *
 * This program is free software: you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free Software
 * Foundation, either version 3 of the License, or 2 any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program. If not, see <https://www.gnu.org/licenses/>.
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
