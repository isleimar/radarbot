#include "Carro.h"
#include <Arduino.h>

Carro:: Carro(int motorEsq, int motorDir) : pinoMotorEsq(motorEsq), pinoMotorDir(motorDir) {}

void Carro::iniciar() {
    pinMode(pinoMotorEsq, OUTPUT);
    pinMode(pinoMotorDir, OUTPUT);
}

void Carro::moverFrente() {
    digitalWrite(pinMotorEsq, HIGH);
    digitalWrite(pinMotorDir, HIGH);
}

void Carro::parar() {
    digitalWrite(pinoMotorEsq, LOW);
    digitalWrite(pinoMotorDir, LOW);
}

void Carro::virarDireita(){
    digitalWrite(pinoMotorEsq, HIGH);
    digitalWrite(pinoMotorDir, LOW);
    delay(500);
    parar();
}

void Carro::virarEsquerda(){
    digitalWrite(pinoMotorEsq, LOW);
    digitalWrite(pinoMotorDir, HIGH);
    delay(500);
    parar();
}

void Carro::virar180(){
    digitalWrite(pinoMotorEsq, HIGH);
    digitalWrite(pinoMotorDir, LOW);
    delay(1000);
    parar();
}