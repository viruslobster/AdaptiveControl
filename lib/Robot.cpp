#include "Robot.h"
#include "Math.h"

Robot::Robot() {
  x     = 0;
  y     = 0;
  theta = 0;
}

Robot::Robot(double x, double y) {
  this->x     = x;
  this->y     = y;
  this->theta = 0.0;
}

void Robot::move(double distance, double turn) {
  theta += turn + randn_notrig(0, 0.5 * (PI / 180.0));
  x += distance * cos(theta);
  y += distance * sin(theta);
}



