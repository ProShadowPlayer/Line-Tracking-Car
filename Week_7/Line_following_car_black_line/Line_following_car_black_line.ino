#include <analogWrite.h>
#define trigPin 27
#define echoPin 14

float duration, distance;



// IR SENSOREN

int IRSensor_Binnen_Links = 25;
int IRSensor_Binnen_Rechts = 26;

//MOTOR LINKS
int in1 = 21;
int in2 = 19;
int enA = 33;


//MOTOR RECHTS
int in3 = 18;
int in4 = 5;
int enB = 32;


//LEDS
int led_rood = 4;
int led_geel = 2;
int led_groen = 15;

//TIMER
int counter = 0;
int teller = 0;

//BUTTON
int buttonPin = 22; 
int buttonState = LOW;



void setup() {
  Serial.begin(115200);




  pinMode(IRSensor_Binnen_Links, INPUT);
  pinMode(IRSensor_Binnen_Rechts, INPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(led_rood, OUTPUT);
  pinMode(led_geel, OUTPUT);
  pinMode(led_groen, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buttonPin, INPUT);
}

void loop() {


  // Write a pulse to the HC-SR04 Trigger Pin

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Measure the response from the HC-SR04 Echo Pin

  duration = pulseIn(echoPin, HIGH);

  // Determine distance from duration
  // Use 343 metres per second as speed of sound

  distance = (duration / 2) * 0.0343;

  // Send results to Serial Monitor

  Serial.print("Distance = ");
  if (distance >= 400 || distance <= 2) {
    Serial.println("Out of range");
  }
  else {
    Serial.print(distance);
    Serial.println(" cm");
  }


  Serial.print("IRSensor Binnen Rechts status = " );
  Serial.println(digitalRead(IRSensor_Binnen_Rechts));
  Serial.print("IRSensor Binnen Links status = " );
  Serial.println(digitalRead(IRSensor_Binnen_Links));




  //VOORUIT
  if (digitalRead(IRSensor_Binnen_Rechts) == 0 && digitalRead(IRSensor_Binnen_Links) == 0) {
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
    analogWrite(enA, 220);
    analogWrite(enB, 220);
    digitalWrite(led_groen, HIGH);
    digitalWrite(led_geel, LOW);
    counter = counter + 1;
    Serial.println(counter);
  }

  if (counter >= 300) {
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);
    analogWrite(enA, 220);
    analogWrite(enB, 220);
    digitalWrite(led_groen, LOW);
    digitalWrite(led_geel, LOW);
    digitalWrite(led_rood, HIGH);
  }



  //STOP
  if (digitalRead(IRSensor_Binnen_Rechts) == 1 && digitalRead(IRSensor_Binnen_Links) == 1 && digitalRead(buttonPin) == LOW || distance <= 10 ) {
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);
    analogWrite(enA, 0);
    analogWrite(enB, 0);
    digitalWrite(led_groen, LOW);
    digitalWrite(led_geel, HIGH);
    digitalWrite(led_rood, LOW);
    counter = 0;
    teller = teller + 1;
  }

  if (teller >= 2100  && distance > 10 || digitalRead(buttonPin) == HIGH) {
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
    analogWrite(enA, 220);
    analogWrite(enB, 220);
    digitalWrite(led_groen, HIGH);
    digitalWrite(led_geel, LOW);
    delay(50);
     
    
  }





  //DRAAIEN
  if (digitalRead(IRSensor_Binnen_Links) == 1 && digitalRead(IRSensor_Binnen_Rechts) == 0) {
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
    analogWrite(enA, 220);
    analogWrite(enB, 220);
    digitalWrite(led_groen, HIGH);
    digitalWrite(led_geel, LOW);
    digitalWrite(led_rood, LOW);
    counter = 0;
    teller = 0;

  }

  if (digitalRead(IRSensor_Binnen_Links) == 0 && digitalRead(IRSensor_Binnen_Rechts) == 1) {
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW );
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
    analogWrite(enA, 220);
    analogWrite(enB, 220);
    digitalWrite(led_groen, HIGH);
    digitalWrite(led_geel, LOW);
    digitalWrite(led_rood, LOW);
    counter = 0;
    teller = 0;

  }
} 
