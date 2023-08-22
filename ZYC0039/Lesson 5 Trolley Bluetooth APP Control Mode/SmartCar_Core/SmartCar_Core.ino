/*************************************
 *     TIME:2020.10.27
 *     Development Team: Zhiyi Technology Co., Ltd.
 *       Bluetooth infrared remote control car
 * 
 **************************************/

#include <IRremote.h>
#include <Servo.h>  

#define A 0xFF02FD   // FORWARD 
#define B 0xFF9867   // BACK
#define C 0xFFE01F  // LEFT
#define D 0xFF906F  // RIGHT
#define F 0xFFA857  // STOP
#define KEY1 16753245 
#define KEY2 16736925 
#define KEY3 16769565
#define KEY4 16720605
#define KEY5 16712445
#define KEY6 16761405
#define KEY7 16769055
#define KEY8 16754775
#define KEY9 16748655
#define KEY0 0xFF7A85      //music
#define KEY_STAR 0xFF30CF  //Line Teacking mode
#define KEY_HASH 0xFF18E7  //Obstacles Avoidance mode

#define RECV_PIN  12
#define ECHO_PIN  A4  
#define TRIG_PIN  A5 
#define ENA 5
#define ENB 6
#define IN1 7
#define IN2 8
#define IN3 9
#define IN4 11
#define LED_Pin 13
#define LineTeacking_Pin_Right  A0   //10
#define LineTeacking_Pin_Middle A2   //4
#define LineTeacking_Pin_Left   A3   //2
#define LineTeacking_Read_Right   digitalRead(A0)
#define LineTeacking_Read_Middle  digitalRead(A2)
#define LineTeacking_Read_Left    digitalRead(A3)
#define carSpeed 200
int left_LED = 16;     //led
int Right_LED = 17;    //led
int speakerPin = 15;         //Define the buzzer pin
int length = 15;            //音符数量
char notes[] = "ccggaagffeeddc "; // 空格代表休息
int beats[] = { 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 2, 4 };
int tempo = 300;
//**************Music function****************//

void playTone(int tone, int duration) {
  for (long i = 0; i < duration * 1000L; i += tone * 2)
  {
    digitalWrite(speakerPin, HIGH);
    delayMicroseconds(tone);
    digitalWrite(speakerPin, LOW);
    delayMicroseconds(tone);
  }
}
void playNote(char note, int duration) {
  char names[] = { 'c', 'd', 'e', 'f', 'g', 'a', 'b', 'C' };
  int tones[] = { 1915, 1700, 1519, 1432, 1275, 1136, 1014, 956 };
  
  //播放与音符名称对应的音调
  for (int i = 0; i < 8; i++) {
    if (names[i] == note) {
      playTone(tones[i], duration);
    }
  }
}

/*****蜂鸣器播放小星星******/
void sound() 
{
  for (int i = 0; i < length; i++) {
    if (notes[i] == ' ') {
      delay(beats[i] * tempo); // rest
    } else {
      playNote(notes[i], beats[i] * tempo);
    }
  
    // pause between notes
    delay(tempo / 2); 
  }
}
Servo servo;
IRrecv irrecv(RECV_PIN);
decode_results results;
unsigned long IR_PreMillis;
unsigned long LT_PreMillis;
int rightDistance = 0, leftDistance = 0, middleDistance = 0;

enum FUNCTIONMODE{
  IDLE,
  LineTeacking,
  ObstaclesAvoidance,
  Bluetooth,
  IRremote
} func_mode = IDLE;

enum MOTIONMODE {
  STOP,
  FORWARD,
  BACK,
  LEFT,
  Music,
  RIGHT
} mov_mode = STOP;

void delays(unsigned long t) {
  for(unsigned long i = 0; i < t; i++) {
    getBTData();
    getIRData();
    delay(1);
  }
}

int getDistance() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  return (int)pulseIn(ECHO_PIN, HIGH) / 58;
}

//*************音乐
void music(bool debug = false)
{ 

 sound();
 digitalWrite(left_LED,LOW);
 digitalWrite(Right_LED,LOW);
 delay(1000);
 digitalWrite(left_LED,LOW);
 digitalWrite(Right_LED,LOW);
 delay(1000);
  if(debug) Serial.println("Go music!");
}


void forward(bool debug = false){ 
 analogWrite(ENA, carSpeed);
 analogWrite(ENB, carSpeed);
 digitalWrite(IN1,HIGH);
 digitalWrite(IN2,LOW);
 digitalWrite(IN3,HIGH);
 digitalWrite(IN4,LOW);
 digitalWrite(left_LED,LOW);
 digitalWrite(Right_LED,LOW);
  if(debug) Serial.println("Go forward!");
}


void back(bool debug = false){
  analogWrite(ENA, carSpeed);
  analogWrite(ENB, carSpeed);
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,HIGH);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,HIGH);
  digitalWrite(left_LED,HIGH);
  digitalWrite(Right_LED,HIGH);
  if(debug) Serial.println("Go back!");
}

void left(bool debug = false){
  analogWrite(ENA,carSpeed);
  analogWrite(ENB,carSpeed);
  digitalWrite(IN1,HIGH);
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,HIGH); 
  digitalWrite(left_LED,LOW);
  digitalWrite(Right_LED,HIGH);
  if(debug) Serial.println("Go left!");
}

void right(bool debug = false){
  analogWrite(ENA,carSpeed);
  analogWrite(ENB,carSpeed);
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,HIGH);
  digitalWrite(IN3,HIGH);
  digitalWrite(IN4,LOW);
  digitalWrite(left_LED,HIGH);
  digitalWrite(Right_LED,LOW);
  if(debug) Serial.println("Go right!");
}

void stop(bool debug = false){
  digitalWrite(ENA, LOW);
  digitalWrite(ENB, LOW);
  if(debug) Serial.println("Stop!");
}
void getBTData() {
  if(Serial.available()) {
    switch(Serial.read()) {
      case 'A': func_mode = Bluetooth; mov_mode = FORWARD;  break;
      case 'B': func_mode = Bluetooth; mov_mode = BACK;     break;
      case 'C': func_mode = Bluetooth; mov_mode = LEFT;     break;
      case 'D': func_mode = Bluetooth; mov_mode = RIGHT;    break;
      case 'F': func_mode = Bluetooth; mov_mode = STOP;     break;
      case '1': func_mode = LineTeacking;                   break;
      case '2': func_mode = ObstaclesAvoidance;             break;
      case '3': func_mode = Bluetooth; mov_mode = Music;  break;   
      default:  break;
    } 
  }
}

void getIRData() {
  if (irrecv.decode(&results)){ 
    IR_PreMillis = millis();
    switch(results.value){
      case A:   func_mode = IRremote; mov_mode = FORWARD;  break;
      case B:   func_mode = IRremote; mov_mode = BACK;     break;
      case C:   func_mode = IRremote; mov_mode = LEFT;     break;
      case D:   func_mode = IRremote; mov_mode = RIGHT;    break;
      case F:   func_mode = IRremote; mov_mode = STOP;     break;
      case KEY_STAR:  func_mode = LineTeacking;                break;
      case KEY_HASH:  func_mode = ObstaclesAvoidance;          break;
      case KEY0:   func_mode = IRremote; mov_mode =  Music;     break;
      default: break;
    }
    irrecv.resume();
  }
}

void bluetooth_mode() {
  if(func_mode == Bluetooth){
    switch(mov_mode){
      case FORWARD: forward();  break;
      case BACK:    back();     break;
      case LEFT:    left();     break;
      case RIGHT:   right();    break;
      case STOP:    stop();     break;
      case Music:   music();     break;
      default: break;
    }
  }
}

void irremote_mode() {
  if(func_mode == IRremote){
    switch(mov_mode){
      case FORWARD: forward();  break;
      case BACK:    back();     break;
      case LEFT:    left();     break;
      case RIGHT:   right();    break;
      case STOP:    stop();     break;
      case Music:  music();    break;
      default: break;
    }
    if(millis() - IR_PreMillis > 500){
      mov_mode = STOP;
      IR_PreMillis = millis();
    }
  }   
}

void line_teacking_mode()
{
  if(func_mode == LineTeacking){
    if(LineTeacking_Read_Middle){
      forward();
      LT_PreMillis = millis();
    } else if(LineTeacking_Read_Right){ 
      //right();
      left();
      while(LineTeacking_Read_Right) {
        getBTData();
        getIRData();
      }
      LT_PreMillis = millis();
    } else if(LineTeacking_Read_Left) {
      //left();
       right();
      while(LineTeacking_Read_Left) {
        getBTData();
        getIRData();
      }
      LT_PreMillis = millis();
    } else {
      if(millis() - LT_PreMillis > 180){
        stop();
      }
    }
  }  
}

void obstacles_avoidance_mode() {
  if(func_mode == ObstaclesAvoidance){
    servo.write(90);
    delays(500);
    middleDistance = getDistance();
    if(middleDistance <= 45) {
      stop();
      delays(500);
      servo.write(10);
      delays(1000);
      rightDistance = getDistance();
      
      delays(500);
      servo.write(90);
      delays(1000);
      servo.write(170);
      delays(1000); 
      leftDistance = getDistance();
      
      delays(500);
      servo.write(90);
      delays(1000);
      if(rightDistance > leftDistance) {
        right();
        delays(360);
      } else if(rightDistance < leftDistance) {
        left();
        delays(360);
      } else if((rightDistance <= 45) || (leftDistance <= 45)) {
        back();
        delays(180);
      } else {
        forward();
      }
    } else {
        forward();
    }  
  }  
}

void setup() {
  Serial.begin(9600);
  servo.attach(3,500,2400);// 500: 0 degree  2400: 180 degree
  servo.write(90);
  irrecv.enableIRIn();
  pinMode(ECHO_PIN, INPUT);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(left_LED,OUTPUT);
  pinMode(Right_LED,OUTPUT);
  pinMode(LineTeacking_Pin_Right, INPUT);
  pinMode(LineTeacking_Pin_Middle, INPUT);
  pinMode(LineTeacking_Pin_Left, INPUT);
  pinMode(speakerPin,OUTPUT);//音乐
}

void loop() {
  getBTData();
  getIRData();
  bluetooth_mode();
  irremote_mode();
  line_teacking_mode();
  obstacles_avoidance_mode();
}
