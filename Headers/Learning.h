#ifndef LEARNING_H
#define LEARNING_H
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <vector>
#include <limits>
#include <sys/time.h>

#define USE_MNIST_LOADER
#define MNIST_DOUBLE
#define EN 600
#define BOY 600


#include "Headers/opencvpaint.h"
#include "Headers/Backpropagation.h"
#include "Headers/readMnist.h"

using namespace cv;
using namespace std;


class Learning{
    Mat *image;
    Mat *karakter;
    unsigned int imgCount;
    mnist_data * data;
    mnist_data * testData;
    Backpropagation * myNeuralNetwork;
    double * expectedValue;
    unsigned int testDataCount;
    unsigned int outputCount;
    unsigned int cnt;

public:
    Learning(int outputCount);
    void translateImage(); // burda 0 dan büyükler karaktere ait çizgilerin belirlenmesi için
    void readData();
    void readTestData();
    void cleanImage(Mat * image);
    void getCharacter();
    void showReadCharacter();
    void startLearning();
    void setInputs();
    void setExpectedOutputs(int x);
    void testNeuralNetwork();

    void resizeImage(Mat * image,int choose);
    double *getExpectedValue() const;
    void setExpectedValue(double *value);
};

#endif // LEARNING_H


