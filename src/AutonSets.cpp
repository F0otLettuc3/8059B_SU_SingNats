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

	// Tasks
	Task odometryTask(Odometry, (void *)"PROS", TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "Odom Task");
	Task controlTask(PPControl, (void *)"PROS", TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "PP Task");
	double smooth = 0.75;
	double FWSwitch = true;
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
	double smooth = 0.75;
	double FWSwitch = true;
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

	// Tasks
	Task odometryTask(Odometry, (void *)"PROS", TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "Odom Task");
	Task controlTask(PPControl, (void *)"PROS", TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "PP Task");
	double smooth = 0.75;
	double FWSwitch = true;

    
	//blue 1
	// First Roller
	printf("start");
	MoveFW(3550, 0.0317777777777777777777777777778, 0.0525, 0.01, 0.001); 		
	baseMove(-1.6);
	waitPP(500);
	Intake.move(100);
	delay(250);
	Intake.move(0);
	
	//Discs
	baseMove(13.5);
	waitPP(1200);
	baseTurn(-17);
	waitTurn(1000);
	delay(250);
	Shoot(2,1350);

	//Move Forward
	Intake.move(-110);
	baseMove(-8);
	waitPP(1200);
	setMaxRPMA(0.5);
	baseTurn(-125, 0.020);
	waitTurn(1550);
	baseMove(-25);
	waitPP(3000);
	setMaxRPMA(0.05);
	Intake.move(110);
	baseMove(-32);
	waitPP(1500);
	baseTurn(-35);
	waitTurn(1000);
	MoveFW(3415, 0.03127777777777777777777777777778, 0.075 ,0.02, 0.00001 ); // middle weird shot for auton
	Shoot(3,650);
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
	waitPP(2000);
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
	MoveFW(3020, 0.033677777777777777777778, 0.009, 0.00024395, 0.0000090625);
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
