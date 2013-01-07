#ifndef NEURALNETWORK_H
#define NEURALNETWORK_H
#include <vector>
#include "Controller.h"
#include "Node.h"

using namespace std;

class NeuralNetwork : public Controller {

public:
    NeuralNetwork(int num_hidden_layers, int num_hidden_nodes);
    virtual void loadConfig (char);
    virtual double getCorrection (double);
    
private:
    Node* inputNodes;
    Node* outputNode;
    Node** hiddenLayer;
    double integral;
    double lastError;
    bool firstRun;
    int num_input_nodes, num_hidden_layers, num_hidden_nodes;
    
    
    
};

#endif // NEURALNETWORK_H
