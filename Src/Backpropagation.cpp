/*
 * Backpropagation.cpp
 *
 *  Created on: 25 Dec 2010
 *      Author: thomas
 *
 */

#include "Headers/Backpropagation.h"

Backpropagation::Backpropagation(const vector<int> & netDescription, int numInputs)
{
    // katman sayısı
	numLayers = netDescription.size();

    // kaç katman olacağı...
    layers = new Layer[numLayers];

    // 0.katmana kadar.
    for(int i = netDescription.size() - 1; i > -1; i--)
    {
        bool isOutput = i == (int)netDescription.size() - 1; // sonuncu output oluyor.
        bool isInput = i == 0; // ilki de input...isİnput ilk layer

        Layer * nextLayer = (isOutput ? 0 : &layers[i + 1]);// sonuncuysa 0 nexti değilse nexti next + 1
        Layer * prevLayer = (isInput ? 0 : &layers[i - 1]); //inputsa yani baştakiyse previ 0;

        layers[i].initialiseLayer(netDescription[i], isOutput, isInput, nextLayer, prevLayer);
    }

    layers[0].connectInput(0, numInputs);// ilk katmana yapılan bağlantı.

    //İlk katman bağlandığı için bağlamaya gerek yok 1 den başlıyoruz.
    for(int i = 1; i < numLayers; i++)
    {

        layers[i].connectInput(layers[i - 1].getOutput(), layers[i - 1].getNumNeurons()); // çıkışlar girişlere bağlanıyor.
    }
}

Backpropagation::~Backpropagation()
{
    delete [] layers;
}

double Backpropagation::train(Pattern & inPattern)
{
    assert(inPattern.getNumInputs() == layers[0].getNumInputs());

    lastPattern = &inPattern;

    layers[0].setInput(inPattern.getInputs()); // ilk katmana veri seti veriliyor.

    feedForward();

    backPropagate();

    updateWeights();

    calculateError();
    return lastError;
}

void Backpropagation::feedForward(double * input)
{
//    for(int i= 0; i < 28;i++){
//        for(int j = 0; j < 28;j++){
//            cout<<*(input+i)<<" ";

//        }
//        cout<<endl;

//    }
    if(input != 0)
    {
        layers[0].setInput(input);
    }

    layers[0].feedForward();
}

double * Backpropagation::getOutput()
{
    return layers[numLayers - 1].getOutput();
}

void Backpropagation::backPropagate()
{
    for(int i = 0; i < layers[numLayers - 1].getNumNeurons(); i++)
    {
        layers[numLayers - 1].getNeurons()[i].setError((lastPattern->getOutput()[i] - layers[numLayers - 1].getOutput()[i])
                *
                Sigmoid::sigFuncPrime(layers[numLayers - 1].getOutput()[i]));
    }
    layers[numLayers - 2].backPropagate();
}

void Backpropagation::updateWeights()
{
    layers[0].updateWeights();
}

void Backpropagation::calculateError()
{
    lastError = 0.0;

    for(int i = 0; i < layers[numLayers - 1].getNumNeurons(); i++)
    {
        lastError += 0.5 * pow(lastPattern->getOutput()[i] - layers[numLayers - 1].getOutput()[i], 2);
    }
}
