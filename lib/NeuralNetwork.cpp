#include "NeuralNetwork.h"

NeuralNetwork::NeuralNetwork ( int num_inputs, int num_outputs, int num_hidden_layers, int num_hidden_nodes ) {
  this->num_inputs = num_inputs + 1;// +1 for bias
  this->num_outputs = num_outputs;
  this->num_hidden_layers = num_hidden_layers;
  this->num_hidden_nodes = num_hidden_nodes;
  
  layers.push_back(createLayer(num_hidden_nodes, this->num_inputs));
  
  for(int i=0;i<num_hidden_layers-1;++i) {
    layers.push_back(createLayer(num_hidden_nodes, num_hidden_nodes));//hidden layers    
  }
  
  //output layer
  layers.push_back(createLayer(num_outputs, num_hidden_nodes));

}

Layer NeuralNetwork::createLayer (int neurons, int inputs) {
  Layer layer;
  for(int i=0;i<neurons;i++) {
   layer.push_back(Node(inputs)); 
  }
  
  return layer;

}

void NeuralNetwork::print() {
  using namespace std;
  
  cout << "=========== INPUT LAYER =============" << endl;
  
  for(int i=0;i<num_inputs;i++) {
    cout << "[" << i << "] ";
  }
  
  cout << endl << "=========== HIDDEN LAYERS ===========" << endl;
  for(int i=0;i<layers.size()-1;i++) {
   for(int j=0;j<layers[i].size();j++) {
    cout << "[" << j << "] ";  
   }
   cout << endl << "------------------------------" << endl;
  }
  cout << "=========== OUTPUT LAYER ===========" << endl;
  
  for(int j=0;j<layers[layers.size()-1].size();j++) {
    cout << "[" << j << "] ";  
   }
   cout << endl << "------------------------------" << endl;
  

}


