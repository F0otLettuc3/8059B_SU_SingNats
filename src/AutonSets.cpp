#include "main.h"

void red1 (){
    Motor FL(FLPort);
	Motor FR(FRPort);
	Motor BLU(BLUPort);
	Motor BLD(BLDPort);
	Motor BRU(BRUPort);
	Motor BRD(BRDPort);
	Motor FW(FWPort);
	Motor Intake(intakePort);
	ADIDigitalOut piston(indexerPort);
	ADIDigitalOut intakeLift(intakePiston);
	intakeLift.set_value(HIGH);

	// Tasks
	Task odometryTask(Odometry, (void *)"PROS", TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "Odom Task");
	Task controlTask(PPControl, (void *)"PROS", TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "PP Task");
	double smooth = 0.75;
	double FWSwitch = true;
	enableBase(true,true);

	// intakeLift.set_value(HIGH);
	FW.move(127);
	MoveFW(3600, 0.04, 0.25, 0.06, 0.001); 		
	baseMove(-1.4);
	waitPP(500);	
	Intake.move(110);
	delay(450);
	Intake.move(0);
	
	//Discs
	baseMove(15);
	waitPP(700);
	delay(300);
	baseTurn(-17,0.078);
	waitTurn(700);
	Shoot(2,850);

	//Move Forward
	Intake.move(127); //Triple Stack Intake
	FW.move(0);
	baseMove(-5);
	waitPP(700);
	baseTurn(-125,0.046);
	waitTurn(1200);
	MoveFW(3560, 0.03367777777777777777777777777778, 0.135 ,0.03, 0.00001); // middle weird shot for auton
	baseMove(-15);
	waitPP(900);
	setMaxRPMA(0.016);
	baseMove(-45);
	waitPP(1400);
	setMaxRPMA(3);
	setMaxRPMV(900);
	delay(300);	
	baseTurn(-30);
	waitTurn(700);
	Shoot(3,550);
	
	// Final Roller
	Intake.move(110);
	baseTurn(-134);
	waitTurn(1100);
	baseMove(-97);
	waitPP(3000);
	baseTurn(-90);
	waitTurn(1000);
	baseMove(-9);
	waitPP(1000);
	delay(150);
	Intake.move(0);


}



void red2 (){
    Motor FL(FLPort);
	Motor FR(FRPort);
	Motor BLU(BLUPort);
	Motor BLD(BLDPort);
	Motor BRU(BRUPort);
	Motor BRD(BRDPort);
	Motor FW(FWPort);
	Motor Intake(intakePort);
	ADIDigitalOut piston(indexerPort);

	// Tasks
	Task odometryTask(Odometry, (void *)"PROS", TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "Odom Task");
	Task controlTask(PPControl, (void *)"PROS", TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "PP Task");
	double smooth = 0.85;
	double FWSwitch = true;
	printf("start");
	enableBase(true,true);


	basePP({position, Node(-30,30)}, 1-smooth, smooth, 14);
	// baseTurn(90);
	// waitTurn(1000);
	// baseMove(30);
	// baseMove(30);
	waitPP(1000);




}



void blue1 (){
    Motor FL(FLPort);
	Motor FR(FRPort);
	Motor BLU(BLUPort);
	Motor BLD(BLDPort);
	Motor BRU(BRUPort);
	Motor BRD(BRDPort);
	Motor FW(FWPort);
	Motor Intake(intakePort);
	ADIDigitalOut piston(indexerPort);
	ADIDigitalOut intakeLift(intakePiston);

	// Tasks
	Task odometryTask(Odometry, (void *)"PROS", TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "Odom Task");
	Task controlTask(PPControl, (void *)"PROS", TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "PP Task");
	double smooth = 0.75;
	double FWSwitch = true;

	// First Roller
	enableBase(true,true);
	printf("start");
	intakeLift.set_value(HIGH);
	MoveFW(3530, 0.0317777777777777777777777777778, 0.0525, 0.01, 0.001); 		
	baseMove(-3);
	waitPP(500);
	Intake.move(100);
	delay(250);
	Intake.move(0);
	
	//Discs
	baseMove(13.5);
	waitPP(1200);
	baseTurn(-19);
	waitTurn(1000);
	delay(250);
	Shoot(2,1350);

	//Move Forward
	intakeLift.set_value(LOW);
	Intake.move(127);
	baseMove(-8);
	waitPP(1200);
	// setMaxRPMA(0.5);
	// baseTurn(-123, 0.020);
	// waitTurn(1550);
	// baseMove(-20);
	// waitPP(3000);
	// intakeLift.set_value(HIGH); 
	// delay(1900);
	// baseTurn(-30,0.022);
	// waitTurn(1500); 
	// MoveFW(3475, 0.03127777777777777777777777777778, 0.075 ,0.02, 0.00001); // middle weird shot for auton
	// Shoot(3,650);
	// printf("time: %.2f", start);

	// Final Roller
	FW.move(0);
	Intake.move(127);
	basePP({position, Node(80,95)}, 1- smooth, smooth, 12);
	waitPP(7000);
	baseTurn(-90);
	waitTurn(2000);
	baseMove(-5);
	waitPP(1000);
}

void blue2 (){
    Motor FL(FLPort);
	Motor FR(FRPort);
	Motor BLU(BLUPort);
	Motor BLD(BLDPort);
	Motor BRU(BRUPort);
	Motor BRD(BRDPort);
	Motor FW(FWPort);
	Motor Intake(intakePort);
	ADIDigitalOut piston(indexerPort);
      
	// Tasks
	Task odometryTask(Odometry, (void *)"PROS", TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "Odom Task");
	Task controlTask(PPControl, (void *)"PROS", TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "PP Task");
	double smooth = 0.75;
	double FWSwitch = true;
}


void skills (){
    Motor FL(FLPort);
	Motor FR(FRPort);
	Motor BLU(BLUPort);
	Motor BLD(BLDPort);
	Motor BRU(BRUPort);
	Motor BRD(BRDPort);
	Motor FW(FWPort);
	Motor Intake(intakePort);
	ADIDigitalOut piston(indexerPort);

	// Tasks
	Task odometryTask(Odometry, (void *)"PROS", TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "Odom Task");
	Task controlTask(PPControl, (void *)"PROS", TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "PP Task");
	double smooth = 0.75;
	double FWSwitch = true;
	enableBase(true,true);

    // Skills
    // First Roller
	baseMove(-5);
	waitPP(700);   
    Intake.move(100);
	delay(300);
	Intake.move(0);
	delay(50);

	// Second Roller
	basePP({position, Node(14, 15)}, 1 - smooth, smooth, 12);
	waitPP(1000);
	Intake.move(127);
	baseTurn(90);
	waitTurn(1000);
	baseMove(-34);
	waitPP(2000);
	delay(300);
	drive(30, 30);
	Intake.move(100);
	delay(300);
	Intake.move(0);
	drive(0, 0);

	//First 3 Discs
	MoveFW(2960, 0.033677777777777777777778, 0.009, 0.00024395, 0.0000090625);
	basePP({position, Node(-25.5, 75)}, 1 - smooth, smooth, 7);
	waitPP(3000);
	delay(500);
	baseTurn(8);
	waitTurn(700);
	Shoot(3,250);

	//4th - 6th Disc
	Intake.move(127);
	baseTurn(-93);
	waitTurn(900);
	baseMove(-32);

}
