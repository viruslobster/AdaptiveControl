#ifndef NEURALNETWORK_H
#define NEURALNETWORK_H
#include <vector>
#include <cstdlib>
#include <iostream>



struct Node {
  std::vector<double> wieghts;
  std::vector<double> inputs;
  double output;
  double blame;
  Node(int inputs) {
    for(int i=0;i<inputs;i++) {
      double f = (double)rand() / RAND_MAX;
      wieghts.push_back(-1 + f * 2);//random number between -1 and 1
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
  std::vector<double> input(std::vector<double> &inputs);
  void learn(double error);
  void update();
  std::vector< Layer > layers;
  void print();
  
  
private:
  Layer createLayer(int neurons, int inputs);
  int num_inputs, num_outputs, num_hidden_layers, num_hidden_nodes;
  double sigmoid(double value);
  
  
};

#endif // NEURALNETWORK_H
