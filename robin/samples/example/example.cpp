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
#include <iostream>
#include <time.h>

#include <robin/robin-nn.h>

static double random(double x);

int main(int argc, char *argv[])
{
    if (argc < 2) {
        std::cout << "Missing matrix size" << std::endl;    
        return 0;
    }
    
    double size = atof(argv[1]);
    srand(time(NULL));
    Matrix <double> A(size, size), B(size, size);

    A = A.applyFunction(random);
    B = B.applyFunction(random);

    std::cout << "Matrix A:\n" << A << std::endl;
    std::cout << "Matrix B:\n" << B << std::endl;

    std::cout << "Matrix A + B:\n" << A + B << std::endl;
    std::cout << "Matrix A * B:\n" << A.dot(B) << std::endl;
    
    std::cout << "Matrix A(1,1): "<< A(0,0) << std::endl;
    std::cout << "Matrix A(" << size << "," << size << "): "
              << A(size - 1, size -1) << std::endl;
    
    return 0;
}

static double random(double x)
{
    return (double)(rand() % 10000 + 1)/10000;
}
