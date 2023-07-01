// This is a remote-controlled car equipped with automatic functionality. The automatic feature can be adjusted according to a specific time frame of your choice.


#include <IRremote.h>
#include <Servo.h>
#include <NewPing.h>

#define TRIGGER_PIN  7
#define ECHO_PIN     5   
#define MAX_DISTANCE 400 

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);
Servo servoMotor;
int LedR = A5;
int LedG = 2;
int pos = 90;

int angmax = 0; 
const int IR_PIN = A0;
IRrecv irrecv(IR_PIN);

// Pinos do módulo relé
const int relayPinD = A1; // Pino do módulo relé
// Pinos do módulo relé
const int relayPinE = 12; // Pino do módulo relé

bool bolinhaAtivada = false; 

void setup() {
  Serial.begin(9600);
  irrecv.enableIRIn();
  servoMotor.attach(9); 
  pinMode(10, OUTPUT);
  pinMode(LedR, OUTPUT);
  pinMode(LedG, OUTPUT);
  pinMode(relayPinD, OUTPUT); // Configura o pino do relé como saída
  pinMode(relayPinE, OUTPUT); // Configura o pino do relé como saída
  servoMotor.write(90);
}


void loop() {
  if (irrecv.decode()) {
    unsigned long x = irrecv.decodedIRData.decodedRawData;
    Serial.println(x, HEX);
    Serial.println("comeco");
    if (x == 0xA55AFF00) { // F
      digitalWrite(LedR, HIGH);
      digitalWrite(LedG, LOW);
      for (pos; pos <= 180; pos++) {  // Incrementa de 90 a 180 graus
        servoMotor.write(pos);  // Move o servo para a posição atual
        delay(15);  // Aguarda um pequeno intervalo para o servo atingir a posição
      }
      delay(1000);
    }

    if (x == 0xF708FF00) { // D
      digitalWrite(LedG, HIGH);
      digitalWrite(LedR, LOW);
      for (pos; pos >= 0; pos--) {  // Decrementa de 180 a 90 graus
        servoMotor.write(pos);  // Move o servo para a posição atual
        delay(15);  // Aguarda um pequeno intervalo para o servo atingir a posição
      }
      delay(1000);
    }

    if (x == 0xF609FF00) { // DIREITA
      direita(600); 
    }

    if (x == 0xF807FF00) { // ESQUERDA
      esquerda(600);
    }

    if (x == 0xEA15FF00) { // BOLINHA
      bolinhaAtivada = !bolinhaAtivada; 
      int i = 0;
      while (i < 3) { // Here you can adjust the time od automatic control i < "The time you want".
        digitalWrite(LedG, HIGH);
        digitalWrite(LedR, HIGH);
        int distance = 0;
        for (int pos1 = 0; pos1 <= 180; pos1++) { 
          servoMotor.write(pos1); 
          delay(40);                   
          Serial.print("Ping: ");
          int d = sonar.ping_cm();
          Serial.print(d);
          Serial.println("cm");
          if (d <= 400 && d > distance ) {
              angmax = pos1;
              Serial.println("Nova distancia maxima");
              distance = d;
              Serial.println(distance);
          }
        }
        servoMotor.write(angmax);
        delay(1000);
        if(angmax <= 20){
          direita(1067);
          delay(100);
          frente(2000);
        }else if (angmax <= 40 & angmax>= 21) {
          direita(800);
          delay(100);
          frente(2000); 
        
        } else if (angmax <= 60 & angmax >= 41) {
          direita(534);
          delay(100);
          frente(2000);  
        
        } else if (angmax <= 80 & angmax >= 61) {
          direita(267);
          delay(100);
          frente(2000);  
        }else if (angmax <= 100 & angmax >= 81) {
          frente(2000);
        }  else if (angmax >= 101 & angmax <= 120) {
          esquerda(257);
          delay(100);
          frente(2000);

        }  else if (angmax >= 121 & angmax <= 140) {
          esquerda(564);
          delay(100);
          frente(2000);
        }  else if (angmax >= 141 & angmax <= 160) {
          esquerda(801);
          delay(100);
          frente(2000);

        } else {
          esquerda(1067);
          delay(100);
          frente(2000);
        }
        i++;
      }
    }

    if (x == 0xBF40FF00) { // CIMA
      frente(3000);
    }
    if (x == 0xE619FF00) { // BAIXO
      digitalWrite(LedG, HIGH);
      digitalWrite(LedR, HIGH);
      direita(1800);
      frente(3000); 
    }
  }

  irrecv.resume();
}
void frente(int duration){
  digitalWrite(LedG, HIGH);
  digitalWrite(LedR, HIGH);
  digitalWrite(relayPinE, HIGH);
  digitalWrite(relayPinD, HIGH);
  delay(duration);
  digitalWrite(LedG, LOW);
  digitalWrite(LedR, LOW);
  digitalWrite(relayPinE, LOW);
  digitalWrite(relayPinD, LOW);
  servoMotor.write(90);
}
void direita(int duration){
  digitalWrite(LedR, HIGH);
  digitalWrite(relayPinD, HIGH);
  delay(duration);
  digitalWrite(LedR, LOW);
  digitalWrite(relayPinD, LOW);
  servoMotor.write(90);
}
void esquerda(int duration){
  digitalWrite(LedG, HIGH);
  digitalWrite(relayPinE, HIGH);
  delay(duration);
  digitalWrite(LedG, LOW);
  digitalWrite(relayPinE, LOW);
  servoMotor.write(90);
}