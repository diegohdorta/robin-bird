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
