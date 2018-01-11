/*
 * Layer.h
 *
 *  Created on: 25 Dec 2010
 *      Author: thomas
 */

#ifndef LAYER_H_
#define LAYER_H_

#include "Neuron.h"

#define LEARNING_RATE 0.2 // öğrenme katsayısı
#define ALPHA 0.2 // alpha katsayısı

class Layer
{
    public:
        Layer();
        virtual ~Layer();
        // layer initialize edilyior.
        void initialiseLayer(int inNumNeurons, bool inOutput, bool inInput, Layer * nextLayer, Layer * prevLayer);

        int getNumInputs();
        int getNumNeurons();
        double * getOutput();
        void connectInput(double * inInput, int inNumInputs);
        void setInput(double * inInput);

        void feedForward();
        void backPropagate();
        void updateWeights();

        Neuron * getNeurons();

    private:
        Neuron * neurons;
        double * input;
        double * output;
        int numInputs;
        int numNeurons;
        bool isOutput;
        bool isInput;

        Layer * nextLayer;
        Layer * prevLayer; // layerlar ar
};

#endif /* LAYER_H_ */
