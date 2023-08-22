/*************************************
 *     TIME:2020.10.27
 *     Development Team: Zhiyi Technology Co., Ltd.
 *     OBSTACLE AVOIDANCE CAR
 * 
 **************************************/
#include <Servo.h>  //servo library
Servo myservo;      // create servo object to control servo

int Echo = A4;
int Trig = A5;
int sound = 15;


#define ENA  5 
#define ENB  6       
#define IN1  7      
#define IN2  8    
#define IN3  9    
#define IN4  11   
  

#define carSpeed 150

int rightDistance = 0, leftDistance = 0, middleDistance = 0;

void forward(){
  analogWrite(ENA, carSpeed);
  analogWrite(ENB, carSpeed);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);

  Serial.println("Forward");
}

void back() {
  analogWrite(ENA, carSpeed);
  analogWrite(ENB, carSpeed);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  Serial.println("Back");
}

void left() {
  analogWrite(ENA, carSpeed);
  analogWrite(ENB, carSpeed);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);

  Serial.println("Left");
}

void right() {
  analogWrite(ENA, carSpeed);
  analogWrite(ENB, carSpeed);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);

  Serial.println("Right");
}

void stop() {
  digitalWrite(ENA, LOW);
  digitalWrite(ENB, LOW);
  Serial.println("Stop!");
}



int Distance_test() {
  digitalWrite(Trig, LOW);   
  delayMicroseconds(2);
  digitalWrite(Trig, HIGH);  
  delayMicroseconds(20);
  digitalWrite(Trig, LOW);   
  float Fdistance = pulseIn(Echo, HIGH);  
  Fdistance= Fdistance / 58;       
  return (int)Fdistance;
}  

/************BLINKSOUND****/
void blinks()
{
 for(int i=0;i<5;i++)
 {
//  digitalWrite(left_LED,HIGH);
//  digitalWrite(Right_LED,HIGH);
  digitalWrite(sound,HIGH);
  delay(100);

  digitalWrite(sound,LOW);
  delay(100); 
 Serial.println("Blink!");
}
delay(150);
  }



void setup() {
  myservo.attach(3,700,2400);  // attach servo on pin 3 to servo object
  Serial.begin(9600);
  pinMode(Echo, INPUT);
  pinMode(Trig, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);

  pinMode(sound,OUTPUT);
  stop();
}

void loop() {
    myservo.write(90);  //setservo position according to scaled value
    delay(500);
    middleDistance = Distance_test();//getDistance();

    if(middleDistance <= 40) {
      stop();
      delay(500);
      myservo.write(10);
      delay(1000);
      rightDistance = Distance_test();//getDistance();

      delay(500);
      myservo.write(90);
      delay(1000);
      myservo.write(180);
      delay(1000);
      leftDistance = Distance_test();//getDistance();

      delay(500);
      myservo.write(90);
      delay(1000);
     
      
      if(rightDistance > leftDistance) {
          right(); 
        delay(360);
      }
      else if(rightDistance < leftDistance) {
     left(); 
        delay(360);
      }
      else if((rightDistance <= 45) || (leftDistance <= 45)) {
        
        back();
        blinks();
       delay(180);
      }
      else {
        forward();
      }
    }
    else {
        forward();
    }
}
