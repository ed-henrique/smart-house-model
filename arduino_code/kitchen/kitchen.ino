//Define os pinos sensor ultrassonico
#define pino_trigger 4	 
#define pino_echo 5

int led = 3;
int sensorGas = A5; 		 
int valorSensorGas = 0;

int som = 13;

float distancia;
 
void setup()
{
  pinMode (led, OUTPUT);
  pinMode (pino_trigger, OUTPUT);
  pinMode (pino_echo, INPUT);
  pinMode (sensorGas, INPUT);
  
  Serial.begin(9600);
}
 
void loop()
{
  //sensor de gas
  valorSensorGas = analogRead(sensorGas);
  Serial.print("Sensor de Gas: ");
  Serial.println(valorSensorGas);
  Serial.println();
  
  //sensor de distancia
  digitalWrite(pino_trigger, LOW);
  delay(100);
  digitalWrite(pino_trigger, HIGH);
  delay(100);
  digitalWrite(pino_trigger, LOW);
  
  //convertendo em CM a distancia
  distancia = pulseIn (pino_echo, HIGH);
  distancia = distancia/58;
  Serial.print ("Sensor Distancia: ");
  Serial.print (distancia);
  Serial.println(" CM");
  Serial.println();
  
  if (distancia < 90) 
  {
  	digitalWrite(led, HIGH);
  }
  else 
  {
  	digitalWrite(led, LOW);
  }
  
  if (valorSensorGas > 250)
  {
  	tone(som, 1500);
    delay(500);
    noTone (som);
    delay(500);
  }
}

