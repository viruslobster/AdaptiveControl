#ifndef ROBOT_H
#define ROBOT_H

struct Robot {
  double x, y, theta;
  void move(double correction);
  Robot();
  Robot(double x, double y);
};

#endif // ROBOT_H
