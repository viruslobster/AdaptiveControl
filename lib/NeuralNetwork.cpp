#include "NeuralNetwork.h"
#include <cmath>
// uncomment to disable assert()
// #define NDEBUG
#include <cassert>


NeuralNetwork::NeuralNetwork ( int num_inputs, int num_outputs, int num_hidden_layers, int num_hidden_nodes ) {
  this->num_inputs = num_inputs + 1;// +1 for bias
  this->num_outputs = num_outputs;
  this->num_hidden_layers = num_hidden_layers;
  this->num_hidden_nodes = num_hidden_nodes;
  if(num_hidden_layers > 0) {
    layers.push_back(createLayer(num_hidden_nodes, this->num_inputs));
    
    for(int i=0;i<num_hidden_layers-1;++i) {
      layers.push_back(createLayer(num_hidden_nodes, num_hidden_nodes + 1));//hidden layers, +1 for bias   
    }
    
    //output layer
    layers.push_back(createLayer(num_outputs, num_hidden_nodes + 1));//+1 for bias
  } else {
   //output layer
    layers.push_back(createLayer(num_outputs, this->num_inputs));
  }

}

std::vector<double> NeuralNetwork::input (std::vector<double> &inputs) {
  using namespace std;
  inputs.push_back(0.0000);//bias
  std::vector<double> outputs;
  
  for(int i=0;i<num_hidden_layers + 1;i++) {
    //cout << i << endl;
    if(i > 0) {
      
      inputs = outputs;
      inputs.push_back(0.0000);//bias
    }
    //std::cout << i << ", " << outputs.size() << std::endl;
    if(i > 1) assert(outputs.size() == num_hidden_nodes);
    outputs.clear();
    
    for(int j=0;j<layers[i].size();j++) {
      double out = 0;
      //std::cout << layers[i][j].wieghts.size() << ", " << inputs.size() << std::endl;
      assert(layers[i][j].wieghts.size() == inputs.size());
      layers[i][j].inputs = inputs;
      for(int k=0;k<layers[i][j].wieghts.size();k++) {
	out += layers[i][j].wieghts[k] * inputs[k];
	layers[i][j].output = out;
      }
      /*if(i != num_hidden_layers)*/ out = sigmoid(out);
      outputs.push_back(out);
    }
    
  }
  
  assert(outputs.size() == num_outputs);
  
  return outputs;
}


Layer NeuralNetwork::createLayer (int neurons, int inputs) {
  Layer layer;
  for(int i=0;i<neurons;i++) {
   layer.push_back(Node(inputs)); 
  }
  
  return layer;

}

double NeuralNetwork::sigmoid (double value) {
  return (1/(1+exp(-value)));

}

void NeuralNetwork::learn (double error) {
  //std::cout << "LEARNING" << std::endl;
  //for the output nodes
  for(int i=0;i<num_outputs;i++) {
    double out = layers[num_hidden_layers][i].output;
    layers[num_hidden_layers][i].blame = out * (1.0-out) * error; 
    //std::cout << "[" << num_hidden_layers << "][" << i << "].blame = " << out * (1.0-out) * error << std::endl;
  }
  //for hidden nodes
  for(int i=num_hidden_layers-1;i>=0;i--) {
    for(int j=0;j<num_hidden_nodes;j++) {
      double blame = 0, out;
      out = layers[i][j].output;
      for(int k=0;k<layers[i+1].size();k++) {
	blame += layers[i+1][k].blame * layers[i+1][k].wieghts[j];
      }
      blame *= out * (1 - out);
      layers[i][j].blame = blame;
      //std::cout << "[" << i << "][" << j << "].blame = " << blame << std::endl;
    }   
  }
  update();
  //std::cout << "DONE LEARNING" << std::endl;

}

void NeuralNetwork::update() {
  for(int i=0;i<num_hidden_layers+1;i++) {
   for(int j=0;j<layers[i].size();j++) {
     for(int k=0;k<layers[i][j].wieghts.size();k++) {
      double delta_w;
      delta_w = 0.0001 * layers[i][j].blame * layers[i][j].inputs[k];
      layers[i][j].wieghts[k] += delta_w;
     }
   }
  }

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


