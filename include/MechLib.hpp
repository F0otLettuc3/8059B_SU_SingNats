#ifndef _MECHLIB_HPP_
#define _MECHLIB_HPP_

extern double TargVel;
extern double Kp, Ki, Kd, Kf;
extern bool FWSwitch;
extern int count, timer;
#define FWLowVal 4000
#define FWHighVal 4550


void FWCtrl(void*ignore);
void shootController(void*ignore);
void moveFW(double p_TargVel);
void moveFW(double p_TargVel, double p_Kf, double p_Kp, double p_Kd, double p_Ki);
void Shoot(int p_count, int p_timer);
void Roller(int p_target);



#endif