
#ifndef CONTROLLER_H
#define CONTROLLER_H

class Controller {
public:
  virtual double getCorrection(double) = 0;
  virtual void loadConfig(char) = 0;
  
};

#endif // CONTROLLER_H
