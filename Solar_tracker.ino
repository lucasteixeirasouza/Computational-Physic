#include <Servo.h>      
Servo myservo_cima;         
Servo myservo2_baixo;    

int initial_position = 90;
int initial_position2 = 90;
int LDR1 = A0;           //azul claro 
int LDR2 = A1;          //Roxo
int LDR3 = A2;          //Amarelo
int LDR4 = A3;          //Laranja         
int servopin = 11;
int servopin2 = 9;        
int valorsensor1;
int valorsensor2;
int valorsensor3;
int valorsensor4;
int averageValue;
int dif1 = 0, dif2 = 0, dif3 = 0, dif4 = 0;
int max1=0, max2=0, max3=0;
int ser1 = 80, ser2=0;
int error = 5;

void setup() { 

  Serial.begin(9600);
  myservo_cima.attach(servopin);
  myservo2_baixo.attach(servopin2); 
  pinMode(LDR1, INPUT);   
  pinMode(LDR2, INPUT);
  pinMode(LDR3, INPUT);   
  pinMode(LDR4, INPUT);
  myservo_cima.write(90);
  myservo2_baixo.write(0);
  delay(2000); 
         
}  
 
void loop() { 

  long int t = 0; float tempo = 0.0; float soma = 0.0; int i = 1;
  while (i < 1001){
    valorsensor1 = analogRead(LDR1); 
    valorsensor2 = analogRead(LDR2); 
    valorsensor3 = analogRead(LDR3); 
    valorsensor4 = analogRead(LDR4); 
    averageValue = (valorsensor1 + valorsensor2 +valorsensor3 + valorsensor4) / 4;
    soma = soma + (float)averageValue;
    i = i+1;
  }

  t = millis(); tempo = (float) t / 1000.;
  Serial.print(tempo);
  Serial.print("," );     
  Serial.println(averageValue);
  delay(1000);

  int R1 = analogRead(LDR1); 
  int R2 = analogRead(LDR2); 
  int diff1 = abs(R1 - R2);   
  int diff2 = abs(R2 - R1);
  int R3 = analogRead(LDR3); 
  int R4 = analogRead(LDR4); 
  int diff3 = abs(R3 - R4);   
  int diff4 = abs(R4 - R3);
  
  if((diff1 <= error) || (diff2 <= error)) { 
    
  } else {    
    if(R1 > R2){
      initial_position++; 
      myservo_cima.write(initial_position); 
    }

    if(R1 < R2) {
     initial_position--;
      myservo_cima.write(initial_position); 
    }
  }
  delay(50);

  if((diff3 <= error) || (diff4 <= error)) { 
    
  } else {    
    if(R3 > R4){
      initial_position2++;
      myservo2_baixo.write(initial_position2);

    }

    if(R3 < R4) {
      initial_position2--;
      myservo2_baixo.write(initial_position2);
    }
  }
  delay(50);

}
