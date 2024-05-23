   ////////////////////////////////////////////////////////
  //          Arduino Obstacle Avoiding Robot v2.0      //             
 //            By Aarav Garg - 2021                    //
////////////////////////////////////////////////////////

//including the libraries
#include <AFMotor.h>
#include <NewPing.h>


//defining pins and variables
#define TRIG_PIN A4 
#define ECHO_PIN A5 
#define MAX_DISTANCE 200
#define MAX_SPEED 200 // sets speed of DC  motors
#define MAX_SPEED_OFFSET 20

#define turn_amount 500

//defining motors,servo,sensor
NewPing sonar(TRIG_PIN, ECHO_PIN, MAX_DISTANCE); 
AF_DCMotor motor1(2, MOTOR12_8KHZ); 
AF_DCMotor motor2(1, MOTOR12_8KHZ);
  
//defining global variables
boolean goesForward=false;
int distance = 100;
int speedSet = 0;

void setup() {
  Serial.begin(9600);
  delay(500);
  distance = readPing();
  delay(100);
  // distance = readPing();
  // delay(100);
  // distance = readPing();
  // delay(100);
  // distance = readPing();
  // delay(100);
}

void loop() {
 delay(40);
 Serial.println(distance);
 
 if(distance<=15)
 {
  Serial.println("Object Detected");
  moveStop();
  delay(1000);
  moveBackward();
  delay(1000);
  turnRight();
  delay(1000);
 }
 else
 {
  moveForward();
 }

 //reseting the variable after the operations
 distance = readPing();
}





int readPing() { 
  delay(70);
  int cm = sonar.ping_cm();
  if(cm==0)
  {
    cm = 250;
  }
  return cm;
}

void moveStop() {
  motor1.run(RELEASE); 
  motor2.run(RELEASE);
  } 
  
void moveForward() {

 if(!goesForward)
  {
    goesForward=true;
    motor1.run(FORWARD);      
    motor2.run(FORWARD);      
   for (speedSet = 0; speedSet < MAX_SPEED; speedSet +=2) // slowly bring the speed up to avoid loading down the batteries too quickly
   {
    motor1.setSpeed(speedSet + 20);
    motor2.setSpeed(speedSet);
    delay(5);
   }
  }
}

void moveBackward() {
    goesForward=false;
    motor1.run(BACKWARD);      
    motor2.run(BACKWARD);  
  for (speedSet = 0; speedSet < MAX_SPEED; speedSet +=2) // slowly bring the speed up to avoid loading down the batteries too quickly
  {
    motor1.setSpeed(speedSet + 20);
    motor2.setSpeed(speedSet);
    delay(5);
  }
}  

void turnRight() {
  Serial.println("Turning Right");
  motor1.run(FORWARD);
  motor2.run(BACKWARD);     
  delay(1600);
  motor1.run(FORWARD);      
  motor2.run(FORWARD);      
} 
 

