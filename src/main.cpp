#include <Arduino.h>
#include <NewPing.h>

//LED
int led = 13;

// PARAMETROS DE REFERÊNCIA
static int MAX_NEAR = 20;
static int MAX_FAR = 35;
static int MAX_SIGN = 200;
static int TimeDelay = 250;
static int MODULO = 1;

// RODAS DIREITA
int RD1 = 4; //RODA IN1
int RD2 = 5; //RODA IN2
// RODA ESQUERDA
int RE1 = 6; //RODA IN3
int RE2 = 7; //RODA IN4

// SENSOR SONAR DIREITA
int echoD = 9;
int trigD = 8;
NewPing sonarD(trigD, echoD, MAX_SIGN);
// SENSOR SONAR ESQUE.RDA
int echoE = 11;
int trigE = 10;
NewPing sonarE(trigE, echoE, MAX_SIGN);
// // SENSOR SONAR CENTRAL
// int echoC = 13;
// int trigC = 12;
// NewPing sonarC(trigC, echoC, MAX_SIGN);

// VARIAVEIS DE MONITORAMENTO
int direita;
int esquerda;

//FUNÇÕES DE MOVIMENTO
void stop();           // PARA
void atack();          // ANDA PARA FRENTE
void back();           // ANDA PARA TRÁS
void right();          // GIRA À DIRETA DENTRO DO PROPRIO EIXO
void left();           // GIRA À ESQUERDA DENTRO DO PROPRIO EIXO
void corrigePosicao(); // CORRIGE POSIÇÃO
void getPosicao();     //ATUALIZA DISTACIAS DOS SENSORES DIREITA E ESQUERDA
int modular(int, int mod = 2);
void printDistance(int); // FUNÇAO PAR TESTE de logica

//FUNÇOES DE MEDIR DISTANCIA
void distanciaD()
{
  direita = sonarD.convert_cm(sonarD.ping_median(2));
  if (direita > MAX_FAR + 10)
    direita = MAX_FAR;
  if (direita < MAX_NEAR - (MAX_NEAR/2))
    direita = MAX_NEAR + (MAX_NEAR/2);
  direita = modular(direita, MODULO);
}
void distanciaE()
{
  esquerda = sonarE.convert_cm(sonarE.ping_median(2));
  if (esquerda > MAX_FAR + 10)
    esquerda = MAX_FAR;
  if (esquerda < MAX_NEAR - (MAX_NEAR/2))
    direita = MAX_NEAR + (MAX_NEAR/2);
  esquerda = modular(esquerda, MODULO);
}

void setup()
{
  Serial.begin(9600);
  pinMode(RD1, OUTPUT);
  pinMode(RD2, OUTPUT);
  pinMode(RE1, OUTPUT);
  pinMode(RE2, OUTPUT);
  pinMode(led, OUTPUT);
}

void loop()
{
  getPosicao();
  corrigePosicao();
}

void getPosicao()
{
  distanciaD();
  distanciaE();
}
void corrigePosicao()
{
  if (direita == 0 && esquerda == 0)
  {
    // objeto fora de alcance
    Serial.println("");
    stop();
  }
  else if (esquerda < MAX_NEAR && direita < MAX_NEAR)
  {
    back();
    printDistance(2);
  }
  else if (esquerda > MAX_FAR && direita > MAX_FAR)
  {
    atack();
    printDistance(8);
  }
  else if (direita > esquerda && (direita - esquerda) > 2)
  {
    left();
    printDistance(4);
  }
  else if (esquerda > direita && (esquerda - direita) > 2)
  {
    right();
    printDistance(6);
  }
  else
  {
    stop();
    printDistance(5);
  }
}
void stop()
{
  digitalWrite(RD1, HIGH);
  digitalWrite(RD2, HIGH);
  digitalWrite(RE1, HIGH);
  digitalWrite(RE2, HIGH);
  digitalWrite(led, HIGH);

}
void atack()
{
  digitalWrite(RD2, HIGH);
  digitalWrite(RD1, LOW);
  digitalWrite(RE2, HIGH);
  digitalWrite(RE1, LOW);
  digitalWrite(led, LOW);
}
void back()
{
  digitalWrite(RD1, HIGH);
  digitalWrite(RD2, LOW);
  digitalWrite(RE1, HIGH);
  digitalWrite(RE2, LOW);
  digitalWrite(led, LOW);
}
void right()
{
  digitalWrite(RD1, HIGH);
  digitalWrite(RD2, LOW);
  digitalWrite(RE1, LOW);
  digitalWrite(RE2, HIGH);
  digitalWrite(led, LOW);
}
void left()
{
  digitalWrite(RD2, HIGH);
  digitalWrite(RD1, LOW);
  digitalWrite(RE2, LOW);
  digitalWrite(RE1, HIGH);
  digitalWrite(led, LOW);
}
int modular(int direcao, int mod)
{
  return direcao - (direcao % mod);
}
void printDistance(int direcao)
{
  if (direcao == 6)
  {
    Serial.println("            RIGHT");
    Serial.print(esquerda);
    Serial.print(" ---------------- ");
    Serial.println(direita);
  }
  else if (direcao == 4)
  {
    Serial.println("LEFT              ");
    Serial.print(esquerda);
    Serial.print(" ---------------- ");
    Serial.println(direita);
  }
  else if (direcao == 2)
  {
    Serial.println("       BACK       ");
    Serial.print(esquerda);
    Serial.print(" ---------------- ");
    Serial.println(direita);
  }
  else if (direcao == 8)
  {
    Serial.println("       ATACK      ");
    Serial.print(esquerda);
    Serial.print(" ---------------- ");
    Serial.println(direita);
  }
  else if (direcao == 5)
  {
    Serial.println("       STOP      ");
    Serial.print(esquerda);
    Serial.print(" ---------------- ");
    Serial.println(direita);
  }
}
