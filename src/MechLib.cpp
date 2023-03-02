#include "main.h"

#define FWKF 0.035278 // Conversion of Velocity to Power
#define FWKP 0.02525 // KP for FeedBack Loop 1.095 for long
#define FWKD 0.001652 //0.085  // KD for FeedBack Loop 0.250
#define FWKI 0.00001 //0.0042 //DO NOT TOUCH KI

double TargVel = 0; //Global Variable
double Kp, Kd, Ki, Kf;
bool FWSwitch = true;


void MoveFW(double p_TargVel, double p_Kf, double p_Kp, double p_Kd, double p_Ki){
    TargVel = p_TargVel;
    Kf = p_Kf;
    Kp = p_Kp;
    Kd = p_Kd;
    Ki = p_Ki;
}

void MoveFW(double p_TargVel){
    MoveFW(p_TargVel, FWKF, FWKP, FWKD, FWKI);
}


void FWCtrl(void *ignore)
{

    Motor FW(FWPort);
    Rotation FWEnc(FWEncPort);
    FWEnc.reset();

    double Error, PrevError, DeltaError = 0;
    double Power = 0;

    while (true){
        if(FWSwitch){
            // printf("casey kinda sus\n");
            double FWVal = (FWEnc.get_velocity()); //Centidegrees -> degrees -> rps -> rpm
            double actual_Vel = -(FWVal*60)/360 ;
            

            // FeedForward Component
            Power = TargVel * Kf;
            
            // FeedBack Component
            Error = TargVel - actual_Vel;
            double Integral = Integral + Error;
            if(Error == 0){
                Integral = 0;
            }
            if(fabs(Error) > 25){
                Integral = 0;
            }
            DeltaError = Error - PrevError;

            // Power Allocation
            Power += Error * Kp + Integral* Ki + DeltaError * Kd;
            FW.move(Power);
            PrevError = Error;

            // Debugging
            printf("Error: %lf \n", Error);
            // printf("Power: %lf \n", Power);
            // printf("Velocity: %lf \n", actual_Vel);
        }

		
    delay(30);
    }
}

// void ShootController(void*ignore){
//     ADIDigitalOut Indexer(indexerPort);
//     int count, timer;
//      for(int i = 0; i < count; i++){
//         Indexer.set_value(HIGH);
//         delay(50);
//         Indexer.set_value(LOW);
//         delay(timer);
//     }
// }


void Shoot(int p_count, int p_timer){
    ADIDigitalOut Indexer(indexerPort);
    int count = p_count;
    int timer = p_timer;
        for(int i = 0; i < count; i++){
        Indexer.set_value(HIGH);
        delay(50);
        Indexer.set_value(LOW);
        delay(timer);
    }
}

void Expand(){
    ADIDigitalOut expansionR(ExpRight);
	ADIDigitalOut expansionL(ExpLeft);
	ADIDigitalOut expansionMid(ExpMid);

    while(true){
        expansionR.set_value(HIGH);
        expansionL.set_value(HIGH);
        expansionMid.set_value(HIGH);
    }
} 