#include "PIDcontroller.h"
#include <sys/time.h>
#include <stdio.h>
#include <unistd.h>

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
  //double time = getTimeMilli();
  //double d_error = error - lastError;
  //double d_time  = time - lastTime;
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

void PIDcontroller::tunePID(double Kp, double Ki, double Kd) {
  this->Kp = Kp;
  this->Ki = Ki;
  this->Kd = Kd;
}





