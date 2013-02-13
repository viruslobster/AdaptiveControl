#ifndef ADAPTIVECONTROLLER_H
#define ADAPTIVECONTROLLER_H

#include "NeuralNetwork.h"
#include "Controller.h"

class AdaptiveController : public Controller {
    public:
        AdaptiveController(int num_hidden_layers, int num_hidden_nodes);
        virtual void loadConfig (char);
        virtual double getCorrection (double);
	
    private:
        NeuralNet *nn;
        double integral;
        double lastError;
        bool firstRun;
};

#endif // ADAPTIVECONTROLLER_H
