/* Copyright 2019-2020 Diego Dorta, Marco Franchi
 *   
 * SPDX-License-Identifier: MIT
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
#include <robin-image.h>
#include <robin-nn.h>
#include <hwd.h>

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
