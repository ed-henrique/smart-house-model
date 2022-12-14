/*
Este código contém a implementação do quarto, cozinha, parte da sala de estar e jardim.
Esta, por sua vez, é composta por:

- 3 sensores ultrasônicos (Servem para detectar presença nos quartos e acender seus respectivos LEDs)
- 5 LEDs (Um simula o alarme)
- Sensor de gás
- Sensor de umidade (Usado para detectar quando ligar uma torneira para molhar as plantas, representado por um LED)

Este modulo foi designado para Lucas Ribeiro, que o implementou.
*/

// Sensores analógicos
#define SENSOR_GAS 0
#define SENSOR_UMIDADE 5

// LEDs
#define LED_JARDIM 13
#define LED_COZINHA 11
#define LED_SALA_DE_ESTAR 10
#define LED_QUARTO 12
#define LED_QUARTO_ALARME 8

// Sensores ultrasônicos
#define QUARTO_ECHO 5
#define QUARTO_TRIGGER 4
#define COZINHA_ECHO 3
#define COZINHA_TRIGGER 2
#define SALA_DE_ESTAR_ECHO 6
#define SALA_DE_ESTAR_TRIGGER 7

// Contadores
unsigned long contadorTempoQuarto = 0;
unsigned long contadorTempoJardim = 0;
unsigned long contadorTempoAlarme = 0;
unsigned long contadorTempoCozinha = 0;
unsigned long contadorTempoSalaDeEstar = 0;

#define INTERVALO 5000
#define PARA_CENTIMETROS 0.017

float distancia;

void setup() {
  Serial.begin(9600);

  pinMode(LED_JARDIM, OUTPUT);
  pinMode(LED_COZINHA, OUTPUT);
  pinMode(LED_SALA_DE_ESTAR, OUTPUT);
  pinMode(LED_QUARTO, OUTPUT);
  pinMode(LED_QUARTO_ALARME, OUTPUT);

  pinMode(QUARTO_ECHO, INPUT);
  pinMode(QUARTO_TRIGGER, OUTPUT);
  pinMode(COZINHA_ECHO, INPUT);
  pinMode(COZINHA_TRIGGER, OUTPUT);
  pinMode(SALA_DE_ESTAR_ECHO, INPUT);
  pinMode(SALA_DE_ESTAR_TRIGGER, OUTPUT);

  pinMode(SENSOR_GAS, INPUT);
  pinMode(SENSOR_UMIDADE, INPUT);
}
 
void loop() {
  quarto();
  jardim();
  cozinha();
  salaDeEstar();
}

void quarto() {
  if (millis() - contadorTempoAlarme >= INTERVALO) {
    contadorTempoAlarme = millis();
    digitalWrite(LED_QUARTO_ALARME, HIGH);
    delay(500);
    digitalWrite(LED_QUARTO_ALARME, LOW);
  }
  
  digitalWrite(QUARTO_TRIGGER, HIGH);
  delay(1);
  digitalWrite(QUARTO_TRIGGER, LOW);
    
  distancia = pulseIn(QUARTO_ECHO, HIGH) * PARA_CENTIMETROS;

  if (distancia != 0.0 && distancia <= 10.0) {
    contadorTempoQuarto = millis();
    
  	digitalWrite(LED_QUARTO, HIGH);
    Serial.print("[QUARTO] LED ligado! Distância: ");
    Serial.print(distancia);
    Serial.println(" CM");
    Serial.println();
  } else if (millis() - contadorTempoQuarto >= INTERVALO) {
  	digitalWrite(LED_QUARTO, LOW);
  }
}

void cozinha() {
  int quantidadeGas = analogRead(SENSOR_GAS);

  digitalWrite(COZINHA_TRIGGER, HIGH);
  delay(1);
  digitalWrite(COZINHA_TRIGGER, LOW);
    
  distancia = pulseIn(COZINHA_ECHO, HIGH) * PARA_CENTIMETROS;

  if (quantidadeGas >= 800) {
    Serial.print("[COZINHA] Excesso de gás detectado! Sensor de gás: ");
    Serial.println(quantidadeGas);
    Serial.println();
  }

  if (distancia != 0.0 && distancia <= 10.0) {
    contadorTempoCozinha = millis();

  	digitalWrite(LED_COZINHA, HIGH);
    Serial.print("[COZINHA] LED ligado! Distância: ");
    Serial.print(distancia);
    Serial.println(" CM");
    Serial.println();
  } else if (millis() - contadorTempoCozinha >= INTERVALO) {
  	digitalWrite(LED_COZINHA, LOW);
  }
}

void salaDeEstar() {
  digitalWrite(SALA_DE_ESTAR_TRIGGER, HIGH);
  delay(1);
  digitalWrite(SALA_DE_ESTAR_TRIGGER, LOW);
    
  distancia = pulseIn(SALA_DE_ESTAR_ECHO, HIGH) * PARA_CENTIMETROS;

  if (distancia != 0.0 && distancia <= 10.0) {
    contadorTempoSalaDeEstar = millis();

  	digitalWrite(LED_SALA_DE_ESTAR, HIGH);
    Serial.print("[SALA DE ESTAR] LED ligado! Distância: ");
    Serial.print(distancia);
    Serial.println(" CM");
    Serial.println();
  } else if (millis() - contadorTempoSalaDeEstar >= INTERVALO) {
  	digitalWrite(LED_SALA_DE_ESTAR, LOW);
  }
}

void jardim () {
  if (millis() - contadorTempoJardim < INTERVALO) return;
  
  contadorTempoJardim = millis(); 
  int leituraUmidade = analogRead(SENSOR_UMIDADE); 

  if (leituraUmidade<=1023 && leituraUmidade>=682) {
    Serial.println("[JARDIM] Nível de Umidade baixo!");
  } else if (leituraUmidade<=681 && leituraUmidade>=341) { 
    Serial.println("[JARDIM] Nível de Umidade Medio!");
  } else if (leituraUmidade<=340 && leituraUmidade>=0) {
    Serial.println("[JARDIM] Nível de Umidade Alto!");
  }
}
