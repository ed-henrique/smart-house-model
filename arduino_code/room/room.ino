#define PIR 2
#define LED 13

int PirSensorState = 0;

void setup() {
  pinMode(PIR, INPUT);
  pinMode(LED, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  PirSensorState = digitalRead(PIR);
  
  if (PirSensorState == HIGH) {
    digitalWrite(LED, HIGH);
  } else {
    digitalWrite(LED, LOW);
  }
  
  delay(10);
}