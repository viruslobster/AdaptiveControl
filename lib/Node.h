#ifndef NODE_H
#define NODE_H
#include <vector>
using namespace std;

class Node {
public:
    Node(int num_inputs);
    double input(vector<double> &input);
    
private:
    double* w;//wieghts
    int num_inputs;
    double summation(vector<double> &input);
    double activation(double);
};

#endif // NODE_H
