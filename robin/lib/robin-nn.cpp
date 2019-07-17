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
#include "robin-nn.h"

/* Constructor based on Model */

RobinBird::RobinBird(const char *fileModelPath)
{
    loadRobinBirdModel(fileModelPath);
}

void RobinBird::loadRobinBirdModel(const char *fileModelPath)
{
    int i;
    int hHeight;
    int height;
    int wWidth;
    int width;
    double value;

    std::ifstream in(fileModelPath);
    std::vector<Matrix<double>> model;

    if (in) {
        in >> hiddenLayersCount;
        in >> learningRate;

        H = std::vector<Matrix<double>>
                        (hiddenLayersCount + 2);
        W = std::vector<Matrix<double>>
                        (hiddenLayersCount + 1);
        B = std::vector<Matrix<double>>
                        (hiddenLayersCount + 1);
        dEdW = std::vector<Matrix<double>>
                        (hiddenLayersCount + 1);
        dEdB = std::vector<Matrix<double>>
                        (hiddenLayersCount + 1);

        for(i = 0; i < 2 * hiddenLayersCount + 2; i++) {
            in >> height;
            in >> width;
            Matrix<double> m(height, width);
            for (hHeight = 0; hHeight < height; hHeight++) {
                for (wWidth = 0; wWidth < width; wWidth++) {
                    in >> value;
                    m.put(hHeight, wWidth, value);
                }
            }
            model.push_back(m);
        }
    }
    in.close();

    /* Assigning values*/
    for (i = 0; i < hiddenLayersCount + 1; i++) {
        W[i] = model[i];
    }
    for (i = hiddenLayersCount + 1; i < model.size(); i++) {
        B[i - hiddenLayersCount - 1] = model[i];
    }
}

/* Constructor Defining Neural Network Settings */

RobinBird::RobinBird(std::vector<int> neurons,
                     double learningRate)
{
    int i;
    srand (time(NULL));

    this->learningRate = learningRate;
    this->hiddenLayersCount = neurons.size() - 2;

    H = std::vector<Matrix<double>> (hiddenLayersCount + 2);
    W = std::vector<Matrix<double>> (hiddenLayersCount + 1);
    B = std::vector<Matrix<double>> (hiddenLayersCount + 1);
    dEdW = std::vector<Matrix<double>> (hiddenLayersCount + 1);
    dEdB = std::vector<Matrix<double>> (hiddenLayersCount + 1);

    for (i = 0; i < neurons.size() - 1; i++) {
        W[i] = Matrix<double>(neurons[i], neurons[i + 1]);
        B[i] = Matrix<double>(1, neurons[i + 1]);
        W[i] = W[i].applyFunction(random);
        B[i] = B[i].applyFunction(random);
    }
}


Matrix<double> RobinBird::computeOutput(std::vector<double> input)
{
    int i;
    H[0] = Matrix<double> ({input});

    for (i = 1; i < hiddenLayersCount + 2; i++) {
        H[i] = H[i - 1].
               dot(W[i - 1]).
               add(B[i - 1]).
               applyFunction(sigmoid);
    }
    return H[hiddenLayersCount + 1];
}

void RobinBird::learn(std::vector<double> expectedOutput)
{
    int i;
    /* error equals to:
     * E = 1/2  (expected - computed)^2
     * 
     * Then, calculate the partial derivative of E
     * with respect to W and B.
     */
    Y = Matrix<double>({expectedOutput});

    /* Compute gradients */
    dEdB[hiddenLayersCount] = H[hiddenLayersCount + 1].
                              subtract(Y).
                              multiply(H[hiddenLayersCount].
                              dot(W[hiddenLayersCount]).
                              add(B[hiddenLayersCount]).
                              applyFunction(sigmoidPrime));
                              
    for (i = hiddenLayersCount - 1; i >= 0; i--) {
        dEdB[i] = dEdB[i + 1].
                  dot(W[i + 1].
                  transpose()).
                  multiply(H[i].
                  dot(W[i]).
                  add(B[i]).
                  applyFunction(sigmoidPrime));
    }
    for (i = 0; i < hiddenLayersCount + 1; i++) {
        dEdW[i] = H[i].
                  transpose().
                  dot(dEdB[i]);
    }
    /* Update the weights */
    for (i = 0; i < hiddenLayersCount + 1; i++) {
        W[i] = W[i].
               subtract(dEdW[i].
                        multiply(learningRate));
        B[i] = B[i].
               subtract(dEdB[i].
                        multiply(learningRate));
    }
}

void RobinBird::writetoFile(Matrix<double> &m, std::ofstream &file)
{
    int i;
    int j;
    int height = m.getHeight();
    int width = m.getWidth();

    file << height << std::endl;
    file << width << std::endl;
    for (i = 0; i < height; i++) {
        for (j = 0; j < width; j++) {
            file <<
            m.get(i, j) <<
            (j != width - 1 ? " " : "");
        }
        file << std::endl;
    }
}

void RobinBird::saveRobinBirdModel(const char *fileModelPath)
{
    time_t rawtime;
    struct tm *timeinfo;
    char buffer[80];

    time(&rawtime);
    timeinfo = localtime(&rawtime);

    strftime(buffer, 80, "%Y_%m_%d_%H_%M_%S_hwd-model.rb", timeinfo);
    std::ofstream out(buffer);
    
    out << hiddenLayersCount << std::endl;
    out << learningRate << std::endl;
    
    for (Matrix<double> m : W) {
        writetoFile(m, out);
    }
    for (Matrix<double> m : B) {
        writetoFile(m, out);
    }
    out.close();
}

double RobinBird::random(double x)
{
    return (double)(rand() % 10000 + 1) / 10000 - 0.5;
}

double RobinBird::sigmoid(double x)
{
    return 1 / (1 + exp(-x));
}

double RobinBird::sigmoidPrime(double x)
{
    return exp(-x) / (pow(1 + exp(-x), 2));
}
