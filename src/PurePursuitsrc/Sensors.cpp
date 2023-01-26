#include "main.h"
/** global variables */
double offset = 0;
Node position;
double encdL = 0, encdV = 0, bearing = 0, angle = halfPI;
double measuredV = 0, measuredVL = 0, measuredVR = 0;
// angle = mathematical angle, taken from x-axis, counter clockwise as positive
void sensors(void * ignore){
  // port data from all sensors
   Motor FL (FLPort);
   Motor BLU (BLUPort);
   Motor BLD (BLDPort);
   Motor FR (FRPort);
   Motor BRU (BRUPort);
   Motor BRD (BRDPort);
   Imu imu(imuPort);
   ADIEncoder encoderV(encdVPort,(encdVPort+1),false);
   ADIEncoder encoderL(encdLPort,(encdLPort+1),false);
   bool calibrated = false;
   int start = millis();
  while(true){
    encdV = encoderV.get_value()*inPerDeg;
    encdL = encoderL.get_value()*inPerDeg;
    bearing = imu.is_calibrating()? 0 : (imu.get_rotation()*toRad + offset*toRad);
    angle = boundRad(halfPI - bearing);
    measuredVR = (FL.get_actual_velocity() + BLU.get_actual_velocity() + BLD.get_actual_velocity())/3 * RPMToInPerMs;
    measuredVL = (FR.get_actual_velocity() + BRU.get_actual_velocity() + BRD.get_actual_velocity())/3 * RPMToInPerMs;;
    measuredV = (measuredVL + measuredVR)/2;
    // printf("measuredVR: %.2f\t, measuredVL: %.2f\n", measuredVR, measuredVL);

    delay(5);
  }
}

void setOffset(double i) {
  offset = i;
}
