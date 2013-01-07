#include "Node.h"
#include <ctime> 
#include <cstdlib>
#include <cmath>


Node::Node() {

}

Node::Node (int num_inputs) {
  setInputs(num_inputs);
}

void Node::setInputs ( int num_inputs ) {
  this->num_inputs = num_inputs;
  w = new double[num_inputs];
  for(int i=0;i<num_inputs;i++) {
    double f = (double)rand() / RAND_MAX;
    w[i] =  -0.5 + f;//random number between -0.5 and 0.5
  }
}


double Node::input (vector<double>& input) {
  double sum = summation(input);
  return activation(sum);
}

double Node::summation (vector<double>& input) {
  if(input.size() != num_inputs) return 0;
  
  double sum = 0;
  for(int i=0;i<num_inputs;i++) {
    sum += input[i] * w[i];    
  }
  
  return sum;
}

double Node::activation (double t) {  
  return (1/(1+exp(-t)));//sigmoid activation function
}




