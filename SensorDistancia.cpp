#include "SensorDistancia.h"
#include <Arduino.h>

SensorDistancia::SensorDistancia(int trigger, int echo) : pinoTrigger(trigger), pinoEcho(echo) {}

void SensorDistancia::iniciar() {
    pinMode(pinoTrigger, OUTPUT);
    pinMode(pinoEcho, INPUT);
}

long SensorDistancia::medirDistancia(){
    digitalWrite(pinoTrigger, LOW);
    delayMicroseconds(2);
    digitalWrite(pinoTrigger, HIGH);
    delayMicroseconds(10);
    digitalWrite(pinoTrigger, LOW);

    long duracao = pulseIn(pinoEcho, HIGH);
    long distancia = duracao * 0.034 / 2;
    return distancia;
}