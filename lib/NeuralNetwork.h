
#ifndef NEURALNETWORK_H
#define NEURALNETWORK_H

#include <cassert>
#include <iostream>
#include <cstdio>
#include <cmath>


class CBackProp {
    private:
        double **out;// output vector for neurons
        double **delta;// the blame for each neuron
        double ***weight;// wieghts for all neurons
        int numl;// number of layers in net
        int *lsize;// a vector for the number of neurons in each layer
        double beta;// learning weight
        double alpha;// momentum
        double ***prevDwt;// storage for previous weights, needed for momentum
        double sigmoid(double in);// non-linear activation function

    public:
        ~CBackProp();
        CBackProp(int nl, int *sz, double b, double a);
        void bpgt(double *tgt); // backpropagates error
        void ffwd(double *in); // feeds forward the input vector
        double mse(double *tgt) const;// mean square error
        double Out(int i) const;// returns the ouput of output node[i]
};

#endif
