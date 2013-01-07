#ifndef NEURALNETWORK_H
#define NEURALNETWORK_H

#include "Controller.h"


class NeuralNetwork : public Controller {

public:
    NeuralNetwork(int num_input_nodes, int num_output_nodes, int num_hidden_layers, int num_hidden_nodes);
    virtual void loadConfig (char);
    virtual double getCorrection (double);
    
    
};

#endif // NEURALNETWORK_H
