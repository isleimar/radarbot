#include "SensorVelocidade.h"

SensorVelocidade::SensorVelocidade(int triggerPin, int pulsosPorVolta):
  triggerPin(triggerPin),
  pulsosPorVolta(pulsosPorVolta),
  pulsosParcial(0),
  pulsosTotal(0),
  tempoAnterior(millis()){}

void SensorVelocidade::iniciar(void (*func)()){  
  pinMode(triggerPin, INPUT);
  callBackFunc = func;
}

void SensorVelocidade::incPulso(){
  contPulsos++;
}

unsigned long SensorVelocidade::getPulsos() const{
  return contPulsos;
}

float SensorVelocidade::getRPM(){
  long decorrido = millis() - tempoAnterior;
  if (decorrido <= 0){
    return 0.0;
  }
  float rpm = ((float)contPulsos / (float)pulsosPorVolta) * MILISSEGUNDOS_POR_MINUTO / (float)decorrido;  
  return rpm;
}

void SensorVelocidade::reset(){
  tempoAnterior = millis();
  contPulsos = 0;
}

void SensorVelocidade::parar(){
  detachInterrupt(digitalPinToInterrupt(triggerPin));
}

void SensorVelocidade::continuar(){  
  reset();  
  attachInterrupt(digitalPinToInterrupt(triggerPin), callBackFunc, FALLING);
}