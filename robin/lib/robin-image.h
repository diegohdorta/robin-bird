/* Copyright (c) 2019 NXP Semiconductors
 * Diego Dorta <diego.dorta@nxp.com>
 * SPDX-License-Identifier: GLP3
 */
#ifndef IMAGE_H
#define IMAGE_H

#include <vector>
#include <png++/png.hpp>

std::vector<double> readImage(const char *filename);

#include "robin-image.cpp"

#endif /* IMAGE_H defined */
