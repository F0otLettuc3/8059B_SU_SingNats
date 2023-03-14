#include "main.h"

void red1 ()
{
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
	enableBase(true,true);
	double smooth = 0.75;
	double FWSwitch = true;
	setMaxRPMA(1.5);

	//First Roller
	Intake.move(110); 		
	baseMove(-14);
	waitPP(1300);
	baseTurn(90);
	waitTurn(1000);
	baseMove(-3);
	waitPP(400);	
	Intake.move(0);
	baseMove(3);

	//Intake Discs
	Intake.move(127);
	MoveFW(3500, 0.039278, 1.8 ,0.50, 0.00001); // middle weird shot for auton
	waitPP(1000);
	baseTurn(225);
	waitTurn(1200);
	baseMove(-28);
	waitPP(1700);

	//Shoot Discs
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
	MoveFW(3475, 0.039278, 1.65 ,0.50, 0.00001); // middle weird shot for auton
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


	// Tasks
	Task controlTask(PPControl, (void *)"PROS", TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "PP Task");
	double smooth = 0.75;
	double FWSwitch = true;
	enableBase(true,true);
	setMaxRPMA(1.5);
	// baseMove(40);
	delay(1000);
	baseTurn(10, 0.3, 0.25);

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
	Controller Master(E_CONTROLLER_MASTER);


	// Tasks
	// Task odometryTask(Odometry, (void *)"PROS", TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "Odom Task");
	Task controlTask(PPControl, (void *)"PROS", TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "PP Task");
	double smooth = 0.86;
	double FWSwitch = true;
	enableBase(true,true);
	setMaxRPMA(1.48);
	// setMaxRPMV(500);
	
    // Matchloads
	MoveFW(2875, 0.0307, 0.2150, 0.009, 0.00001);
	delay(1200);
	Shoot(10,550);
	// delay(4400);nn
	Intake.move(127);

	// First Set of Discs
	baseMove(15);
	waitPP(1200);
	baseTurn(55);
	waitTurn(800);
	baseMove(-27);
	waitPP(1500);
	delay(100);
	setMaxRPMA(0.4);
	baseMove(-10);
	waitPP(2000);
	setMaxRPMA(1.48);
	MoveFW(2785, 0.0307, 0.2125, 0.009, 0.00001);
	baseMove(38);
	waitPP(1400);
	baseTurn(2);
	waitTurn(400);
	Shoot(3,400);

	// Second Set of Discs
	baseTurn(9, 0.3, 0.25);
	waitTurn(500);
	baseMove(-4);
	waitPP(600);
	baseTurn(105);
	waitTurn(1400);
	baseMove(-44);
	waitPP(1400);
	baseTurn(152, 0.048, 0.3);
	waitTurn(900);
	baseMove(-40);
	waitPP(1500);
	baseTurn(88);
	waitTurn(1000);
	baseMove(22);
	waitPP(1300);
	Shoot(3,400);

	// Third Set of Discs
	baseTurn(95, 0.2, 0.15);
	waitTurn(700);
	baseMove(-39.5);
	waitPP(1500);
	setMaxRPMA(0.4);
	delay(300);
	baseMove(-16);
	waitPP(1400);
	setMaxRPMA(0.8);
	baseTurn(107);
	waitTurn(700);

	// First Roller
	Intake.move(105);
	baseMove(-13.3);
	waitPP(1200);
	MoveFW(2900, 0.0307, 0.2150, 0.009, 0.00001);
	

	// Second Roller
	baseMove(25);
	waitPP(1000);
	Intake.move(-110);
	baseTurn(193);
	waitTurn(1000);
	baseMove(-31.5);
	waitPP(1750);

	// Matchloads 2
	baseMove(28);
	waitPP(1600);
	baseTurn(233);
	waitTurn(1100);
	baseMove(45.7);
	waitPP(1600);
	baseTurn(180);
	waitTurn(1000);
	baseMove(-3.7);
	waitPP(1000);
	Shoot(10,550);
	Intake.move(127);

	// Fourth Set of Discs
	MoveFW(3100, 0.03, 0.3, 0.009, 0.00001);
	baseMove(10);
	waitPP(1200);
	baseTurn(283);
	waitTurn(1500);
	baseMove(-44.3);
	waitPP(1700);
	baseTurn(326);
	waitTurn(1200);
	baseMove(-52.4);
	waitPP(1600);
	baseTurn(272);
	waitTurn(1000);
	Shoot(3,400);

	setMaxRPMV(600);
	setMaxRPMA(1.75);


	// Third Roller
	baseTurn(290);
	waitTurn(700);
	baseMove(-44);
	waitPP(1450);


	// // Fourth Roller
	// baseMove(15);
	// waitPP(700);
	// baseTurn(10);
	// waitTurn(1100);
	// baseMove(-13);
	// waitPP(800);

	//Expansion lezgo
	baseMove(15);
	waitPP(800);
	baseTurn(-30); 
	waitTurn(1000);
	delay(400);
	// Master.print(0,2, "Expand Now!!!");
	Expand();

}


void driverSkills (){
    Motor FL(FLPort);
	Motor FR(FRPort);
	Motor BLU(BLUPort);
	Motor BLD(BLDPort);
	Motor BRU(BRUPort);
	Motor BRD(BRDPort);
	Motor FW(FWPort);
	Motor Intake(intakePort);
	ADIDigitalOut piston(indexerPort);
	Controller Master(E_CONTROLLER_MASTER);


	// Tasks
	// Task odometryTask(Odometry, (void *)"PROS", TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "Odom Task");
	Task controlTask(PPControl, (void *)"PROS", TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "PP Task");
	Task FWCtrlTask(FWCtrl, (void *)"PROS", TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "Flywheel Task");
	double smooth = 0.86;
	double FWSwitch = true;
	enableBase(true,true);
	setMaxRPMA(1.48);
	// setMaxRPMV(500);
	
    // Matchloads
	MoveFW(2875, 0.0307, 0.2150, 0.009, 0.00001);
	delay(1200);
	Shoot(10,550);
	// delay(5500);
	Intake.move(127);

	// First Set of Discs
	baseMove(15);
	waitPP(1200);
	baseTurn(55);
	waitTurn(1000);
	baseMove(-27);
	waitPP(1500);
	delay(100);
	setMaxRPMA(0.4);
	baseMove(-10);
	waitPP(2000);
	setMaxRPMA(1.48);
	MoveFW(2800, 0.0307, 0.2125, 0.009, 0.00001);
	baseMove(38);
	waitPP(1400);
	baseTurn(2);
	waitTurn(400);
	Shoot(3,400);

	// Second Set of Discs
	baseTurn(9, 0.3, 0.25);
	waitTurn(500);
	baseMove(-4);
	waitPP(600);
	baseTurn(103);
	waitTurn(1400);
	baseMove(-44);
	waitPP(1400);
	baseTurn(152, 0.048, 0.3);
	waitTurn(900);
	baseMove(-40);
	waitPP(1500);
	baseTurn(88);
	waitTurn(1000);
	baseMove(22);
	waitPP(1300);
	Shoot(3,400);

	controlTask.suspend();

}
