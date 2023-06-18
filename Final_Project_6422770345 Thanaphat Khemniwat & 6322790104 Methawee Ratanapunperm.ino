//Final_Project_6422770345 Thanaphat Khemniwat & 6322790104 Methawee Ratanapunperm
#define Thanaphat_Khemniwat 6422770345 //Easter Egg, This line can be comment.
#define Methawee_Ratanapunperm 6322790104 //Easter Egg, This line can be comment.
//-----------------------------------------
#include <Servo.h>          //Servo motor library. This is standard library
#include <NewPing.h>        //Ultrasonic sensor function library. You must install this library
//-----------------------------------------
//our L298N control pins
const int LeftMotorForward = 6;
const int LeftMotorBackward = 9;
const int RightMotorForward = 5;
const int RightMotorBackward = 3;
//-----------------------------------------
//sensor pins
#define trig_pin A2 //analog input 2
#define echo_pin A1 //analog input 1
#define maximum_distance 200
NewPing sonar(trig_pin, echo_pin, maximum_distance); //sensor function
//-----------------------------------------
boolean goesForward = false;
//-----------------------------------------
Servo servo_motor; //our servo name
int distance = 100;
//-----------------------------------------
void setup(){

  pinMode(RightMotorForward, OUTPUT);
  pinMode(LeftMotorForward, OUTPUT);
  pinMode(LeftMotorBackward, OUTPUT);
  pinMode(RightMotorBackward, OUTPUT);
  servo_motor.attach(10); //our servo pin
  servo_motor.write(115);
  distance = readPing();
}
//-----------------------------------------
void loop(){

  int distanceRight = 0;
  int distanceLeft = 0;
  delay(50);

  if (distance <= 40){
    moveStop();
    delay(300);
    moveBackward();
    delay(400);
    moveStop();
    delay(300);
    distanceRight = lookRight();
    delay(300);
    distanceLeft = lookLeft();
    delay(300);

    if (distanceRight >= distanceLeft){
      turnRight();
      moveStop();
    }
    else{
      turnLeft();
      moveStop();
    }
  }
  else{
      moveForward(); 
  }
    distance = readPing();
}
//-----------------------------------------
int lookRight(){  
  servo_motor.write(50);
  delay(500);
  int distance = readPing();
  delay(100);
  servo_motor.write(115);
  return distance;
}

int lookLeft(){
  servo_motor.write(170);
  delay(500);
  int distance = readPing();
  delay(100);
  servo_motor.write(115);
  return distance;
  delay(100);
}
//-----------------------------------------
int readPing(){
  delay(70);
  int cm = sonar.ping_cm();
  Serial.print("cm = ");
  Serial.println(cm);
  if (cm==0){
    cm=250;
  }
  return cm;
}
//-----------------------------------------
void moveStop(){

  analogWrite(RightMotorForward, LOW);
  analogWrite(LeftMotorForward, LOW);
  analogWrite(RightMotorBackward, LOW);
  analogWrite(LeftMotorBackward, LOW);
}
//-----------------------------------------

void moveForward(){

  if(!goesForward){

    goesForward=true;
    
    analogWrite(LeftMotorForward, 100);
    analogWrite(RightMotorForward, 100);
  
    analogWrite(LeftMotorBackward, LOW);
    analogWrite(RightMotorBackward, LOW); 
  }
}
void moveBackward(){

  goesForward=false;

  analogWrite(LeftMotorBackward, 100);
  analogWrite(RightMotorBackward, 100);
  
  analogWrite(LeftMotorForward, LOW);
  analogWrite(RightMotorForward, LOW);
  
}
//-----------------------------------------

void turnRight(){

  analogWrite(LeftMotorForward, 100);
  analogWrite(RightMotorBackward, 100);
  
  analogWrite(LeftMotorBackward, LOW);
  analogWrite(RightMotorForward, LOW);
  
  delay(500);
}

void turnLeft(){

  analogWrite(LeftMotorBackward, 100);
  analogWrite(RightMotorForward, 100);
  
  analogWrite(LeftMotorForward, LOW);
  analogWrite(RightMotorBackward, LOW);

  delay(500);
}
//-----------------------------------------