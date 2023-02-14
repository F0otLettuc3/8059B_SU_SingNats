#include "main.h"

void on_center_button() {}

void initialize()
{

	// INIT Base Motors
	Motor FL(FLPort, E_MOTOR_GEARSET_06, true, E_MOTOR_ENCODER_DEGREES);
	Motor BLU(BLUPort, E_MOTOR_GEARSET_06, false, E_MOTOR_ENCODER_DEGREES);
	Motor BLD(BLDPort, E_MOTOR_GEARSET_06, true, E_MOTOR_ENCODER_DEGREES);
	Motor FR(FRPort, E_MOTOR_GEARSET_06, false, E_MOTOR_ENCODER_DEGREES);
	Motor BRU(BRUPort, E_MOTOR_GEARSET_06, true, E_MOTOR_ENCODER_DEGREES);
	Motor BRD(BRDPort, E_MOTOR_GEARSET_06, false, E_MOTOR_ENCODER_DEGREES);

	// INIT Other Motors
	Motor FW(FWPort, E_MOTOR_GEARSET_06, false, E_MOTOR_ENCODER_DEGREES);
	Motor intake(intakePort, E_MOTOR_GEARSET_06, false, E_MOTOR_ENCODER_DEGREES);
	FW.tare_position();

	// ADIPorts
	ADIDigitalIn limit(limitPort);
	ADIDigitalOut indexer(indexerPort, false);
	ADIDigitalOut expansionR(Exp1,  LOW);
	ADIDigitalOut expansionL(Exp2, LOW);


	// Tasks
	Task sensorTask(sensors, (void *)"PROS", TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "Sensor Task");
	Task FWCtrlTask(FWCtrl, (void *)"PROS", TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "Flywheel Task");
	// Task debugTask(Debug, (void *)"PROS", TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "Debug Task");
	Task odometryTask(Odometry, (void *)"PROS", TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "Odom Task");
	// Task controlTask(PPControl, (void *)"PROS", TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "PP Task");

	
}

void disabled() {
	// Master.print(0,2, "Hello");
}

void competition_initialize() {}

void autonomous()
{

int autoNum = 2;

switch(autoNum){
	case 1: red1(); break;
	case 2: red2(); break;
	case 3: blue1(); break;
	case 4: blue2(); break;
	case 5: skills(); break;
}

//Red 1 is full awp
//Red 2 is partial awp
// Blue 1 is near roller

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
	Controller Partner(E_CONTROLLER_PARTNER);
	ADIDigitalOut piston(indexerPort);
	ADIDigitalOut expansionR(Exp1);
	ADIDigitalOut expansionL(Exp2);
	expansionL.set_value(LOW);
	expansionR.set_value(LOW);


	// Initialise Pneumatic States
	//  piston.set_value(HIGH);

	// Initialise Driver States
	bool Tank = true;
	bool Break = false;
	double left, right;
	FWSwitch = false;


	while (true)
	{
		if (Master.get_digital_new_press(DIGITAL_Y)){Tank = !Tank;}
		if (Master.get_digital_new_press(DIGITAL_DOWN)){Break =!Break;}

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

		FL.move(left);
		BLU.move(left);
		BLD.move(left);
		FR.move(right);
		BRU.move(right);
		BRD.move(right);

		// Triple Shot
		if (Master.get_digital_new_press(DIGITAL_R1)){FWSwitch = !FWSwitch;}

		if (FWSwitch){
			MoveFW(2907, 0.028677777777777777777778, 0.129, 0.0024395, 0.0000090625);
			Master.rumble("-");
			// Master.print(0,2, "Flywheel On ");
		}
		else{
			FW.move(0);
		}


		// Triple Shot
		if (Master.get_digital_new_press(DIGITAL_R2)){Shoot(3,220);}

		// Intake
		if(Master.get_digital(DIGITAL_L1)){Intake.move(127);}
		else if(Master.get_digital(DIGITAL_L2)){Intake.move(-127);}
		else{Intake.move(0);}

		//Expansion
		if(Master.get_digital(DIGITAL_UP) && Master.get_digital(DIGITAL_DOWN)){
			expansionL.set_value(HIGH);
			expansionR.set_value(HIGH);
		}

		if(Partner.get_digital(DIGITAL_UP) && Partner.get_digital(DIGITAL_DOWN)){
			expansionL.set_value(HIGH);
			expansionR.set_value(HIGH);

		}


		delay(10);
	}
}
