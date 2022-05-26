#include <Servo.h>

Servo servo;  // cream un obiect , putem crea maxim 12 obiecte Servo
//MOTOR A
int enA = 5;
int in1 = 6;
int in2 = 7;

//MOTOR B
int enB = 11;
int in3 = 9;
int in4 = 10;

int curent = 0;

//Senzor Ultrasonic
const int trigPin = 13;
const int echoPin = 12;
int distance;

//Led Pins
int redPin = A5;
int bluePin = A4;
int greenPin = A3; 

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(redPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  digitalWrite(trigPin, LOW);
  servo.attach(4);
}

void loop() {
  int nr=0;
  while(masura()<=25 && nr==0){
      nr=0;
      moveBackward();
      delay(250);
      moveStop();
      delay(100);
      int L=lookLeft();
      int R=lookRight();
        if(lookRight() > lookLeft()){                  
              turnRight();
              delay(250);
               L=lookLeft();
              if(L<25){
                turnRight();
              delay(150);
              }
              moveStop();
              delay(100);
              nr=1;
                       
      }else{
              turnLeft();
              delay(250);
              int R=lookRight();
              if(R<25){
              turnLeft();
              delay(150);
              }
              moveStop();
              delay(100);
              nr=1;
            }
      }
      
    
  
  if(masura()>25){
    moveForward();
    servo.write(90);
  }

}



void moveStop(){
  digitalWrite(enA, LOW);
  digitalWrite(enB, LOW);
  
  analogWrite(bluePin, 0);
  analogWrite(redPin, 255);
  analogWrite(greenPin, 0);
  
}

void moveBackward(){
  digitalWrite(in2, HIGH);
  digitalWrite(in1, LOW);
  digitalWrite(enA, HIGH);

  digitalWrite(in4, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(enB, HIGH);
  
  analogWrite(bluePin, 255);
  analogWrite(redPin, 255);
  analogWrite(greenPin, 0);
}

void moveForward(){
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(enA, HIGH);

  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  digitalWrite(enB, HIGH);

  analogWrite(bluePin, 255);
  analogWrite(redPin, 0);
  analogWrite(greenPin, 255);
}

void turnLeft(){
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  digitalWrite(enB, HIGH);
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(enA, HIGH);

  
  analogWrite(bluePin, 0);
  analogWrite(redPin, 0); 
  analogWrite(greenPin, 255);
}

void turnRight(){
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    digitalWrite(enA, HIGH);
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
    digitalWrite(enB, HIGH);
      
    analogWrite(bluePin, 255);
    analogWrite(redPin, 0); 
    analogWrite(greenPin, 0);
}

int masura(){
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  int duration = pulseIn(echoPin, HIGH);// pulseIn(pin, value) sau pulseIn(pin, value, timestamp) timestamp=microsecunde
  int distance = duration*0.034/2;  
  if(distance<0){distance=0;}
  return distance;
}

int lookRight()
{
    servo.write(45); 
    delay(200); 
    return masura();
}

int lookLeft()
{
    servo.write(125); 
    delay(200);
    return masura();
}
