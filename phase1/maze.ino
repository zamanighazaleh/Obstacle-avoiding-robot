#include <AFMotor.h>

int motor_Num_1 = 1;
int motor_Num_2 = 2;
int motor_Num_3 = 3;
int motor_Num_4 = 4;

int sonar_Num_1 = 18;
int sonar_Num_2 = 19;
int sonar_Num_3 = 20;
int sonar_Num_4 = 21;

bool forward = true;
bool backward = true;
bool left = true;
bool right = true;

int speed = 200;

int curent = 0; // 0 -> stop , 1 -> for , 2-> left , 3-> back , 4 -> right

AF_DCMotor motor_1(motor_Num_1);
AF_DCMotor motor_2(motor_Num_2);
AF_DCMotor motor_3(motor_Num_3);
AF_DCMotor motor_4(motor_Num_4);

int find_way(int speed)
{
  
  switch(curent)
  {
    case 1:
      if (backward)
        RobotBackward(speed);
      else if(left)
        RobotLeft(speed);
      else if (right) RobotRight(speed);
      else RobotStop();
      break;
      
    case 2 : 
      if (right)
        RobotRight(speed);
      else if(forward)
        RobotForward(speed);
      else if (backward) RobotBackward(speed);
      else RobotStop();
    
      break;
    case 3 : 
      if (left)
        RobotLeft(speed);
      else if(forward)
        RobotForward(speed);
      else if (right) RobotRight(speed);
      else RobotStop();
      break;

    case 4 : 
      if (forward)
        RobotForward(speed);
      else if(left)
        RobotLeft(speed);
      else if (backward) RobotBackward(speed);
      else RobotStop();
      break;
  }
}

void sonar_1_rise()
{
  if(right)
    right = false;
    else right = true;
  if(curent == 4)
    find_way(speed);

}

void sonar_2_rise()
{
  if(forward)
    forward = false;
  else forward = true;
  if(curent == 1)
  find_way(speed);
}
void sonar_3_rise()
{
  if(backward)
    backward = false;
  else backward = true;
  if(curent == 3)
  find_way(speed);

}
void sonar_4_rise()
{
  if(left)
    left = false;
    else left = true;
    if(curent == 2)
  find_way(speed);

}

/*
void sonar_1_fall()
{
  right = true;
}
void sonar_2_fall()
{
  forward = true;
}
void sonar_3_fall()
{
  backward = true;
}
void sonar_4_fall()
{
  left = true;
}
*/
void setup() 
{
	//Set initial speed of the motor & stop
  int speed = 200;

  pinMode(sonar_Num_1 , INPUT);
  pinMode(sonar_Num_2 , INPUT);
  pinMode(sonar_Num_3 , INPUT);
  pinMode(sonar_Num_4 , INPUT);

  attachInterrupt(digitalPinToInterrupt(sonar_Num_1),sonar_1_rise,CHANGE); 
  attachInterrupt(digitalPinToInterrupt(sonar_Num_2),sonar_2_rise,CHANGE); 
  attachInterrupt(digitalPinToInterrupt(sonar_Num_3),sonar_3_rise,CHANGE); 
  attachInterrupt(digitalPinToInterrupt(sonar_Num_4),sonar_4_rise,CHANGE); 

 // attachInterrupt(digitalPinToInterrupt(sonar_Num_1),sonar_1_fall,FALLING); 
  //attachInterrupt(digitalPinToInterrupt(sonar_Num_2),sonar_2_fall,FALLING); 
  //attachInterrupt(digitalPinToInterrupt(sonar_Num_3),sonar_3_fall,FALLING); 
  //attachInterrupt(digitalPinToInterrupt(sonar_Num_4),sonar_4_fall,FALLING); 

  motor_1.setSpeed(speed);
  motor_2.setSpeed(speed);
  motor_3.setSpeed(speed);
  motor_4.setSpeed(speed);


	motor_1.run(RELEASE);
  motor_2.run(RELEASE);
	motor_3.run(RELEASE);
	motor_4.run(RELEASE);

  RobotForward(speed);

}

void RobotBackward(int speed)
{
  curent = 3;

  motor_1.setSpeed(speed);
  motor_2.setSpeed(speed);
  motor_3.setSpeed(speed);
  motor_4.setSpeed(speed);


  motor_1.run(RELEASE);
  motor_2.run(RELEASE);
  motor_3.run(RELEASE);
  motor_4.run(RELEASE);


  motor_1.run(RELEASE);
  motor_2.run(FORWARD);
  motor_3.run(BACKWARD);
  motor_4.run(RELEASE);
}


void RobotLeft(int speed)
{
  curent = 2;
  motor_1.setSpeed(speed);
  motor_2.setSpeed(speed);
  motor_3.setSpeed(speed);
  motor_4.setSpeed(speed);


  motor_1.run(RELEASE);
  motor_2.run(RELEASE);
  motor_3.run(RELEASE);
  motor_4.run(RELEASE);


  motor_1.run(FORWARD);
  motor_2.run(RELEASE);
  motor_3.run(RELEASE);
  motor_4.run(BACKWARD);
}

void RobotRight(int speed)
{
  curent = 4;

  motor_1.setSpeed(speed);
  motor_2.setSpeed(speed);
  motor_3.setSpeed(speed);
  motor_4.setSpeed(speed);


  motor_1.run(RELEASE);
  motor_2.run(RELEASE);
  motor_3.run(RELEASE);
  motor_4.run(RELEASE);


  motor_1.run(BACKWARD);
  motor_2.run(RELEASE);
  motor_3.run(RELEASE);
  motor_4.run(FORWARD);
}

void RobotForward(int speed)
{
  curent = 1;
  motor_1.setSpeed(speed);
  motor_2.setSpeed(speed);
  motor_3.setSpeed(speed);
  motor_4.setSpeed(speed);


  motor_1.run(RELEASE);
  motor_2.run(RELEASE);
  motor_3.run(RELEASE);
  motor_4.run(RELEASE);


  motor_1.run(RELEASE);
  motor_2.run(BACKWARD);
  motor_3.run(FORWARD);
  motor_4.run(RELEASE);
}



void RobotStop()
{
  curent = 0;
  motor_1.run(RELEASE);
  motor_2.run(RELEASE);
  motor_3.run(RELEASE);
  motor_4.run(RELEASE);
}

void loop() 
{

}