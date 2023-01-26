#include "main.h"
#define kV 1642
#define kA 9950
#define kP 950
#define DEFAULT_TURN_KP 0.0422

// #define kA 50000
// #define kP 1000

double turnKP = DEFAULT_TURN_KP;

bool enablePP = false;
bool reverse = false;
Path path;

int closestPointIndex = 0;
double lastFracIndex = 0;
double targBearing = 0;

bool enableL = false, enableR = false;



void drive(double l, double r){
  Motor FL (FLPort);
  Motor BLU (BLUPort);
  Motor BLD (BLDPort);
  Motor FR (FRPort);
  Motor BRU (BRUPort);
  Motor BRD (BRDPort);

  FL.move(l);
  BLU.move(l);
  BLD.move(l);
  FR.move(r);
  BRU.move(r);
  BRD.move(r);
}

void resetPP() {
  closestPointIndex = 0;
  lastFracIndex = 0;
  targBearing = bearing;
}

void enableBase(bool left, bool right) {
  enableL = left;
  enableR = right;
}


void baseTurn(double p_bearing, double kp) {
  turnKP = kp;
  targBearing = p_bearing*toRad;
  printf("Turn to: %.5fdeg\n", p_bearing);
}

void baseTurn(double p_bearing) {
  baseTurn(p_bearing, DEFAULT_TURN_KP);
}

double calcBaseTurn(double x, double y, bool rev) {
  double turnBearing = atan2(x - position.getX(), y - position.getY());

  // if(fabs(turnBearing - bearing) > fabs(turnBearing - 360 - bearing)) turnBearing = turnBearing - 360;

  double diffBearing = boundRad(turnBearing - bearing);
  if(diffBearing > PI) diffBearing -= twoPI;
  turnBearing = bearing + diffBearing;

  return (rev ? (turnBearing+PI)*toDeg : turnBearing*toDeg);
}

// void baseTurn(double x, double y, bool rev) {
//   baseTurn(x, y, DEFAULT_TURN_KP, rev);
// }

void waitTurn(double cutoff) {
  double start = millis();
  while((fabs(targBearing - bearing)*toDeg > TURN_LEEWAY || fabs(measuredVL*inPerMsToRPM) > 5 || fabs(measuredVR*inPerMsToRPM) > 5) && millis() - start < cutoff) delay(5);
  printf("I stopped :)\n\n");
}

void basePP(std::vector<Node> wps, double p_w_data, double p_w_smooth, double p_lookAhead, bool p_reverse){
  path.setWps(wps, p_w_data, p_w_smooth, p_lookAhead);
  reverse = p_reverse;
}

void baseMove(double dis) {
  std::vector<Node> straightPath = {position, position + Node(dis*sin(bearing), dis*cos(bearing))};

  double smooth = 0.75;
	basePP(straightPath, 1-smooth, smooth, 14, dis < 0);
}

void baseMove(double x, double y, bool rev) {
  baseMove(sqrt(pow(x - position.getX(), 2) + pow(y - position.getY(), 2)) * (rev ? -1 : 1));
}

void baseMove(double x, double y) {
  baseMove(x, y, false);
}

void waitPP(double cutoff){
  // int stopTime;
  double start = millis();
  Node target = path.getSmoWp(path.getN()-1);
  while((distance(position, target) >= LEEWAY || fabs(measuredV*inPerMsToRPM) > 2) && millis() - start < cutoff) delay(5);

  resetPP();
  enablePP = false;
  reverse = false;

  printf("Stopped!!!\n\n");
}

void PPControl(void * ignore){
  Node lookAheadNode;

  // unit: in/ms
  double targV = 0, targVL = 0, targVR = 0;
  double prevTargVL = 0, prevTargVR = 0;
  // unit: in/ms^2
  double targAL = 0, targAR = 0;

  int count = 1;

  while(competition::is_autonomous()){
    if(count % 10 == 0) printf("status: %s\t", (enablePP? "enabled": "disabled"));

    if(enablePP) {

      // FIND CLOSEST POINT
      double minDist = INF;
      for(int i = closestPointIndex; i < path.getN(); ++i){
        double d = distance(position, path.getSmoWp(i));
        if(d < minDist){
          minDist = d;
          closestPointIndex = i;
        }
      }
      if(count % 10 == 0) {
        printf("Pt on path: ");
        path.getSmoWp(closestPointIndex).print();

      }

      // ===================================================================================

      // FIND LOOK AHEAD POINT
      for(int i = floor(lastFracIndex);i<=path.getN()-2;++i){

        Node start = path.getSmoWp(i);
        Node end = path.getSmoWp(i+1);
        std::vector<double> l = position.findLookAhead(start, end, path.getLookAhead());
        if(l[0]){
          // if there's an intersection calculate fractional index
          double fracIndex = i + l[1];
          if(fracIndex >= lastFracIndex){
            lookAheadNode = start + (end - start) * l[1];
            lastFracIndex = fracIndex;
            break;
          }
        }
      }

      if(count % 10 == 0) {
        printf("\tCurr: ");
        position.print();

        printf(" Bearing: %.2f\tlook ahead point:", bearing*toDeg);
        lookAheadNode.print();
      }

      // ===================================================================================

      // calculate moveCurvature
      // under "Curvature of Arc" header
      // calculate angle from x-axis, counter clockwise as positive
      double robotAngle = reverse ? angle+PI:angle;

      double a = -tan(robotAngle);
      double b = 1;
      double c = tan(robotAngle)*position.getX() - position.getY();
      double xabs = fabs(a * lookAheadNode.getX() + b * lookAheadNode.getY() + c)/sqrt(a*a + b*b);
      double crossProduct = sin(robotAngle)*(lookAheadNode.getX() - position.getX()) - cos(robotAngle)*(lookAheadNode.getY() - position.getY());
      double signedCurv = crossProduct >= 0 ? 1 : -1;
      double moveCurvature = signedCurv*2*xabs/(path.getLookAhead()*path.getLookAhead());

      // ===================================================================================

      // FIND TARGET VELOCITIES
      double targVClosest = reverse ? -path.getTargV(closestPointIndex) : path.getTargV(closestPointIndex);

      // rate limiter
      targV = targVClosest;
      targV = targV + abscap(targVClosest, globalMaxA);

      targVL = targV*(2 - moveCurvature*2*R_DIS)/2;
      targVR = targV*(2 + moveCurvature*2*R_DIS)/2;
      if(count % 10 == 0) printf("\tMove Curvature: %.5f", moveCurvature*1000);


    }else {
      double errorBearing = targBearing - bearing;
      printf("errorBearing: %.2f \n", errorBearing);
      if(enableL&&enableR) {
        targVR = enableL ? abscap(errorBearing*turnKP, globalMaxV) : 0;
        targVL = -targVR;

      }else {
        targVL = enableL ? abscap(errorBearing*0.2, globalMaxV) : 0;
        targVR = enableR ? -abscap(errorBearing*0.2, globalMaxV) : 0;
      }

      if(count % 10 == 0) {
        position.print();
        printf("\tBearing: %.5f\ttargVL: %5f", bearing*toDeg, targVL);
      }
    }

    // ===================================================================================

     // motor controller
    targAL = (targVL - prevTargVL)/dT;
    targAR = (targVR - prevTargVR)/dT;

    // feedforward terms
    double ffL = kV * targVL + kA * targAL;
    double ffR = kV * targVR + kA * targAR;

    // feedback terms
    double fbL;
    double fbR;

    if(reverse) {
      fbL = kP * (targVL - measuredVR);
      fbR = kP * (targVR - measuredVL);
    }else {
      fbL = kP * (targVL - measuredVL);
      fbR = kP * (targVR - measuredVR);
    }

        // set power
    if(reverse) {
      // if(count % 10 == 0) printf("PowerL: %4.2f\tPowerR: %4.2f\n", (ffR + fbR), (ffL + fbL));
      drive((ffR + fbR), (ffL + fbL));
    }else {
      // if(count % 10 == 0) printf("PowerL: %4.2f\tPowerR: %4.2f\n", (ffL + fbL), (ffR + fbR));
      drive((ffL + fbL), (ffR + fbR));
    }


    // handling prev
    prevTargVL = targVL;
    prevTargVR = targVR;


    // debugging
    if(count % 10 == 0) printf("\tTargV: %4.5f\tMeasuredV: %4.5f", targV*inPerMsToRPM, measuredV*inPerMsToRPM);
    count++;
    if(count % 10 == 0) printf("\n");

    delay(dT);
  }
}