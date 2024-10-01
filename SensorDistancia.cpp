#include "SensorDistancia.h"
#include <Arduino.h>

SensorDistancia::SensorDistancia(int trigger, int echo): 
    pinoTrigger(trigger), 
    pinoEcho(echo),
    distancia(0),
    status(SD_PARADO)    
     {}

void SensorDistancia::iniciar() {
    pinMode(pinoTrigger, OUTPUT);
    pinMode(pinoEcho, INPUT);
    status = SD_AGUARDAR;
    esperar = millis() + 100;
}

void SensorDistancia::parar(){
    status = SD_PARADO;
    esperar = millis() + 100;
    distancia = 0;
}

void SensorDistancia::continuar(){
    status = SD_AGUARDAR;
    esperar = millis() + 100;
    distancia = 0;
}

int SensorDistancia::getDistancia(){
    return distancia;
}

void SensorDistancia::loop(){
    if (esperar < millis()){
        switch (status){
        case SD_PARADO:
            esperar = millis() + 100;
            break;
        case SD_AGUARDAR:
            digitalWrite(pinoTrigger, LOW);   
            status = SD_TRIGGER;
            esperar = millis() + 2;
            break;
        case SD_TRIGGER:
            digitalWrite(pinoTrigger, HIGH);
            status = SD_LER;
            esperar = millis() + 5;            
            break;
        case SD_LER:
            digitalWrite(pinoTrigger, LOW);
            status = SD_AGUARDAR;
            long duracao = pulseIn(pinoEcho, HIGH);
            if (duracao > 0){
                distancia = duracao * 0.034 / 2;
                // Serial.println(distancia);
            }            
            esperar = millis() + 400;
            break;
        default:
            status = SD_PARADO;
            esperar = millis() + 100;
            break;
        }
    }

}