
/*************************************
 *     TIME:2020.10.29
 *     Development Team: Zhiyi Technology Co., Ltd.
 *     INFRARED REMOTE CONTROL
 * 
 **************************************/
#include <IRremote.h>

//------- IR REMOTE CODES ---------//
#define FORWARD 0xFF02FD   //16718055  
#define BACK    0xFF9867    //16730805
#define LEFT    0xFFE01F    //16716015
#define RIGHT   0xFF906F    //16734885
#define  STOP   0xFFA857    //16726215
#define Buzzer  0xFF7A85    //16738455
 
#define RECV_PIN  12

#define ENB 5   // Left  wheel speed
#define IN1 7   // Left  wheel forward
#define IN2 8   // Left  wheel reverse
#define IN3 9   // Right wheel reverse
#define IN4 11  // Right wheel forward
#define ENA 6   // Right wheel speed
#define carSpeed 200  // initial speed of car >=0 to <=255
int sound = 15;
//int left_LED = 16;
//int Right_LED = 17;

IRrecv irrecv(RECV_PIN);
decode_results results;
unsigned long val;
unsigned long preMillis;

void forward() {
  digitalWrite(ENA, HIGH);
  digitalWrite(ENB, HIGH);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
//  digitalWrite(left_LED,LOW);
//  digitalWrite(Right_LED,LOW);
  Serial.println("go forward!");
}

void back(){
  digitalWrite(ENA, HIGH);
  digitalWrite(ENB, HIGH);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
//  digitalWrite(left_LED,HIGH);
//  digitalWrite(Right_LED,HIGH);
  Serial.println("go back!");
}

void left(){
  analogWrite(ENA, carSpeed);
  analogWrite(ENB, carSpeed);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH); 
//  digitalWrite(left_LED,LOW);
//  digitalWrite(Right_LED,HIGH);
  Serial.println("go left!");
}

void right(){
  analogWrite(ENA, carSpeed);
  analogWrite(ENB, carSpeed);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
//  digitalWrite(left_LED,HIGH);
//  digitalWrite(Right_LED,LOW);
  Serial.println("go right!");
}

void stop()
{
  digitalWrite(ENA, LOW);
  digitalWrite(ENB, LOW);
  Serial.println("STOP!");
}


/************BLINKSOUND****/
void blinks()
{
 for(int i=0;i<5;i++)
 {
//  digitalWrite(left_LED,HIGH);
//  digitalWrite(Right_LED,HIGH);
  digitalWrite(sound,HIGH);
  delay(500);
//  digitalWrite(left_LED,LOW);
//  digitalWrite(Right_LED,LOW);
  digitalWrite(sound,LOW);
  delay(500); 
 Serial.println("Blink!");
}
delay(1000);
  }
//////////////////////////////////
void setup() {
  Serial.begin(9600);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
//  pinMode(left_LED,OUTPUT);
//  pinMode(Right_LED,OUTPUT);
  pinMode(sound,OUTPUT);
  stop();
  irrecv.enableIRIn();
}
////////////////////////////////
  
void loop() {
  if (irrecv.decode(&results)){ 
    preMillis = millis();
    val = results.value;
    Serial.println(val);
    irrecv.resume();
    switch(val){
      case FORWARD: forward();  break;
      case BACK:    back();     break;
      case LEFT:    left();     break;
      case RIGHT:   right();    break;
      //case STOP:    stop();     break;
      case Buzzer:  blinks();   break;
      default:                  break;
    }
  }
  else{
    if(millis() - preMillis > 500){
      stop();
      preMillis = millis();
    }
  }
}
