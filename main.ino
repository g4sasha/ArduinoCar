#include <Servo.h>
#define servoPin 3

#define hcTrigPin 5
#define hcEchoPin 4

#define leftAxisEnable    5
#define leftAxisFront     7
#define leftAxisBack      8

#define rightAxisEnable   6
#define rightAxisFront    9
#define rightAxisBack     11

Servo servo;

long r_range = 0;
long l_range = 0;
long dst;

bool debug = false;

// При обращении к ней мы получаем расстояние в сантиметрах
long getDistance()
{
   long duration, distance;
   
   digitalWrite(hcTrigPin, LOW);
   delayMicroseconds(2);
   digitalWrite(hcTrigPin, HIGH);
   delayMicroseconds(10);
   digitalWrite(hcTrigPin, LOW);
   
   duration = pulseIn(hcEchoPin, HIGH);
   distance = duration / 58;
   
   return distance;
}

void setup()
{
  servo.attach(servoPin);
  
  pinMode(hcTrigPin, OUTPUT);
  pinMode(hcEchoPin, INPUT);

  pinMode(rightAxisEnable, OUTPUT);
  pinMode(rightAxisFront, OUTPUT);
  pinMode(rightAxisBack, OUTPUT);
  
  pinMode(leftAxisEnable, OUTPUT);
  pinMode(leftAxisFront, OUTPUT);
  pinMode(leftAxisBack, OUTPUT);

  digitalWrite(rightAxisEnable, HIGH);
  digitalWrite(leftAxisEnable, HIGH);

  Serial.begin(9600);

  servo.write(90);
  delay(1000);

  if(debug)
  {
    Serial.println("debug on!");
  }
}

void loop()
{
  if(!debug)
  {
    // Смотрим направо и измеряем расстояние
    servo.write(0);
    delay(500);
    r_range = getDistance();
    delay(500);
  
    // Смотрим налево и измеряем расстояние
    servo.write(180);
    delay(500);
    l_range = getDistance();
    delay(500);

    servo.write(90);

    Serial.println("Right: " + String(r_range));
    Serial.println("Left: " + String(l_range));
    
    delay(500);
  
    if(r_range > l_range)
    {
      Serial.println("carRight");
      carRight();
      delay(360);
      carStop();
    }
  
    if(r_range <= l_range)
    {
      Serial.println("carLeft");
      carLeft();
      delay(360);
      carStop();
    }

    Serial.println("Go!");
    dst = getDistance();
    while(dst >= 20)
    {
      dst = getDistance();
      carFront();
    }

    Serial.println("Stop!");

    carStop();
    delay(500);
  }

  else
  {
    carRight();
    delay(2000);
    carLeft();
    delay(2000);
  }
}

void carStop()
{
  digitalWrite(rightAxisFront, LOW);
  digitalWrite(rightAxisBack, LOW);
  digitalWrite(leftAxisFront, LOW);
  digitalWrite(leftAxisBack, LOW);
}

void carRight()
{
  carStop();
  digitalWrite(rightAxisFront, LOW);
  digitalWrite(rightAxisBack, HIGH);
  digitalWrite(leftAxisFront, HIGH);
  digitalWrite(leftAxisBack, LOW);
}

void carLeft()
{
  carStop();
  digitalWrite(rightAxisFront, HIGH);
  digitalWrite(rightAxisBack, LOW);
  digitalWrite(leftAxisFront, LOW);
  digitalWrite(leftAxisBack, HIGH);
}

void carBack()
{
  carStop();
  digitalWrite(rightAxisFront, LOW);
  digitalWrite(rightAxisBack, HIGH);
  digitalWrite(leftAxisFront, LOW);
  digitalWrite(leftAxisBack, HIGH);
}

void carFront()
{
  carStop();
  digitalWrite(rightAxisFront, HIGH);
  digitalWrite(rightAxisBack, LOW);
  digitalWrite(leftAxisFront, HIGH);
  digitalWrite(leftAxisBack, LOW);
}
