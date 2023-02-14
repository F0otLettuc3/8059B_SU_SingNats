#include "main.h"
/** to test odometry in opcontrol() when not in competition */
#define COMPETITION_MODE false
/** Update the robot's position using side encoders values. */
void Odometry(void * ignore){
  Controller master(E_CONTROLLER_MASTER);

  /** D loop variables */
  double prevEncdV = 0, prevEncdL = 0, prevBearing = bearing;
  int count = 0;
  while(true){
    // Amount moved by robot
    double encdChangeV = encdV-prevEncdV;
    double encdChangeL = encdL-prevEncdL;
    double bearingChange = bearing - prevBearing;
    // printf("bearingChange %2f \n", bearingChange);

    // Update prev variables
		prevEncdV = encdV;
		prevEncdL = encdL;
    prevBearing = bearing;

    // Calculate local offset
    Node localOffset;
    if(bearingChange) {
      // printf("hello");
      localOffset = Node(encdChangeL/bearingChange + L_DIS, encdChangeV/bearingChange + V_DIS) * 2*sin(bearingChange/2);
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

void resetCoords(){
  printf("reset coords");
  Node rotatedOffset = Node(0,0);
  bearing = 0;
}
