#ifndef _MECHLIB_HPP_
#define _MECHLIB_HPP_

extern double TargVel;
extern double Kp, Ki, Kd, Kf;
extern bool FWSwitch;
#define FWLowVal 4000
#define FWHighVal 4550

void FWCtrl(void*ignore);
void MoveFW(double p_TargVel);
void MoveFW(double p_TargVel, double p_Kf, double p_Kp, double p_Kd, double p_Ki);




#endif