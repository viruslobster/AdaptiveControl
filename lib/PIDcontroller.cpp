#include "PIDcontroller.h"
#include <iostream>
#include <fstream>
#include <string>
#include <boost/algorithm/string.hpp>
#include <vector>
#include <stdlib.h>

using namespace std;
using namespace boost;

PIDcontroller::PIDcontroller() {
    isfirstrun = true;
    Kp = 0;
    Ki = 0;
    Kd = 0;
    min = 0;
    max = 0;
}

PIDcontroller::PIDcontroller(double min, double max) {
    this->isfirstrun = true;
    this->Kp = 1.2;
    this->Ki = 0.001;
    this->Kd = 30;
    this->min = min;
    this->max = max;


}

double PIDcontroller::getCorrection (double error) {
    double correction;

    if(isfirstrun) {
        correction = Kp * error;
        lastError = error;
        isfirstrun = false;
    } else {
        double d_error = error - lastError;
        integral += error;
        correction = Kp * error + Ki * integral + Kd * d_error;
        lastError = error;
    }

    if(min != max) {
        if(correction > max) correction = max;

        if(correction < min) correction = min;
    }

    return correction;
}

void PIDcontroller::loadConfig (char c) {
    string filename = "pid.";
    filename += c;
    filename.append(".config");
    ifstream file(filename.c_str());

    if(file.is_open()) {
        string line;
        getline(file, line);
        file.close();

        vector<string> fields;
        split(fields, line, is_any_of(","));
        double p, i, d;
        p = atof(fields[0].c_str());
        i = atof(fields[1].c_str());
        d = atof(fields[2].c_str());        
        tunePID(p, i, d);
    } else {
        cerr << "Cannot open " << filename << endl;
    }
}

void PIDcontroller::tunePID(double Kp, double Ki, double Kd) {
    this->Kp = Kp;
    this->Ki = Ki;
    this->Kd = Kd;
}





