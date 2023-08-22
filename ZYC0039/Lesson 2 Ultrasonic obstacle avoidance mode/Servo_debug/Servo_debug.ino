/*************************************
 *     TIME:2020.10.27
 *     Development Team: Zhiyi Technology Co., Ltd.
 *     Servo
 * 
 **************************************/
#include <Servo.h>
Servo myservo;

void setup(){
  myservo.attach(3);
  myservo.write(90);// move servos to center position -> 90°
} 
void loop(){

}
