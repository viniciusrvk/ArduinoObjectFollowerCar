#include <Arduino.h>
#include <NewPing.h>

// RODAS DIREITA
int RD1 = 4; //RODA IN1
int RD2 = 5; //RODA IN2
// RODA ESQUERDA
int RE1 = 6; //RODA IN3
int RE2 = 7; //RODA IN4

// SENSOR SONAR DIREITA
int echoD = 9;
int trigD = 8;
NewPing sonarD(trigD, echoD, 70);
// SENSOR SONAR ESQUERDA
int echoE = 11;
int trigE = 10;
NewPing sonarE(trigE, echoE, 70);

int MAX_NEAR = 10;
int MAX_FAR = 20;
int MAX_LEFT = 3;
int MAX_RIGTH = -3;

int direita;
int esquerda;
int diferencaDireitaEsquerda;

//FUNÇÕES DE MOVIMENTO
void stop(); // PARA
void atack(); // ANDA PARA FRENTE
void back(); // ANDA PARA TRÁS
void right(); // GIRA À DIRETA DENTRO DO PROPRIO EIXO
void left(); // GIRA À ESQUERDA DENTRO DO PROPRIO EIXO
void corrigePosicao(); // CORRIGE POSIÇÃO 
void getPosicao(); //ATUALIZA DISTACIAS DOS SENSORES DIREITA E ESQUERDA

//FUNÇOES DE MEDIR DISTANCIA 
void distanciaD(){
  direita = sonarD.ping_cm();
  delay(50);
  // sonarD.timer_stop();
}
void distanciaE(){
  esquerda = sonarE.ping_cm();
  delay(50);
  // sonarE.timer_stop();
}

void setup() {
  Serial.begin(9600);
  pinMode(RD1, OUTPUT);
  pinMode(RD2, OUTPUT);
  pinMode(RE1, OUTPUT);
  pinMode(RE2, OUTPUT);

}

void loop() {
  getPosicao();
  corrigePosicao();
}

void getPosicao(){
  distanciaD();
  distanciaE();
  diferencaDireitaEsquerda = direita - esquerda;

}
void corrigePosicao(){
  if(direita < MAX_NEAR && esquerda < MAX_NEAR){
    back();
  }
  else if(direita > MAX_FAR && esquerda > MAX_FAR){
    atack();
  }
  else if (diferencaDireitaEsquerda > MAX_LEFT) {
    left();
  }
  else if(diferencaDireitaEsquerda < MAX_RIGTH){
    right();
  }
  else{
    stop();
  }
}
void stop(){
  digitalWrite(RD1, HIGH);
  digitalWrite(RD2, HIGH);
  digitalWrite(RE1, HIGH);
  digitalWrite(RE2, HIGH);
}
void atack(){
  digitalWrite(RD2, HIGH);
  digitalWrite(RD1, LOW);
  digitalWrite(RE2, HIGH);
  digitalWrite(RE1, LOW);
}
void back(){
  digitalWrite(RD1, HIGH);
  digitalWrite(RD2, LOW);
  digitalWrite(RE1, HIGH);
  digitalWrite(RE2, LOW);
}
void right(){
  digitalWrite(RD1, HIGH);
  digitalWrite(RD2, LOW);
  digitalWrite(RE1, LOW);
  digitalWrite(RE2, HIGH);
}
void left(){
  digitalWrite(RD2, HIGH);
  digitalWrite(RD1, LOW);
  digitalWrite(RE2, LOW);
  digitalWrite(RE1, HIGH);
}
