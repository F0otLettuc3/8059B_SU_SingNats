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
	Task debugTask(Debug, (void *)"PROS", TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "Debug Task");
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

	// Tasks
	Task odometryTask(Odometry, (void *)"PROS", TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "Odom Task");
	Task controlTask(PPControl, (void *)"PROS", TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "PP Task");
	double smooth = 0.75;
	// Enable Base
	enableBase(true, true);

	// Skills
	// First Roller
	baseMove(-5);
	waitPP(700);
	Intake.move(100);
	delay(300);
	Intake.move(0);
	delay(50);

	// Second Roller
	basePP({position, Node(10, 15)}, 1 - smooth, smooth, 12);
	waitPP(2000);
	Intake.move(127);
	baseTurn(90);
	waitTurn(2000);
	baseMove(-35);
	waitPP(2000);
	Intake.move(0);
	// delay(300);
	// drive(30, 30);
	// Intake.move(100);
	// delay(700);
	// Intake.move(0);
	// drive(0, 0);

	// Triple Shot
	basePP({position, Node(-18, 75)}, 1 - smooth, smooth, 12);
	waitPP(3000);

	//
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

		if (FWSwitch)
		{
			MoveFW(2985, 0.035078, 0.035, 0.00025, 0.000007); // Triple
			// MoveFW(3537, 0.034389, 0.029, 0.0019, 0.00002); //lONG SHOT
			// MoveFW(3314); //Middle Shots

			// printf("i luv lulu tan\n");
		}
		else if (FWSwitch == false)
		{
			FW.move(0);
		}

		// MoveFW(3570, 0.02535, 0.001661, 0.00001); Long Shot
		// MoveFW(3310); Middle Shots

		// Triple Shot
		if (Master.get_digital_new_press(DIGITAL_R2))
		{
			printf("Shot\n");
			piston.set_value(HIGH);
			delay(50);
			piston.set_value(LOW);
			delay(400);
			printf("Shot\n");
			piston.set_value(HIGH);
			delay(50);
			piston.set_value(LOW);
			delay(400);
			printf("Shot\n");
			piston.set_value(HIGH);
			delay(50);
			piston.set_value(LOW);
		}

		// Intake
		if (Master.get_digital(DIGITAL_L1))
		{
			Intake.move(127);
		}
		else if (Master.get_digital(DIGITAL_L2))
		{
			Intake.move(-127);
		}
		else
		{
			Intake.move(0);
		}
		delay(10);
	}
}
