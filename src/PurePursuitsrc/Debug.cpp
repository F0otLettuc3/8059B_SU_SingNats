#include "main.h"
void printVector(std::vector<double> vd){
  for(auto m : vd){
    printf("%.2f ", m);
  }
  printf("\n");
}
void posPrintTerminal(){
  printf("X: %.2f Y: %.2f bearing: %.2f\n", position.getX(), position.getY(), bearing*toDeg);
}
void posPrintMaster(){
  Controller master(E_CONTROLLER_MASTER);
  master.print(2, 0, "%.2f %.2f %.2f", position.getX(), position.getY(), bearing*toDeg);
}
void encdPrintTerminal(){
  printf("EncdL: %4.1f \t EncdR: %4.1f\n", encdL, encdV);
}
void velPrintTerminal(){
  printf("VelL: %.2f VelR: %.2f\n", measuredVL, measuredVR);
}

void Debug(void * ignore) {
  while(true) {
    switch(DEBUG_MODE) {
      case -1:
        posPrintTerminal();
        break;
      case 1:
        encdPrintTerminal();
        break;
      case 2:
        velPrintTerminal();
        break;
    }
    posPrintMaster();

    delay(dT);
  }
}
