#include "SensorDistancia.h"
#include <Arduino.h>

SensorDistancia::SensorDistancia(int trigger, int echo): 
    pinoTrigger(trigger), 
    pinoEcho(echo) {}

void SensorDistancia::iniciar() {
    pinMode(pinoTrigger, OUTPUT);
    pinMode(pinoEcho, INPUT); 
}

float SensorDistancia::getDistancia(){
    delay(10);
    digitalWrite(pinoTrigger, LOW);
    delay(2);
    digitalWrite(pinoTrigger, HIGH);
    delay(10);
    digitalWrite(pinoTrigger, LOW);
    long duracao = pulseIn(pinoEcho, HIGH);
    float distancia = duracao * 0.034 / 2;
    return distancia;
}
