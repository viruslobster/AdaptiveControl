#include "NeuralNetwork.h"
#include <boost/concept_check.hpp>


NeuralNetwork::NeuralNetwork (int num_hidden_layers, int num_hidden_nodes) {
  this->num_input_nodes = 3;  
  this->num_hidden_layers = num_hidden_layers;
  this->num_hidden_nodes = num_hidden_nodes;
  integral = 0;
  firstRun = true;
  
  
  outputNode = new Node(num_hidden_nodes);//init the outputNode
  
  hiddenLayer = new Node*[num_hidden_layers];
  for(int i=0;i<num_hidden_layers;i++) {
    if(i==0) {//if this is the first loop then we get out input from the input nodes
      hiddenLayer[i] = new Node[num_hidden_nodes];
      for(int a=0;a<num_hidden_nodes;a++) {
	hiddenLayer[i][a].setInputs(num_input_nodes);
      }
    } else {//if this is not the first run, we get out input from another hidden layer
      hiddenLayer[i] = new Node[num_hidden_nodes];
      for(int a=0;a<num_hidden_nodes;a++) {
	hiddenLayer[i][a].setInputs(num_hidden_nodes);	
      }      
    }
  }

}


void NeuralNetwork::loadConfig (char) {

}

double NeuralNetwork::getCorrection (double error) {
  double correction;
  vector<double> input;
  integral += error;
  if(firstRun) {    
    input.push_back(error);
    input.push_back(0);
    input.push_back(0);   
  } else {
    input.push_back(error);
    input.push_back(integral);
    input.push_back(error - lastError);
  }
  lastError = error;
  
  for(int i=0;i<num_hidden_layers;i++){
      vector<double> results;
      for(int j=0;j<num_hidden_nodes;j++) {
	//double input = {error, 0, 0};
	double out = hiddenLayer[i][j].input(input);
	results.push_back(out);
      }
      input = results;      
    }
    
    
    correction = outputNode->input(input);
    return correction;    
}

