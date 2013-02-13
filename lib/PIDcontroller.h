#ifndef PIDCONTROLLER_H
#define PIDCONTROLLER_H

#include "Controller.h"

class PIDcontroller : public Controller {
    public:
        PIDcontroller();
        PIDcontroller(double, double);
        double getCorrection(double);
        void loadConfig(char);
        void tunePID(double, double, double);

    private:        
        double integral;
        double Kp, Ki, Kd;
        double lastError;        
        bool isfirstrun;
        double min, max;
};

#endif // PIDCONTROLLER_H
