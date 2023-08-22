/*************************************
 *          TIME:2020.10.27
 *  Development Team: Zhiyi Technology Co., Ltd.
 *         
 *          
 **************************************/

//define L298n module IO Pin
#define ENA 5
#define ENB 6
#define IN1 7
#define IN2 8
#define IN3 9
#define IN4 11

void forward(){ 
  digitalWrite(ENA,HIGH); //enable L298n A channel
  digitalWrite(ENB,HIGH); //enable L298n B channel
  digitalWrite(IN1,HIGH);
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,HIGH);
  digitalWrite(IN4,LOW); 
 
  
  Serial.println("Forward");//send message to serial monitor
}

void back(){
  digitalWrite(ENA,HIGH);
  digitalWrite(ENB,HIGH);
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,HIGH);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,HIGH);

  Serial.println("Back");
}

void left(){
  digitalWrite(ENA,HIGH);
  digitalWrite(ENB,HIGH);
  digitalWrite(IN1,HIGH);
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,HIGH);
  Serial.println("Left");
}

void right(){
  digitalWrite(ENA,HIGH);
  digitalWrite(ENB,HIGH);
   digitalWrite(IN1,LOW); //set IN1 LOW level
  digitalWrite(IN2,HIGH); //set IN2 HIGH level
  digitalWrite(IN3,HIGH); //set IN3 HIGH level
  digitalWrite(IN4,LOW); //set IN4 LOW level
  Serial.println("Right");
}

//before execute loop() function, 
//setup() function will execute first and only execute once
void setup() {
  Serial.begin(9600); //open serial and set the baudrate
  pinMode(IN1,OUTPUT);//before useing io pin, pin mode must be set first 
  pinMode(IN2,OUTPUT);
  pinMode(IN3,OUTPUT);
  pinMode(IN4,OUTPUT);
  pinMode(ENA,OUTPUT);
  pinMode(ENB,OUTPUT);
}

//Repeat execution
void loop() {
  forward();  //go forward 
  delay(1000);//delay 1000 ms
  back(); //go back    
  delay(1000);
  left(); //turning left  
  delay(1000);
  right(); //turning right 
  delay(1000);
}
