/*
 * Pattern.cpp
 *
 *  Created on: 26 Dec 2010
 *      Author: thomas
 */

#include "Headers/Pattern.h"

Pattern::Pattern(int numInputs, double * inputs, double * expectedOutput) : numInputs(numInputs), inputs(inputs), expectedOutput(expectedOutput){

}

Pattern::~Pattern()
{

}

double * Pattern::getInputs()
{
    return inputs;
}

int Pattern::getNumInputs()
{
    return numInputs;
}

double * Pattern::getOutput()
{
    return expectedOutput;
}
