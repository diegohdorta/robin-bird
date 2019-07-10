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
#include <iostream>
#include <time.h>

#include "robin/math.h"

static double random(double x);

int main(void)
{
    srand(time(NULL));
    Matrix <double> A(3, 3), B(3, 3);

    A = A.applyFunction(random);
    B = B.applyFunction(random);

    std::cout << A + B << std::endl;
    std::cout << A.dot(B) << std::endl;
    std::cout << A(0,0) << std::endl;
    
    return 0;
}

static double random(double x)
{
    return (double)(rand() % 10000 + 1)/10000;
}
