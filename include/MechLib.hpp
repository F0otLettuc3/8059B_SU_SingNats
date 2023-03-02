#ifndef MECHLIB_HPP
#define MECHLIB_HPP

extern double TargVel;
extern double Kp, Ki, Kd, Kf;
extern bool FWSwitch;
extern int count, timer;
#define FWLowVal 4000
#define FWHighVal 4550


void FWCtrl(void*ignore);
void ShootController(void*ignore);
void MoveFW(double p_TargVel);
void MoveFW(double p_TargVel, double p_Kf, double p_Kp, double p_Kd, double p_Ki);
void Shoot(int p_count, int p_timer);
void Expand();




#endif