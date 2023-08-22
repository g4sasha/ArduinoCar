
/*************************************
 *     TIME:2020.10.27
 *     Development Team: Zhiyi Technology Co., Ltd.
 *     RIGHT WHEEL
 * 
 **************************************/
// define IO pin
#define ENA 6
#define IN3 9
#define IN4 11

//init the car
void setup() {
  pinMode(IN3, OUTPUT);     //set IO pin mode OUTPUT
  pinMode(IN4, OUTPUT);
  pinMode(ENA, OUTPUT);
  digitalWrite(ENA, HIGH);  //Enable right motor
}

//mian loop
void loop() {
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);  //left wheel turning forwards
  delay(1000);               //delay 500ms
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);   //left wheel stoped
  delay(1000);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);   //left wheel turning backwards
  delay(1000);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, HIGH);  //left wheel stoped
  delay(1000);
}
