#include <Servo.h>

Servo curtain;
int pos = 0;

#define PIR 2
#define FAN 5
#define LED 13

int PirSensorState = 0;
int isCurtainOpen = 0;
int time = 20000;

void setup()
{
  pinMode(PIR, INPUT);
  pinMode(LED, OUTPUT);
  pinMode(FAN, OUTPUT);
  curtain.attach(6);
}

void loop()
{
  if (millis() >= time) {
    if (isCurtainOpen) close_curtain();
    else               open_curtain();

    isCurtainOpen = !isCurtainOpen;
    time += 20000;
  }

  PirSensorState = digitalRead(PIR);
  
  if (PirSensorState == HIGH) {
    digitalWrite(LED, HIGH);
    digitalWrite(FAN, HIGH);
  } else {
    digitalWrite(LED, LOW);
    digitalWrite(FAN, LOW);
  }
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