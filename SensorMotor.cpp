#include "SensorMotor.h"

SensorMotor::SensorMotor(int triggerPin, int pulsosPorVolta):
  triggerPin(triggerPin),
  pulsosPorVolta(pulsosPorVolta),
  pulsosParcial(0),
  pulsosTotal(0),
  tempoAnterior(millis()){}

void SensorMotor::iniciar(void (*func)()){  
  pinMode(triggerPin, INPUT);
  callBackFunc = func;
}

void SensorMotor::incPulso(){
  pulsosParcial++;
}

unsigned long SensorMotor::getPulsos() const{
  return pulsosParcial;
}

unsigned long SensorMotor::getPulsosTotal() const{
  return pulsosTotal + pulsosParcial;
}

float SensorMotor::getVoltas() const{
  return ((float)getPulsos() / pulsosPorVolta);
}

float SensorMotor::getVoltasTotal() const{
  return ((float)getPulsosTotal() / pulsosPorVolta);
}

float SensorMotor::getRPM(){
  long decorrido = millis() - tempoAnterior;
  if (decorrido <= 0){
    return 0.0;
  }
  float rpm = (getVoltas() / (float)decorrido) *  MILISSEGUNDOS_POR_MINUTO;  
  return rpm;
}

void SensorMotor::reset(){
  pulsosTotal += pulsosParcial;
  tempoAnterior = millis();
  pulsosParcial = 0;
}

void SensorMotor::parar(){
  detachInterrupt(digitalPinToInterrupt(triggerPin));
}

void SensorMotor::continuar(){  
  reset();  
  attachInterrupt(digitalPinToInterrupt(triggerPin), callBackFunc, FALLING);
}