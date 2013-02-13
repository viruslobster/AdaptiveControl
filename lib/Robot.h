#ifndef ROBOT_H
#define ROBOT_H

struct Robot {
    double x, y, theta;
    void move(double distance, double turn);
    Robot();
    Robot(double x, double y);
};

#endif // ROBOT_H
