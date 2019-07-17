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
#include <robin/robin-image.h>
#include <robin/robin-nn.h>
#include <robin/hwd.h>

int main(int argc, char **argv)
{
    if (argc < 3) {
        std::cout << "Use: " << argv[0] << " model image" << std::endl;
        return 1;
    }
    const char *modelName = argv[1];
    const char *imageName = argv[2];
    
    RobinBird nn(modelName);
    HandwrittenDigit foo(std::move(nn));
    
    std::vector<double> image = readImage(imageName);    
    foo.runInferenceSingleImage(image);

    return 0;
}
