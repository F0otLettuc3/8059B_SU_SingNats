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
	setMaxRPMA(1.5);
	// baseMove(40);
	baseTurn(-90);

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
	Intake.move(80);
	baseMove(-3);
	waitPP(400);   
	delay(100);
	Intake.move(0);
	delay(50);

	// Second Roller
	basePP({position, Node(10, 10)}, 1 - smooth, smooth, 3);
	waitPP(700);
	Intake.move(110);
	baseTurn(90);
	waitTurn(700);
	baseMove(-33);
	waitPP(1600);
	delay(50);
	Intake.move(0);


	//First 3 Discs
	moveFW(3145, 0.0307, 0.2125, 0.009, 0.00001);
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
	baseTurn(-140);
	waitTurn(1000);
	moveFW(3145, 0.0307, 0.2125, 0.009, 0.00001);
	baseMove(-33);
	waitPP(1400);
	baseTurn(-45);
	waitTurn(1000);
	Shoot(3,350);

	//7th and 8th disc
	baseMove(-20);
	waitPP(1200);
	baseTurn(-135);
	waitTurn(1000);
	Intake.move(127);
	baseMove(-30);
	waitPP(1700);
	baseTurn(-15);
	waitTurn(1000);
	baseMove(45);
	waitPP(1600);
	baseTurn(-87);
	waitTurn(1500);
	baseMove(10);
	waitPP(1000);
	baseTurn(92);
	waitTurn(1000);
	
	
}
