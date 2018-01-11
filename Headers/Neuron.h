/*
 * Neuron.h
 *
 *  Created on: 25 Dec 2010
 *      Author: thomas
 */

#ifndef NEURON_H_
#define NEURON_H_

#include <stdlib.h>
#include "Sigmoid.h"

class Neuron
{
    public:
        Neuron();
        virtual ~Neuron();

        void initialiseNeuron(double * inInput, int inNumInputs); // noronun oluşturulması.
        void setInput(double * inInput); // girişin setlenmesi.
        double getOutput();// noronun çıkışı.

        double fire();  // ağırlar ve girişin çarpımının sigmoid fonksiyonuna verililiyor test için çıktı.
        double getWeightedSum(); // giriş ve ağırlıkların  çarpımının toplamı

        void setError(double inError);
        double getError();

        double * getWeights();
        double * getPrevWeightDelta();
        int getNumInputs();
        double * getInput();

    private:
        double * input; //giriş
        double * weights; // şu an ki ağırlık
        double * prevWeightDelta; // önce ki ağırlık
        double output; // çıkış
        double error; // hata miktari
        int numInputs; //giriş sayısı
};

#endif /* NEURON_H_ */
