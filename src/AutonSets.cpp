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
	// Task odometryTask(Odometry, (void *)"PROS", TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "Odom Task");
	Task controlTask(PPControl, (void *)"PROS", TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "PP Task");
	enableBase(true,true);
	double smooth = 0.75;
	double FWSwitch = true;
	setMaxRPMA(1.8);

	Intake.move(110); 		
	baseMove(-14);
	waitPP(1300);
	baseTurn(90);
	waitTurn(1000);
	baseMove(-3);
	waitPP(400);	
	Intake.move(0);
	baseMove(3);
	Intake.move(127);
	moveFW(3500, 0.039278, 1.8 ,0.50, 0.00001); // middle weird shot for auton
	waitPP(1000);
	baseTurn(225);
	waitTurn(1200);
	baseMove(-28);
	waitPP(1700);
	baseTurn(106);
	waitTurn(1100);
	Shoot(1,600);
	Shoot(1,600);
	Shoot(1,100);
	baseTurn(220);
	waitTurn(800);
	baseMove(-28);
	waitPP(1500);
	baseTurn(48);
	waitTurn(1000);
	baseMove(68);
	waitPP(1800);    
	Intake.move(40);
	baseTurn(180);
	waitTurn(1000);
	baseMove(-10);
	waitPP(700);	
	controlTask.suspend();
}



void  red2 (){
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
	// Task odometryTask(Odometry, (void *)"PROS", TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "Odom Task");
		Task controlTask(PPControl, (void *)"PROS", TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "PP Task");
	enableBase(true,true);
	double smooth = 0.75;
	double FWSwitch = true;
	setMaxRPMA(1.8);

	Intake.move(110); 		
	baseMove(-14);
	waitPP(1300);
	baseTurn(90);
	waitTurn(1000);
	baseMove(-3.5);
	waitPP(400);	
	Intake.move(0);
	baseMove(3);
	Intake.move(127);
	moveFW(3475, 0.039278, 1.65 ,0.50, 0.00001); // middle weird shot for auton
	waitPP(1000);
	baseTurn(225);
	waitTurn(1200);
	baseMove(-28);
	waitPP(1700);
	baseTurn(106);
	waitTurn(1100);
	Shoot(1,600);
	Shoot(1,600);
	Shoot(1,100);
	// baseTurn(220);
	// waitTurn(800);
	// baseMove(-28);
	// waitPP(1500);
	// baseTurn(48);
	// waitTurn(1000);
	// baseMove(68);
	// waitPP(1800);    
	// Intake.move(40);
	// baseTurn(180);
	// waitTurn(1000);
	// baseMove(-10);
	// waitPP(700);	
	controlTask.suspend();

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
	Task controlTask(PPControl, (void *)"PROS", TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "PP Task");
	double smooth = 0.75;
	double FWSwitch = true;
	enableBase(true,true);
	Intake.move(70);
	baseMove(-3);
	waitPP(400);   
	delay(100);
	Intake.move(0);
	delay(50);
	baseMove(3);
	waitPP(400);
	controlTask.suspend();	

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
	Task controlTask(PPControl, (void *)"PROS", TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "PP Task");
	double smooth = 0.75;
	double FWSwitch = true;
	enableBase(true,true);

	baseMove(-15);
	Intake.move(110);
	waitPP(1000);
	baseTurn(90);
	waitTurn(1000);
	baseMove(-5);
	waitPP(1000);
	delay(50);
	Intake.move(0);
	baseMove(5);
	waitPP(1000);
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
	ADIDigitalOut expansionR(Exp1);
	ADIDigitalOut expansionL(Exp2);

	// Tasks
	// Task odometryTask(Odometry, (void *)"PROS", TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "Odom Task");
	Task controlTask(PPControl, (void *)"PROS", TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "PP Task");
	double smooth = 0.86;
	double FWSwitch = true;
	enableBase(true,true);
	setMaxRPMA(1.48);
	
    // Skills
    // First Roller
	Intake.move(100);
	baseMove(-3);
	waitPP(400);   
	delay(100);
	Intake.move(0);
	delay(50);

	// Second Roller
	basePP({position, Node(10, 10)}, 1 - smooth, smooth, 3);
	waitPP(700);
	Intake.move(127);
	baseTurn(90);
	waitTurn(700);
	baseMove(-36.5);
	waitPP(1600);
	delay(50);
	Intake.move(0);


	//First 3 Discs
	moveFW(2907, 0.028677777777777777777778, 0.129, 0.0024395, 0.0000090625);
	baseMove(4);
	waitPP(300);
	baseTurn(0);
	waitTurn(600);
	baseMove(60);
	waitPP(2000);
	// baseTurn(10,0.05);
	// waitTurn(1000);
	Shoot(3,300);

	//4th - 6th Disc
	moveFW(0);
	Intake.move(127);
	waitPP(300);
	baseTurn(-41);
	waitTurn(900);
	baseMove(-34);
	waitPP(1500);
	setMaxRPMA(1);
	baseTurn(-142);
	waitTurn(1000);
	moveFW(2900, 0.031677777777777777777778, 0.122, 0.024395, 0.0000090625); //Corner but back (skills) shot
	baseMove(-40);
	waitPP(1200);
	baseTurn(-51);
	waitTurn(1000);
	Shoot(3,300);

	//7th - 9th Disc
	Intake.move(-115);
	baseTurn(-139);
	waitTurn(1500);
	setMaxRPMA(1.48);
	moveFW(2907, 0.028677777777777777777778, 0.129, 0.0024395, 0.0000090625);
	baseMove(-30);
	waitPP(2000);
	setMaxRPMA(0.1);
	Intake.move(127);
	baseMove(-25);
	waitPP(1500);
	setMaxRPMA(1.48);
	baseTurn(-90);
	waitTurn(1000);
	baseMove(30);
	waitPP(2000);
	Intake.move(100);
	baseTurn(-75);
	waitTurn(700);
	Shoot(3,250);
	baseTurn(-90);
	waitTurn(500);
	baseMove(-60);
	waitPP(4000);
	delay(30);
	Intake.move(80);
	baseTurn(180);
	baseMove(-27);
	waitPP(1000);
	Intake.move(0);
	baseMove(25);
	waitPP(1000);
	baseTurn(-135);
	waitTurn(1000);
	baseMove(-10);
	waitPP(1000);
	expansionL.set_value(HIGH);
	expansionR.set_value(HIGH);
	
}
