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
  pulsosParcial++;
}

unsigned long SensorVelocidade::getPulsos() const{
  return pulsosParcial;
}

unsigned long SensorVelocidade::getPulsosTotal() const{
  return pulsosTotal + pulsosParcial;
}

float SensorVelocidade::getVoltas() const{
  return ((float)getPulsos() / pulsosPorVolta);
}

float SensorVelocidade::getVoltasTotal() const{
  return ((float)getPulsosTotal() / pulsosPorVolta);
}

float SensorVelocidade::getRPM(){
  long decorrido = millis() - tempoAnterior;
  if (decorrido <= 0){
    return 0.0;
  }
  float rpm = (getVoltas() / (float)decorrido) *  MILISSEGUNDOS_POR_MINUTO;  
  return rpm;
}

void SensorVelocidade::reset(){
  pulsosTotal += pulsosParcial;
  tempoAnterior = millis();
  pulsosParcial = 0;
}

void SensorVelocidade::parar(){
  detachInterrupt(digitalPinToInterrupt(triggerPin));
}

void SensorVelocidade::continuar(){  
  reset();  
  attachInterrupt(digitalPinToInterrupt(triggerPin), callBackFunc, FALLING);
}