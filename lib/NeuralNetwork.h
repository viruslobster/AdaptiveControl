#ifndef NEURALNETWORK_H
#define NEURALNETWORK_H
#include <vector>
#include <cstdlib>
#include <iostream>



struct Node {
  std::vector<double> wieghts;  
  double output;
  double blame;
  Node(int inputs) {
    for(int i=0;i<inputs;i++) {
      double f = (double)rand() / RAND_MAX;
      wieghts.push_back(-0.5 + f);//random number between -0.5 and 0.5
    }    
  }
  
  void print() {
    for(int i=0;i<wieghts.size();i++) {
      std::cout << "[" << i << "]: " << wieghts[i] << std::endl;      
    }
  }
  
};
typedef std::vector<Node> Layer;


class NeuralNetwork {
public:
  NeuralNetwork(int num_inputs, int num_outputs, int num_hidden_layers, int num_hidden_nodes);
  double input(std::vector<double> inputs);
  double learn(double error);
  void update();
  std::vector< Layer > layers;
  void print();
  
  
private:
  Layer createLayer(int neurons, int inputs);
  int num_inputs, num_outputs, num_hidden_layers, num_hidden_nodes;
  
  
};

#endif // NEURALNETWORK_H
