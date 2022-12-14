#define sensorUmidade A5

unsigned long tempoAnterior = 0;
unsigned long intervalo = 1000; 

int trigger_quarto = 4;
int echo_quarto = 5;

int trigger_coz = 2;
int echo_coz = 3;

int trigger_sala = 7;
int echo_sala = 6;


int sensorGas = A0; 		 
int valorSensorGas = 0;
int led = 12;
int led2 = 11;
int led3 = 10;

float distancia;


void setup()
{
  pinMode (led, OUTPUT);
  pinMode (led2, OUTPUT);
  pinMode (led3, OUTPUT);
  pinMode (trigger_quarto, OUTPUT);
  pinMode (echo_quarto, INPUT);

  pinMode (trigger_coz, OUTPUT);
  pinMode (echo_coz, INPUT);

  pinMode (trigger_sala, OUTPUT);
  pinMode (echo_sala, INPUT);
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

  
  led_quarto();

  led_cozinha();

  led_sala();
  
  jardim();



}

void led_quarto()
{

  //sensor de distancia
  digitalWrite(trigger_quarto, LOW);
  delay(100);
  digitalWrite(trigger_quarto, HIGH);
  delay(100);
  digitalWrite(trigger_quarto, LOW);
    
  //convertendo em CM a distancia
  distancia = pulseIn (echo_quarto, HIGH);
  distancia = distancia/58;
  Serial.print ("Sensor Distancia Quarto: ");
  Serial.print (distancia);
  Serial.println(" CM");
  Serial.println();

  if (distancia != 0 && distancia < 10) {
  	digitalWrite(led, HIGH);
  }
  else {
  	digitalWrite(led, LOW);
  }

}

void led_cozinha()
{
  //sensor de distancia
  digitalWrite(trigger_coz, LOW);
  delay(100);
  digitalWrite(trigger_coz, HIGH);
  delay(100);
  digitalWrite(trigger_coz, LOW);
    
  //convertendo em CM a distancia
  distancia = pulseIn (echo_coz, HIGH);
  distancia = distancia/58;
  Serial.print ("Sensor Distancia Cozinha: ");
  Serial.print (distancia);
  Serial.println(" CM");
  Serial.println();

  if (distancia != 0 && distancia < 10) {
  	digitalWrite(led2, HIGH);
  }
  else {
  	digitalWrite(led2, LOW);
  }
}

void led_sala()
{
  //sensor de distancia
  digitalWrite(trigger_sala, LOW);
  delay(100);
  digitalWrite(trigger_sala, HIGH);
  delay(100);
  digitalWrite(trigger_sala, LOW);
    
  //convertendo em CM a distancia
  distancia = pulseIn (echo_sala, HIGH);
  distancia = distancia/58;
  Serial.print ("Sensor Distancia Sala: ");
  Serial.print (distancia);
  Serial.println(" CM");
  Serial.println();

  if (distancia != 0 && distancia < 10) {
  	digitalWrite(led3, HIGH);
  }
  else {
  	digitalWrite(led3, LOW);
  }
}

void jardim (){
  unsigned long tempoAtual = millis(); 
  if (tempoAtual-tempoAnterior > intervalo){
    tempoAnterior =tempoAtual; 
    int leitura = analogRead(sensorUmidade); 

    if (leitura<=1023 && leitura>=682){
      Serial.println("Nivel de Umidade baixo");
    }else{
      if (leitura<=681 && leitura>=341){ 
        Serial.println("Nivel de Umidade Medio");
      }
      else{
        if (leitura<=340 && leitura>=0){
          Serial.println("Nivel de Umidade Alto");
        }
      } 
    }
  }
}
