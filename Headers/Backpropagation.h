#ifndef BACKPROPAGATION_H_
#define BACKPROPAGATION_H_

#include <iostream>
#include <vector>
#include <assert.h>

using namespace std;

#include "Headers/Pattern.h"
#include "Headers/Layer.h"

class Backpropagation
{
    public:
        Backpropagation(const vector<int> & netDescription, int numInputs);
        virtual ~Backpropagation();

        double train(Pattern & inPattern);
        void feedForward(double * input = 0);
        double * getOutput();

    private:
        Layer * layers;
        int numLayers;
        double lastError;
        Pattern * lastPattern;

        void backPropagate();
        void updateWeights();
        void calculateError();
};

#endif /* BACKPROPAGATION_H_ */
