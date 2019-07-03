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

#include "robin-nn.cpp"

#endif /* ROBIN_NN_H_ */
