/* Copyright (c) 2019 NXP Semiconductors
 * Diego Dorta <diego.dorta@nxp.com>
 * SPDX-License-Identifier: GLP3
 */
#ifndef HWD_H
#define HWD_H

#define DATA_SET_TRAINING           "hwd-digits-train.rb"
#define DATA_SET_TRAINING_SIZE      936
#define DATA_SET_TESTING            "hwd-digits-test.rb"
#define DATA_SET_TESTING_SIZE       10
#define MNIST_MODEL_TRAINED_NAME    "hwd-digits-model.rb"

class HandwrittenDigit
{
    public:
        RobinBird net;
         
        const char *trainingDatasetFileName;
        const char *testingDatasetFileName;
        const char *mnistModelTrainedName = MNIST_MODEL_TRAINED_NAME;
        int iterationsTraining;
        int trainingDatasetSize;
        int testingDatasetSize;

        std::vector<std::vector<double>> inputVectorTraining;
        std::vector<std::vector<double>> inputVectorTesting;

        std::vector<std::vector<double>> outputVectorTraining;
        std::vector<std::vector<double>> outputVectorTesting;
   
        HandwrittenDigit(RobinBird &&n) : net(n)
        {
            this->iterationsTraining = 30;
        }
   
        void setDatasetFileForTraining(const char* datasetFileName,
                                       int datasetSize)
        {
            this->trainingDatasetFileName = datasetFileName;
            this->trainingDatasetSize = datasetSize;
        }
       
        void setDatasetFileForTesting(const char* datasetFileName,
                                      int datasetSize)
        {
            this->testingDatasetFileName = datasetFileName;
            this->testingDatasetSize = datasetSize;
        } 
        
        
        void runInferenceSingleImage(std::vector<double> img);
        Matrix<double> runInferenceSingleImageToVector(std::vector<double> img);
        void trainingDataset(void);
        void testingDataset(void);  
        void loadDatasetForTraining(void);
        void loadDatasetForTesting(void);       
        void saveModel(void);
};

static double step(double x)
{
    if (x > 0.9) {
        return 1.0;
    }
    if (x < 0.1) {
        return 0.0;
    }
    return x;
}

//#include "hwd.cpp"

#endif /* HWD_H defined */
