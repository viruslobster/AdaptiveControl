#include "PIDcontroller.h"
#include <sys/time.h>
#include <stdio.h>
#include <unistd.h>

PIDcontroller::PIDcontroller() {
  isfirstrun = true;
  Kp = 5;
  Ki = 0.001;
  Kd = 1;
  

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
  
  return correction;
}

void PIDcontroller::tunePID (double Kp, double Ki, double Kd) {
  this->Kp = Kp;
  this->Ki = Ki;
  this->Kd = Kd;
}




