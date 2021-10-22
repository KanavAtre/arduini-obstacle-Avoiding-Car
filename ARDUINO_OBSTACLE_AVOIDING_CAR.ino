
#include <AFMotor.h>  
#include <NewPing.h>

#define TRIG_PIN A0
#define ECHO_PIN A1
#define MAX_DISTANCE 200 
#define MAX_SPEED 190 // sets speed of DC  motors
#define MAX_SPEED_OFFSET 20

NewPing sonar(TRIG_PIN, ECHO_PIN, MAX_DISTANCE); 

AF_DCMotor motor1(1, MOTOR12_1KHZ); 
AF_DCMotor motor3(3, MOTOR34_1KHZ);

//myservo.write(20);
boolean goesForward=false;
int distance = 100;
int speedSet = 0;

void setup() {

  delay(2000);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);

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

void loop() {
 int distanceR = 0;
 int distanceL =  0;
 delay(40);
 
 if(distance<=15)
 {
  moveStop();
  delay(100);
  moveBackward();
  delay(300);
  moveStop();
  delay(200);
  distanceR = lookRight();
  Serial.println(distanceR);
  delay(200);
  distanceL = lookLeft();
  Serial.println(distanceL);
  delay(200);

  if(distanceR>=distanceL)
  {
    turnRight();
    moveStop();
  }else
  {
    turnLeft();
    moveStop();
  }
 }else
 {
  moveForward();
 }
 distance = readPing();
 Serial.println(distance);
}

int lookRight()
{
    motor3.run(BACKWARD);
    motor1.run(FORWARD); 
    delay(500);
    int distance = readPing();
    delay(100);
    motor1.run(BACKWARD);
    motor3.run(FORWARD);
    delay(500);
    return distance;
}

int lookLeft()
{
    motor3.run(FORWARD);
    motor1.run(BACKWARD); 
    delay(500);
    int distance = readPing();
    delay(100);
    motor1.run(FORWARD);
    motor3.run(BACKWARD);
    delay(500);
    return distance;
}

void moveStop() {
  motor1.run(RELEASE); 

  motor3.run(RELEASE);
  } 
  
void moveForward() {

 if(!goesForward)
  {
    goesForward=true;
    motor1.run(FORWARD);       
    motor3.run(FORWARD);     
   for (speedSet = 0; speedSet < MAX_SPEED; speedSet +=2) // slowly bring the speed up to avoid loading down the batteries too quickly
   {
    motor1.setSpeed(speedSet);
    motor3.setSpeed(speedSet);
    delay(5);
   }
  }
}

void moveBackward() {
    goesForward=false;  
    motor1.run(BACKWARD);      
    motor3.run(BACKWARD);  
  for (speedSet = 0; speedSet < MAX_SPEED; speedSet +=2) // slowly bring the speed up to avoid loading down the batteries too quickly
  {
    motor1.setSpeed(speedSet);
    motor3.setSpeed(speedSet);
    delay(5);
  }
}  

void turnRight() {
  motor1.run(FORWARD);
  motor3.run(BACKWARD);     
  delay(500);
  motor1.run(FORWARD);      
  motor3.run(FORWARD);      
} 
 
void turnLeft() {
  motor1.run(BACKWARD);     
  motor3.run(FORWARD);   
  delay(500);
  motor1.run(FORWARD);     
  motor3.run(FORWARD);
}  
