//2020.12.10

//Control board pin definition
int motor_L_ENA = 5; //The left motor control terminal is connected to pins 5, 7, and 8 of the Arduino board
int motor_L_IN1 = 7;
int motor_L_IN2 = 8;
int motor_R_ENB = 6; //The right motor control end is connected to pins 6,9 and 11 of the Arduino board
int motor_R_IN3 = 9;
int motor_R_IN4 = 11;

int infrared_L = A0;  //The left infrared sensor is connected to the A0 pin of the Arduino board
int infrared_M = A2;  //The mid-side infrared sensor is connected to the A2 pin of the Arduino board
int infrared_R = A3;  //The right infrared sensor is connected to the A3 pin of the Arduino board

int sensor_L = 1;  //The detection value of the left infrared sensor, the default value is 1, outside the black line
int sensor_M = 1;  //The detection value of the middle infrared sensor, the default value is 1, is on the black line
int sensor_R = 1;  //The detection value of the infrared sensor on the right, the default value is 1, outside the black line
int low_speed = 200;  //The setting of high speed and low speed when turning left and right can be adjusted
int high_speed = 200;

//Subfunction definition
void go_forward_high_speed()   //The car ahead
{
  analogWrite(motor_L_ENA, high_speed);  //The left motor is running forward
  digitalWrite(motor_L_IN1, 1);
  digitalWrite(motor_L_IN2, 0);

  analogWrite(motor_R_ENB,high_speed);   //Right motor forward
  digitalWrite(motor_R_IN3, 1);
  digitalWrite(motor_R_IN4, 0);
}

void stop_with_brake()  //The car brake
{
  digitalWrite(motor_L_ENA, 0);  //Left motor braking
  digitalWrite(motor_L_IN1, 0);
  digitalWrite(motor_L_IN2, 0) ;

  digitalWrite(motor_R_ENB, 0);  //Right motor braking
  digitalWrite(motor_R_IN3, 0);
  digitalWrite(motor_R_IN4, 0) ;
}

void go_forward_left()  //The car left
{
  digitalWrite(motor_L_IN1, 1);
  digitalWrite(motor_L_IN2, 0);
  analogWrite(motor_L_ENA, low_speed); //Revolver at low speed

  digitalWrite(motor_R_IN3, 0);
  digitalWrite(motor_R_IN4, 1);
  analogWrite(motor_R_ENB, high_speed);  //Right round the
}

void go_forward_right()  //The car turn right
{
  digitalWrite(motor_L_IN1, 0);
  digitalWrite(motor_L_IN2, 1);
  analogWrite(motor_L_ENA, high_speed); //Revolver high-speed

  digitalWrite(motor_R_IN3, 1);
  digitalWrite(motor_R_IN4, 0);
  analogWrite(motor_R_ENB, low_speed);  //The right wheel low speed
}


void setup()
{
  pinMode(motor_L_ENA, OUTPUT); //Left motor enabler and PWM port
  pinMode(motor_L_IN1, OUTPUT);  //Left motor control port 1
  pinMode(motor_L_IN2, OUTPUT);  //Left motor control port 2
  pinMode(motor_R_ENB, OUTPUT); //Right motor enable and PWM speed control port
  pinMode(motor_R_IN3, OUTPUT);  //Right motor control port 3
  pinMode(motor_R_IN4, OUTPUT);  //Left motor control port 4

  pinMode(infrared_L, INPUT);  //Left infrared sensor
  pinMode(infrared_M, INPUT);  //Intermediate infrared sensor
  pinMode(infrared_R, INPUT);  //Right infrared sensor
}

void loop()
{
  sensor_L=digitalRead(infrared_L);
  sensor_M=digitalRead(infrared_M);
  sensor_R=digitalRead(infrared_R);

  if( sensor_M==1)  //The car is on the black line
  {  
    go_forward_high_speed();   //go forward
  }

if(sensor_L==1)  //The car left
  {
  
    go_forward_left();   //Turn left for 100 milliseconds, the time can be adjusted
    delay(100);
  } 

if(sensor_R==1)  //The car right
  {
   
     go_forward_right();  //Car right turn 100 milliseconds, the time can be adjusted
    delay(100);
  }
if(sensor_R&&sensor_L==1)  //The car ahead
  {

    go_forward_high_speed();   //go forward  
    
    delay(100);//Car right turn 100 milliseconds, the time can be adjusted
  }
if(sensor_R&&sensor_M==1)  //Trolley braid right
  {
     go_forward_right();  //Car right turn 100 milliseconds, the time can be adjusted
      
      delay(100);   
    
  }

if(sensor_L&&sensor_M==1)  //Trolley knitting left side
  {
      go_forward_left();  //Turn left for 100 milliseconds, the time can be adjusted
      
      delay(100);   
    
  }
if(sensor_L&&sensor_M&&sensor_R==1)  //The car is on the stop line
  {
     stop_with_brake();  //Brake 2 seconds,
 
     delay(2000);
    
  }
}
