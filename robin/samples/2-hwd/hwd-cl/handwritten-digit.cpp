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
#include "hwd.h"
                         
int main(int argc, char *argv[])
{
    RobinBird nn({1024, 15, 10}, 0.7);  
    HandwrittenDigit foo(std::move(nn));
  
    foo.setDatasetFileForTraining(DATA_SET_TRAINING, DATA_SET_TRAINING_SIZE);
    foo.loadDatasetForTraining();
    foo.trainingDataset();
 
    foo.setDatasetFileForTesting(DATA_SET_TESTING, DATA_SET_TESTING_SIZE);
    foo.loadDatasetForTesting();
    foo.testingDataset();
   
    foo.saveModel();
    return 0;
}
