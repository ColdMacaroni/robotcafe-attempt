#pragma config(Motor,  port1,           forwardMotorA,    tmotorNormal, openLoop)
#pragma config(Motor,  port2,           forwardMotorB,    tmotorNormal, openLoop, reversed)
#pragma config(Motor,  port3,           sideMotorA,     tmotorNormal, openLoop)
#pragma config(Motor,  port4,           sideMotorB,     tmotorNormal, openLoop, reversed)
#pragma config(Motor,  port6,           carriageMotor,      tmotorNormal, openLoop)
#pragma config(Motor,  port8,           handMotor,      tmotorNormal, openLoop)
// Alias port to somthing
// fa				1
// sa				3
// fb				2
// sb 			4
// carriage 6
// claw			8

/*   Robot
*  ___________
* | fa     sa |
* |           |
* |           |
* |           |
* |_sb_____fb_|
*/

/* Joysticks
*
*  4+   +1
*   3   2
*/

/*----------------------------------------------------------------------------------------------------*\
|*                           - Dual Joystick Control with Arm - 1 Remote -                            *|
|*                                      ROBOTC on VEX 2.0 Cortex                                      *|
|*                                                                                                    *|
|*  This program uses both the Left and the Right joysticks to run the robot using "tank control".    *|
|*  The Group 6 buttons on the top-right of the VEXnet Joystick are used to raise and lower an arm.   *|
|*                                                                                                    *|
|*                                        ROBOT CONFIGURATION                                         *|
|*    NOTES:                                                                                          *|
|*    1)  Ch1 is the X axis and Ch2 is the Y axis for the RIGHT joystick.                             *|
|*    2)  Ch3 is the Y axis and Ch4 is the X axis for the LEFT joystick.                              *|
|*                                                                                                    *|
|*    MOTORS & SENSORS:                                                                               *|
|*    [I/O Port]              [Name]              [Type]              [Description]                   *|
|*    Motor - Port 2          rightMotor           VEX Motor           Right motor                    *|
|*    Motor - Port 3          leftMotor            VEX Motor           Left motor                     *|
|*    Motor - Port 6          armMotor             VEX Motor           Arm motor                      *|
\*----------------------------------------------------------------------------------------------------*/

//+++++++++++++++++++++++++++++++++++++++++++++| MAIN |+++++++++++++++++++++++++++++++++++++++++++++++

task main()
{
	// Threshhold in case the joystick doesnt stop exactly at centre
	const float threshold = 5.0;
	const float speed = 0.5;

	const float handSpeed = 40.0;
	const float carriageSpeed = 30.0;

	float joyFwdA;
	float joyFwdB;

	float joySidA;
	float joySidB;

	// Main loop
	while(1)
	{
		// Apply the threshold
		joyFwdA = (abs(vexRT[Ch3]) <= threshold) ? 0 : vexRT[Ch3];
		joyFwdB = (abs(vexRT[Ch2]) <= threshold) ? 0 : vexRT[Ch2];

		joySidA = (abs(vexRT[Ch1]) <= threshold) ? 0 : vexRT[Ch1];
		joySidB = (abs(vexRT[Ch4]) <= threshold) ? 0 : vexRT[Ch4];

		//Driving Motor Control
		motor[forwardMotorA] = joyFwdA * speed;
		motor[forwardMotorB] = joyFwdB * speed;

		motor[sideMotorA] = joySidA * speed;
		motor[sideMotorB] = joySidB * speed;

		//Carriage Control
		if(vexRT[Btn8D])
		{
			motor[carriageMotor] = carriageSpeed;
		}
		else if(vexRT[Btn8R])
		{
			motor[carriageMotor] = carriageSpeed * -1;
		}
		else
		{
			motor[carriageMotor] = 0;
		}

		// Hand control
		// I'm not sure which is open and which is close
		if(vexRT[Btn7D])
		{
			motor[handMotor] = handSpeed;
		}
		else if(vexRT[Btn7R])
		{
			motor[handMotor] = handSpeed * -1;
		}
		else
		{
			motor[handMotor] = 0;
		}
	}
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
