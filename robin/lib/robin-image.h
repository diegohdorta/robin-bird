/* Copyright 2019-2020 Diego Dorta, Marco Franchi
 * SPDX-License-Identifier: MIT
 */
#ifndef IMAGE_H
#define IMAGE_H

#include <vector>
#include <png++/png.hpp>

std::vector<double> readImage(const char *filename);

//#include "robin-image.cpp"

#endif /* IMAGE_H defined */
