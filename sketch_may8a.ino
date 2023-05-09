// Sonic skynjari
int echoPin = 9;
int trigPin = 10;

// Mótor A
int pwmA = 3;
int Ai1 = 5;
int Ai2 = 4;

// Mótor B
int pwmB = 6;
int Bi1 = 7;
int Bi2 = 8;

int vifta = 1;

#include "tdelay.h"

const int rautt = 12;     // pinninn sem LED peran er tengd í
const int blatt = 13;     // pinninn sem LED peran er tengd í
bool LED_on = true;       // breytan heldur utan um hvort á að vera kveikt eða slökkt á LED perunni
TDelay LED_bidtimi(250);  // Blikktíminn í ms., kveikt í 1 sek., slökkt í 1 sek.
const int stefnu_haegri = 11;
const int stefnu_vinstri = 2;


void setup() {
  // Sonic pinnar
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  // Mótor pinnar
  pinMode(pwmA, OUTPUT);
  pinMode(pwmB, OUTPUT);
  pinMode(Ai1, OUTPUT);
  pinMode(Ai2, OUTPUT);
  pinMode(13, OUTPUT);  // skilgreini pinnann sem LED er tengt í sem úttakspinna
  pinMode(12, OUTPUT);  // skilgreini pinnann sem LED er tengt í sem úttakspinna
  pinMode(Bi1, OUTPUT);
  pinMode(Bi2, OUTPUT);

  pinMode(stefnu_vinstri, OUTPUT);
  pinMode(stefnu_haegri, OUTPUT);


  
  Serial.begin(9600);
}

void loop() {

  afram(200);
  int maela = maelaFjarlaegd();
  Serial.println(maela);
  if (maela < 50) {
    stoppa();
    delay(250);
    vinstri(160);
    delay(400);
    stoppa();
    delay(250);

    int v = maelaFjarlaegd();
    haegri(160);
    delay(800);
    stoppa();
    delay(250);
    int h = maelaFjarlaegd();
    stoppa();
    delay(250);
    if (v > h) {
      vinstri(160);
      delay(800);
    }
    if (h < 50 && v < 50) {
      haegri(160);
      delay(400);
    }
  }
}

void afram(int hradi) {
  // Set Motor A forward
  digitalWrite(Ai1, HIGH);
  digitalWrite(Ai2, LOW);

  // Set Motor B forward
  digitalWrite(Bi1, HIGH);
  digitalWrite(Bi2, LOW);

  // Set the motor speeds
  analogWrite(pwmA, hradi);
  analogWrite(pwmB, hradi);

  digitalWrite(stefnu_haegri, LOW);
  digitalWrite(stefnu_vinstri, LOW);
  digitalWrite(vifta, HIGH);

  // Fallið timiLidinn() skilar true ef biðtíminn er liðinn í þessu tilfelli 1 sek.
  if (LED_bidtimi.timiLidinn() == true) {
    // víxla (e. toggle) stöðunni á breytunni sem heldur utan um hvort kveikt eða slökkt er á LED perunni
    LED_on = !LED_on;
  }

  // kveikir eða slekkur á LED perunni eftir stöðu LED_on breytunnar
  digitalWrite(12, LED_on);
  //stoppa();
  //delay(250);
  digitalWrite(13, !LED_on);
}

int maelaFjarlaegd() {
  // sendir út púlsar
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // mælt hvað púlsarnir voru lengi að berast til baka
  return pulseIn(echoPin, HIGH) / 58.0;  // deilt með 58 til að breyta í cm
}
void bakka(int hradi) {
  // Set Motor A forward
  digitalWrite(rautt, LOW);
  digitalWrite(blatt, LOW);
  
  digitalWrite(Ai1, LOW);
  digitalWrite(Ai2, HIGH);

  // Set Motor B forward
  digitalWrite(Bi1, LOW);
  digitalWrite(Bi2, HIGH);

  // Set the motor speeds
  analogWrite(pwmA, hradi);
  analogWrite(pwmB, hradi);
  
  digitalWrite(vifta, LOW);
}
void stoppa() {
  // Set Motor A forward
  digitalWrite(rautt, LOW);
  digitalWrite(blatt, LOW);
  
  digitalWrite(Ai1, LOW);
  digitalWrite(Ai2, LOW);

  // Set Motor B forward
  digitalWrite(Bi1, LOW);
  digitalWrite(Bi2, LOW);

  // Set the motor speeds
  analogWrite(pwmA, 0);
  analogWrite(pwmB, 0);
  
  digitalWrite(vifta, LOW);
}
void vinstri(int hradi) {
  // Set Motor A forward
  digitalWrite(stefnu_haegri, LOW);
  digitalWrite(stefnu_vinstri, HIGH);

  digitalWrite(rautt, LOW);
  digitalWrite(blatt, LOW);

  digitalWrite(Ai1, LOW);
  digitalWrite(Ai2, HIGH);

  // Set Motor B forward
  digitalWrite(Bi1, HIGH);
  digitalWrite(Bi2, LOW);

  // Set the motor speeds
  analogWrite(pwmA, hradi);
  analogWrite(pwmB, hradi);

  digitalWrite(vifta, LOW);
}
void haegri(int hradi) {
  // Set Motor A forward
  digitalWrite(stefnu_haegri, HIGH);
  digitalWrite(stefnu_vinstri, LOW);

  digitalWrite(rautt, LOW);
  digitalWrite(blatt, LOW);
  
  digitalWrite(Ai1, HIGH);
  digitalWrite(Ai2, LOW);

  // Set Motor B forward
  digitalWrite(Bi1, LOW);
  digitalWrite(Bi2, HIGH);

  // Set the motor speeds
  analogWrite(pwmA, hradi);
  analogWrite(pwmB, hradi);

  digitalWrite(vifta, LOW);
}