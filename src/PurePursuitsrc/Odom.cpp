#include "main.h"
/** to test odometry in opcontrol() when not in competition */
#define COMPETITION_MODE false
/** Update the robot's position using side encoders values. */
void Odometry(void * ignore){
  Controller master(E_CONTROLLER_MASTER);

  /** D loop variables */
  double prevEncdV = 0, prevEncdL = 0, prevBearing = bearing;
  int count = 0;
  while(!COMPETITION_MODE || competition::is_autonomous()){
    // Amount moved by robot
    double encdChangeV = encdV-prevEncdV;
    double encdChangeL = encdL-prevEncdL;
    double bearingChange = bearing - prevBearing;

    // Update prev variables
		prevEncdV = encdV;
		prevEncdL = encdL;
    prevBearing = bearing;

    // Calculate local offset
    Node localOffset;
    if(bearingChange) {
      localOffset = Node(encdChangeL/bearingChange + S_DIS, encdChangeV/bearingChange + R_DIS) * 2*sin(bearingChange/2);
    }else {
      localOffset = Node(encdChangeL, encdChangeV);
    }

    // Calculate global offset rotated by avg rotation
    double avgBearing = prevBearing + bearingChange/2;
    Node rotatedOffset = Node(cos(-avgBearing)*localOffset.getX() - sin(-avgBearing)*localOffset.getY(),
                              sin(-avgBearing)*localOffset.getX() + cos(-avgBearing)*localOffset.getY());
    position = position + rotatedOffset;


    master.print(2, 0, "%.2f, %.2f, %.2f          ", position.getX(), position.getY(), bearing/toRad);

    Task::delay(dT);
  }
}
