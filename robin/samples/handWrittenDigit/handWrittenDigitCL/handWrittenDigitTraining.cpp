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
#include <robin-nn.h>
#include <hwd.h>
                         
int main(int argc, char *argv[])
{
    if (argc < 7) {
        std::cout << "Use: " << argv[0]
                  << " train size test size n_hidden_layers learning_rate"
                  << std::endl;
        return 1;
    }
    const char *datasetTrain = argv[1];
    int datasetTrainSize = atoi(argv[2]);
    
    const char *datasetTest = argv[3];
    int datasetTestSize = atoi(argv[4]);
    
    int nHiddenLayers = atoi(argv[5]);
    double learningRateExperimental = atof(argv[6]);
    
    if (datasetTrainSize > 936 || datasetTrainSize < 1) {
        std::cout << "Size out of range <1 - 936>" << std::endl;
        return 1;
    }

    if (datasetTestSize > 10 || datasetTestSize < 1) {
        std::cout << "Size out of range <1 - 10>" << std::endl;
        return 1;
    }

    RobinBird nn({1024, nHiddenLayers , 10}, learningRateExperimental);  
    HandwrittenDigit foo(std::move(nn));
  
    foo.setDatasetFileForTraining(datasetTrain, datasetTrainSize);
    foo.loadDatasetForTraining();
    foo.trainingDataset(); 

    foo.setDatasetFileForTesting(datasetTest, datasetTestSize);
    foo.loadDatasetForTesting();
    foo.testingDataset();

    foo.saveModel();
    return 0;
}
