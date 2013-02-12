#include "AdaptiveController.h"
#include <iostream>
using namespace std;

AdaptiveController::AdaptiveController(int num_hidden_layers, int num_hidden_nodes) {
  firstRun = true;
  integral = 0;  
  
  int *layers = new int[num_hidden_layers + 2];//+2 for input and output layers
  layers[0] = 2;
  cout << "[0] = " << 3 << endl;
  for(int i=1;i<num_hidden_layers+1;i++) {
    layers[i] = num_hidden_nodes;
    cout << "[" << i << "] = " << num_hidden_nodes << endl;
  }
  layers[num_hidden_layers+1] = 1;//the output layer
  cout << "[" << num_hidden_layers+1 << "] = " << 1 << endl;
  double beta = 0.5, alpha = 0.1;

	
	
	

	
  // Creating the net
  nn = new CBackProp(num_hidden_layers + 2, layers, beta, alpha);

  
  

}


double AdaptiveController::getCorrection ( double error ) {
  double correction;
  double input[2];
  //integral += error;
  if(firstRun) {    
    input[0] = error;
    input[1] = 0;
    //input[2] = 0;
    firstRun = false;
  } else {
    double error_vector[1];
    error_vector[0] = error;
    nn->bpgt(error_vector);
    input[0] = error;
    //input[1] = 0;//integral;
    input[1] = error - lastError;    
  }
  lastError = error;
  
  
    
    
  nn->ffwd(input);
  
  return nn->Out(0);    

}

void AdaptiveController::loadConfig ( char ) {

}

