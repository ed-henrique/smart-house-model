#define sensorUmidade A0

unsigned long tempoAnterior = 0;
unsigned long intervalo = 1000; 

void setup() {
  Serial.begin(9600); // Inicialização da comunicação serial

}
void loop() {
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