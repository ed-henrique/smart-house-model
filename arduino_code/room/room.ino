#include <Servo.h>

Servo curtain;
int pos = 0;

#define PIR 2
#define FAN 5
#define LED 13
int BUZZER = 8;

int PirSensorState = 0;
int isCurtainOpen = 0;
long time = 20000;

void setup()
{
  Serial.begin(9600);

  pinMode(PIR, INPUT);
  pinMode(LED, OUTPUT);
  pinMode(FAN, OUTPUT);
  pinMode(BUZZER, OUTPUT);
  curtain.attach(9);
}

void loop()
{
  Serial.println(time);
  Serial.println(millis());

  if (millis() >= time) {
    //Serial.println("Mexendo servo motor");
    //Serial.println(isCurtainOpen);
    Serial.println("Apitando buzzer");
    
    for(int i=2000 ; i>100 ; i--){
         tone(BUZZER, i);
         delay(10);
    } 
    
    //if (isCurtainOpen) close_curtain();
    //else               open_curtain();

    //isCurtainOpen = !isCurtainOpen;
          
   
    time += 20000;
  }

  PirSensorState = digitalRead(PIR);
  
  if (PirSensorState == HIGH) {
    digitalWrite(LED, HIGH);
    digitalWrite(FAN, HIGH);

    Serial.print("PIR Sensor State: ");
    Serial.println("Led ligado");

    delay(50);
  } else {
    digitalWrite(LED, LOW);
    digitalWrite(FAN, LOW);

    Serial.print("PIR Sensor State: ");
    Serial.println("Led desligado");

    delay(50);
  }

  delay(30);
}

void open_curtain() {
  for (pos = 0; pos < 180; pos++) {
    curtain.write(pos);
    delay(30);
  }
}

void close_curtain() {
  for (pos = 180; pos > 0; pos--) {
    curtain.write(pos);
    delay(30);
  }
}