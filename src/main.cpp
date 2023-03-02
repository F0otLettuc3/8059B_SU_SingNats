#include "main.h"
#include "Selection.hpp"


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
	ADIDigitalOut expansionR(ExpRight, LOW);
	ADIDigitalOut expansionL(ExpLeft, LOW);
	ADIDigitalOut expansionMid(ExpMid, LOW);


	// Tasks
	Task sensorTask(sensors, (void *)"PROS", TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "Sensor Task");
	Task FWCtrlTask(FWCtrl, (void *)"PROS", TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "Flywheel Task");
	// Task debugTask(Debug, (void *)"PROS", TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "Debug Task");
	Task odometryTask(Odometry, (void *)"PROS", TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "Odom Task");
	// Task controlTask(PPControl, (void *)"PROS", TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "PP Task");

	selector::init();

	
}

void disabled() {
	ADIDigitalOut expansionR(ExpRight, LOW);
	ADIDigitalOut expansionL(ExpLeft, LOW);
	ADIDigitalOut expansionMid(ExpMid, LOW);
}

void competition_initialize() {}

void autonomous()
{

int autoNum = 5;

switch(autoNum){
	case 1: red1(); break;
	case 2: red2(); break;
	case 3: blue1(); break;
	case 4: blue2(); break;
	case 5: skills(); break;
}
// if(selector::auton == 1){red1();}
// if(selector::auton == 2){red2();}
// if(selector::auton == 3){printf("lol");}
// if(selector::auton == -1){blue1();}
// if(selector::auton == -2){blue2();}
// if(selector::auton == -3){printf("lol");}
// if(selector::auton == 0){skills();}




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

	// Controllers
	Controller Master(E_CONTROLLER_MASTER);
	Controller Partner(E_CONTROLLER_PARTNER);

	// Pistons`
	ADIDigitalOut piston(indexerPort);
	ADIDigitalOut expansionR(ExpRight);
	ADIDigitalOut expansionL(ExpLeft);
	ADIDigitalOut expansionMid(ExpMid);
	// expansionL.set_value(LOW);
	// expansionR.set_value(LOW);
	// expansionMid.set_value(LOW);


	// Initialise Driver States
	bool Tank = true;
	bool Break = false;
	double left, right;
	bool firstMatch = false;
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



		// Triple Shot
		if (Master.get_digital_new_press(DIGITAL_R2)){Shoot(3,270);}

		// Intake
		if(Master.get_digital(DIGITAL_L1)){Intake.move(127);}
		else if(Master.get_digital(DIGITAL_L2)){Intake.move(-127);}
		else{Intake.move(0);}

		//Expansion
		if(Master.get_digital(DIGITAL_UP) && Master.get_digital(DIGITAL_DOWN)){Expand();}
		if(Partner.get_digital(DIGITAL_UP) && Partner.get_digital(DIGITAL_DOWN)){Expand();}


		if(Master.get_digital(DIGITAL_RIGHT)){
				firstMatch = !firstMatch;

				if(firstMatch){
					FWSwitch = true;
					if (FWSwitch){MoveFW(2900, 0.0310, 0.2150, 0.009, 0.00001);}					
					delay(1200);
					Shoot(10,550);

	
				}
				else{
					FWSwitch = true;
					delay(100);
					if (FWSwitch){MoveFW(2900, 0.0310, 0.2150, 0.009, 0.00001);}
					Shoot(10,550);
				}
			}

		//Flywheel Controller				
		if (FWSwitch){MoveFW(2900, 0.027, 0.2125, 0.009, 0.00001);Master.rumble("-");}
		else{FW.move(0);}	
		delay(10);
	
		// if(Master.get_digital_new_press(DIGITAL_X)){driverSkills();}
}

}