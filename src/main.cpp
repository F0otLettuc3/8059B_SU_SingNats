#include "main.h"

void on_center_button() {}

void initialize()
{

	// INIT Base Motors
	Motor FL(FLPort, E_MOTOR_GEARSET_06, false, E_MOTOR_ENCODER_DEGREES);
	Motor BLU(BLUPort, E_MOTOR_GEARSET_06, true, E_MOTOR_ENCODER_DEGREES);
	Motor BLD(BLDPort, E_MOTOR_GEARSET_06, false, E_MOTOR_ENCODER_DEGREES);
	Motor FR(FRPort, E_MOTOR_GEARSET_06, true, E_MOTOR_ENCODER_DEGREES);
	Motor BRU(BRUPort, E_MOTOR_GEARSET_06, false, E_MOTOR_ENCODER_DEGREES);
	Motor BRD(BRDPort, E_MOTOR_GEARSET_06, true, E_MOTOR_ENCODER_DEGREES);

	// INIT Other Motors
	Motor FW(FWPort, E_MOTOR_GEARSET_06, false, E_MOTOR_ENCODER_DEGREES);
	Motor intake(intakePort, E_MOTOR_GEARSET_06, false, E_MOTOR_ENCODER_DEGREES);
	FW.tare_position();

	// ADIPorts
	ADIDigitalIn limit(limitPort);
	ADIDigitalOut indexer(indexerPort, false);

	// Tasks
	Task sensorTask(sensors, (void *)"PROS", TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "Sensor Task");
	Task FWCtrlTask(FWCtrl, (void *)"PROS", TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "Flywheel Task");
	// Task debugTask(Debug, (void *)"PROS", TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "Debug Task");
	Task odometryTask(Odometry, (void *)"PROS", TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "Odom Task");
	Task controlTask(PPControl, (void *)"PROS", TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "PP Task");
	
}

void disabled() {}

void competition_initialize() {}

void autonomous()
{
	// Motors
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
	// Enable Base
	enableBase(true, true);

	baseMove(35);

	// // Skills
		// // First Roller
		// baseMove(-5);
		// waitPP(700);
		// Intake.move(100);
		// delay(300);
		// Intake.move(0);
		// delay(50);

		// // Second Roller
		// basePP({position, Node(14, 15)}, 1 - smooth, smooth, 12);
		// waitPP(2000);
		// Intake.move(127);
		// baseTurn(90);
		// waitTurn(1000);
		// baseMove(-34);
		// waitPP(2000);
		// delay(300);
		// drive(30, 30);
		// Intake.move(100);
		// delay(300);
		// Intake.move(0);
		// drive(0, 0);

		// //First 3 Discs
		// MoveFW(3020, 0.033677777777777777777778, 0.009, 0.00024395, 0.0000090625);
		// basePP({position, Node(-25.5, 75)}, 1 - smooth, smooth, 7);
		// waitPP(3000);
		// delay(500);
		// baseTurn(8);
		// waitTurn(700);
		// Shoot(3,250);

		// //4th - 6th Disc
		// Intake.move(127);
		// baseTurn(-93);
		// waitTurn(900);
		// baseMove(-32);

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


void opcontrol()
{

	// Device Declaration
	Motor FL(FLPort);
	Motor FR(FRPort);
	Motor BLU(BLUPort);
	Motor BLD(BLDPort);
	Motor BRU(BRUPort);
	Motor BRD(BRDPort);
	Motor FW(FWPort);
	Motor Intake(intakePort);
	Controller Master(E_CONTROLLER_MASTER);
	ADIDigitalOut piston(indexerPort);

	// Initialise Pneumatic States
	//  piston.set_value(HIGH);

	// Initialise Driver States
	bool Tank = true;
	double left, right;
	FWSwitch = false;

	while (true)
	{

		if (Master.get_digital_new_press(DIGITAL_Y))
		{
			Tank = !Tank;
		}

		if (Tank)
		{
			left = Master.get_analog(ANALOG_LEFT_Y);
			right = Master.get_analog(ANALOG_RIGHT_Y);
		}
		else
		{
			double power = Master.get_analog(ANALOG_LEFT_Y);
			double turn = Master.get_analog(ANALOG_RIGHT_X);
			left = power + turn;
			right = power - turn;
		}

		FL.move(right);
		BLU.move(right);
		BLD.move(right);
		FR.move(left);
		BRU.move(left);
		BRD.move(left);

		// Triple Shot
		if (Master.get_digital_new_press(DIGITAL_R1))
		{
			FWSwitch = !FWSwitch;
		}

		if (FWSwitch){
			MoveFW(3020, 0.033677777777777777777778, 0.009, 0.00024395, 0.0000090625);
			// MoveFW(3425, 0.03127777777777777777777777777778, 0.075 ,0.02, 0.00001 ); // middle weird shot for auton
			}
		else{FW.move(0);}

		// MoveFW(3570, 0.02535, 0.001661, 0.00001); Long Shot
		// MoveFW(3310); Middle Shots

		// Triple Shot
		if (Master.get_digital_new_press(DIGITAL_R2)){Shoot(3,700);}

		// Intake
		if(Master.get_digital(DIGITAL_L1)){Intake.move(127);}
		else if(Master.get_digital(DIGITAL_L2)){Intake.move(-127);}
		else{Intake.move(0);}
		delay(10);
	}
}
