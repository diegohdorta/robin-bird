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
#ifndef ROBIN_NN_H_
#define ROBIN_NN_H_

#include <cmath>
#include <fstream>
#include <stdlib.h>
#include <time.h>
#include <vector>

#include "math.h"

class RobinBird
{
    public:
        RobinBird(std::vector<int> neurons, double learningRate);
        RobinBird(const char *filepath);

        Matrix<double> computeOutput(std::vector<double> input);
        void learn(std::vector<double> expectedOutput);

        void saveRobinBirdModel(const char *filepath);
        void loadRobinBirdModel(const char *filepath);

        std::vector<Matrix<double>> W;
        std::vector<Matrix<double>> B;
        
    private:
        std::vector<Matrix<double>> H;
        std::vector<Matrix<double>> dEdW;
        std::vector<Matrix<double>> dEdB;

        Matrix<double> Y;

        int hiddenLayersCount;
        double learningRate;

        static double random(double x);
        static double sigmoid(double x);
        static double sigmoidPrime(double x);

        void writetoFile(Matrix<double> &m, std::ofstream &file);
};

//#include "robin-nn.cpp"

#endif /* ROBIN_NN_H_ */
