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
#include "robin-nn.h"

#include "hwd.h"

int main(int argc, char **argv)
{
    RobinBird nn("hwd-digits-model.rb");
    HandwrittenDigit foo(std::move(nn));
    
    std::vector<double> image = readImage("media/number.png");
    
    foo.runInferenceSingleImage(image);

    return 0;
}
