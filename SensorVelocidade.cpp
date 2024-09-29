#include "SensorVelocidade.h"

SensorVelocidade::SensorVelocidade(int triggerPin, int pulsosPorVolta):
  triggerPin(triggerPin),
  pulsosPorVolta(pulsosPorVolta),
  contPulsos(0),
  tempoAnterior(millis()){
    pinMode(triggerPin, INPUT);
  }

void SensorVelocidade::setCallback(void (*func)()){
  callBackFunc = func;
}

int SensorVelocidade::getTriggerPin(){
  return this->triggerPin;
}

float SensorVelocidade::getRPM(){
  long decorrido = millis() - tempoAnterior;
  if ((int)decorrido == 0){
    return 0.0;
  }
  float rpm = ((float)contPulsos / (float)pulsosPorVolta) * MILISSEGUNDOS_POR_MINUTO / (float)decorrido;
  if (decorrido > INTERVALO_TEMPO){
    tempoAnterior = millis();
    contPulsos = 0;
  }

  return rpm;
}

void SensorVelocidade::incPulso(){
  contPulsos++;
}

void SensorVelocidade::iniciar(){  
  tempoAnterior = millis();
  contPulsos = 0;  
  attachInterrupt(digitalPinToInterrupt(triggerPin), callBackFunc, FALLING);
}

void SensorVelocidade::parar(){
  detachInterrupt(digitalPinToInterrupt(triggerPin));
}
