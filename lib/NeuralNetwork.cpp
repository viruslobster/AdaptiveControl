
#include "NeuralNetwork.h"
#include <ctime>
#include <cstdlib>



CBackProp::CBackProp(int nl, int *sz, double b, double a) : beta (b), alpha (a) {
    // store layers and layer sizes
    numl = nl;
    lsize = new int[numl];

    for(int i = 0; i < numl; i++) {
        lsize[i] = sz[i];
    }

    // init output nodes for each neuron
    out = new double*[numl];
    // init delta array for each node
    delta = new double*[numl];
    
    for(int i = 0; i < numl; i++) {
        out[i] = new double[lsize[i]];
	if(i != 0) delta[i] = new double[lsize[i]];
    }   

    //	init space for each wieght
    weight = new double**[numl];
    //	init memory for previous weights
    prevDwt = new double**[numl];
    //	assign random initial wieghts
    srand ((unsigned)(time(NULL)));// seed the random number generator

    for(int i = 1; i < numl; i++) {
        weight[i] = new double*[lsize[i]];
        prevDwt[i] = new double*[lsize[i]];

        for( int j = 0; j < lsize[i]; j++ ) {
            weight[i][j] = new double[lsize[i - 1] + 1];
            prevDwt[i][j] = new double[lsize[i - 1] + 1];

            for(int k = 0; k < lsize[i - 1] + 1; k++) {
                weight[i][j][k] = ( double ) ( rand() ) / ( RAND_MAX / 2 ) - 1; //32767
                prevDwt[i][j][k] = ( double ) 0.0;
            }
        }
    }
}



CBackProp::~CBackProp() {
    //	free out
    for ( int i = 0; i < numl; i++ )
        delete[] out[i];

    delete[] out;

    //	free delta
    for ( int i = 1; i < numl; i++ )
        delete[] delta[i];

    delete[] delta;

    //	free weight
    for ( int i = 1; i < numl; i++ )
        for ( int j = 0; j < lsize[i]; j++ )
            delete[] weight[i][j];

    for ( int i = 1; i < numl; i++ )
        delete[] weight[i];

    delete[] weight;

    //	free prevDwt
    for ( int i = 1; i < numl; i++ )
        for ( int j = 0; j < lsize[i]; j++ )
            delete[] prevDwt[i][j];

    for ( int i = 1; i < numl; i++ )
        delete[] prevDwt[i];

    delete[] prevDwt;

    //	free layer info
    delete[] lsize;
}

// sigmoid function
double CBackProp::sigmoid(double in) {
    return (double)(1 / (1 + exp(-in)));
}

// mean square error
double CBackProp::mse ( double *tgt ) const {
    double mse = 0;

    for (int i = 0; i < lsize[numl - 1]; i++)
        mse += (tgt[i] - out[numl - 1][i]) * (tgt[i] - out[numl - 1][i]);

    return mse / 2;
}


// returns the ouput of output node[i]
double CBackProp::Out ( int i ) const {
    return out[numl - 1][i];// returns the ouput of output node[i]
}

// feeds forward the input vector
void CBackProp::ffwd (double *in) {
    double sum;

    // feed input vector to input layer
    for(int i = 0; i < lsize[0]; i++)
        out[0][i] = in[i];

    // for each layer
    for(int i = 1; i < numl; i++) {
        // for each neuron in layer
        for(int j = 0; j < lsize[i]; j++) {
            sum = 0.0;

            // for each input in the previous laye
            for (int k = 0; k < lsize[i - 1]; k++) {
                // Sum(w*x)
                sum += out[i - 1][k] * weight[i][j][k];
            }

            sum += weight[i][j][lsize[i - 1]];// bias
            out[i][j] = sigmoid(sum);// activation function
        }
    }
}


// backpropagates error
void CBackProp::bpgt(double *tgt) {
    double sum;



    // find delta for the output layer
    for(int i = 0; i < lsize[numl - 1]; i++) {
        double y = out[numl - 1][i];
        delta[numl - 1][i] = y * (1 - y) * (tgt[i] - y);
    }

    // find delta for hidden layers
    for(int i = numl - 2; i > 0; i--) {
        for(int j = 0; j < lsize[i]; j++) {
            sum = 0.0;

            for(int k = 0; k < lsize[i + 1]; k++ ) {
                sum += delta[i + 1][k] * weight[i + 1][k][j];
            }

            double y = out[i][j];
            delta[i][j] = y * (1 - y) * sum;
        }
    }

    //	apply momentum
    for(int i = 1; i < numl; i++) {
        for(int j = 0; j < lsize[i]; j++) {
            for(int k = 0; k < lsize[i - 1]; k++) {
                weight[i][j][k] += alpha * prevDwt[i][j][k];
            }

            weight[i][j][lsize[i - 1]] += alpha * prevDwt[i][j][lsize[i - 1]];// bias
        }
    }

    //	actualy adjust weights
    for(int i = 1; i < numl; i++) {
        for(int j = 0; j < lsize[i]; j++ ) {
            for(int k = 0; k < lsize[i - 1]; k++ ) {
                prevDwt[i][j][k] = beta * delta[i][j] * out[i - 1][k];
                weight[i][j][k] += prevDwt[i][j][k];
            }

            prevDwt[i][j][lsize[i - 1]] = beta * delta[i][j];
            weight[i][j][lsize[i - 1]] += prevDwt[i][j][lsize[i - 1]];
        }
    }
}

