#include "RCSwitch.h"
#include <stdlib.h>
#include <stdio.h>
#include <neotimer.h>
//10 minutes timer
unsigned long waterPeriod = 10 * 60UL * 1000;
Neotimer waterTimer = Neotimer(waterPeriod);
unsigned long lockerPeriod = 6 * 60 * 60UL * 1000;
Neotimer lockerTimer = Neotimer(lockerPeriod);
//Neotimer lockerTimer = Neotimer(30*1000);

int waterPin = 7;
int lockerPin = 8;
const int capteur_D = 4;
//const int capteur_A = A0;

//int val_analogique;
int dogPin = 12;

RCSwitch signalReciever = RCSwitch();

int waterOn = 1111;
int waterOff = 9999;
int lockerOn = 2222;
int lockerOff = 8888;
int dogOn = 3333;
int dogOff = 7777;

bool dogEnabled=true;

void setup() {
  //init relay pin
  pinMode(waterPin, OUTPUT);
  pinMode(lockerPin, OUTPUT);
  digitalWrite(waterPin, HIGH);
  digitalWrite(lockerPin, HIGH);

  pinMode(capteur_D, INPUT);
  //  pinMode(capteur_A, INPUT);
  pinMode(dogPin, OUTPUT);
  digitalWrite(dogPin, HIGH);

  Serial.begin(9600);
  //init FM receiver
  signalReciever.enableReceive(0);  // Receiver on inerrupt 0 =&gt; that is pin #2
}

void checkTimer() {
  if (waterTimer.done()) {
    digitalWrite(waterPin, HIGH);
    Serial.println("water off");
    waterTimer = Neotimer(waterPeriod);
  }

  if (lockerTimer.done()) {
    digitalWrite(lockerPin, HIGH);
    Serial.println("locker off");
    lockerTimer = Neotimer(lockerPeriod);
  }
}

void checkSprinkler(int value) {
  if (value == waterOff) {
    //switch relay off
    digitalWrite(waterPin, HIGH);
    waterTimer.stop();
    Serial.println("Timer stop");
    delay(3000);

  }
  if (value == waterOn )  {
    //switch relay on
    digitalWrite(waterPin, LOW);
    waterTimer.start();
    Serial.println("Water on");
    delay(3000);
  }

}

void checkLocker(int value) {
  if (value == lockerOff) {
    //switch relay off
    digitalWrite(lockerPin, HIGH);
    lockerTimer.stop();
    Serial.println("Locker timer stop");
    delay(3000);

  }
  if (value == lockerOn )  {
    //switch relay on
    digitalWrite(lockerPin, LOW);
    lockerTimer.start();
    Serial.println("Locker on");
    delay(3000);
  }
}
void checkDog(int value) {
  if(value==dogOff){
    dogEnabled = false;
  }

  if(!dogEnabled){
    return;
  }
  
  if (digitalRead(capteur_D) == LOW) {
    Serial.println("Digital value : wet");
    digitalWrite(dogPin, LOW);
    delay(1000);
  } else {
    Serial.println("Digital value : dry");
    digitalWrite(dogPin, HIGH);
    delay(1000);
  }

}
void loop() {

  checkTimer();
  int value = -1;

  if (signalReciever.available()) {
    value = signalReciever.getReceivedValue();

    signalReciever.resetAvailable();
  }


  checkSprinkler(value);

  checkLocker(value);

  checkDog(value);

}
