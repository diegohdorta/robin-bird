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
#include <chrono>
#include <ctime>
#include <fstream>
#include <iostream>
#include <time.h>

#include "robin-nn.h"
#include "hwd.h"

void HandwrittenDigit::runInferenceSingleImage(std::vector<double> img)
{
    std::cout << this->net.computeOutput(img).applyFunction(step);
}

Matrix<double> HandwrittenDigit::runInferenceSingleImageToVector(std::vector<double> img)
{
    return this->net.computeOutput(img).applyFunction(step);
}

void HandwrittenDigit::trainingDataset(void)
{
    int i = 0;
    int j = 0;
    
    auto start = std::chrono::system_clock::now();
    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start;
    std::time_t end_time = std::chrono::system_clock::to_time_t(end);
    std::cout << "Start training at " << std::ctime(&end_time) << std::endl;
    
    start = std::chrono::system_clock::now();    
    for (i = 0; i < this->iterationsTraining; i++) {
        for (j = 0; j < this->inputVectorTraining.size(); j++) {
            this->net.computeOutput(this->inputVectorTraining[j]);
            this->net.learn(this->outputVectorTraining[j]);
        }
        std::cout << '\r'
                  << "Training # "
                  << i + 1
                  << " - "
                  << this->iterationsTraining
                  << std::flush;     
    }
    end = std::chrono::system_clock::now();    
    elapsed_seconds = end - start;
    end_time = std::chrono::system_clock::to_time_t(end);
    std::cout << "\n\nEnded training at "
              << std::ctime(&end_time)
              << "Training time: " << elapsed_seconds.count()
              << "s\n" << std::endl;
}

void HandwrittenDigit::testingDataset(void)
{
    int i = 0;
    int j = 0;
    
    auto start = std::chrono::system_clock::now();    
    std::cout << "       Expected     <>     Actual\n" << std::endl;    
    for (i = 0; i < this->inputVectorTesting.size(); i++) {   
        for (j = 0; j < this->testingDatasetSize; j++) {   
            std::cout << this->outputVectorTesting[i][j] << " ";
        }
        std::cout << "<> " <<
        this->net.computeOutput(this->inputVectorTesting[i]).applyFunction(step)
        << std::endl;
    }
    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start;
    std::cout << "Inference time: " << elapsed_seconds.count()
              << "s" << std::endl;
}

void HandwrittenDigit::loadDatasetForTraining(void)
{
    int size = this->trainingDatasetSize;
    this->inputVectorTraining.resize(size);
    this->outputVectorTraining.resize(size);
    int i = 0;
    int height = 0;
    int width = 0;
    int n;
    std::ifstream f(this->trainingDatasetFileName);
    if (f) {
        std::string line;
        for (i = 0; i < size; i++) {
            for (height = 0; height < 32; height++) {
                getline(f, line);
                for (width = 0; width < 32; width++) {
                    this->inputVectorTraining[i].
                        push_back(atoi(line.substr(width,1).c_str()));
                }
            }
            getline(f, line);
            this->outputVectorTraining[i].resize(10);
            n = atoi(line.substr(0,1).c_str());
            this->outputVectorTraining[i][n] = 1;
        }
    }
    f.close();
}
 
void HandwrittenDigit::loadDatasetForTesting(void)
{
    int size = this->testingDatasetSize;
    this->inputVectorTesting.resize(size);
    this->outputVectorTesting.resize(size);
    int i = 0;
    int height = 0;
    int width = 0;
    int n;
    std::ifstream f(this->testingDatasetFileName);
    if (f) {
        std::string line;
        for (i = 0; i < size; i++) {
            for (height = 0; height < 32; height++) {
                getline(f, line);
                for (width = 0; width < 32; width++) {
                    this->inputVectorTesting[i].
                        push_back(atoi(line.substr(width,1).c_str()));
                }
            }
            getline(f, line);
            this->outputVectorTesting[i].resize(10);
            n = atoi(line.substr(0,1).c_str());
            this->outputVectorTesting[i][n] = 1;
        }
    }
    f.close();
}
 
void HandwrittenDigit::saveModel(void)
{
    this->net.saveRobinBirdModel(MNIST_MODEL_TRAINED_NAME);
}
