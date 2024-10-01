#include "SensorVelocidade.h"

SensorVelocidade::SensorVelocidade(int triggerPin, int pulsosPorVolta):
  triggerPin(triggerPin),
  pulsosPorVolta(pulsosPorVolta),
  contPulsos(0),
  tempoAnterior(millis()){}

void SensorVelocidade::iniciar(void (*func)()){  
  pinMode(triggerPin, INPUT);
  callBackFunc = func;
}

float SensorVelocidade::getRPM(){
  long decorrido = millis() - tempoAnterior;
  if (decorrido <= 0){
    return 0.0;
  }
  float rpm = ((float)contPulsos / (float)pulsosPorVolta) * MILISSEGUNDOS_POR_MINUTO / (float)decorrido;  
  return rpm;
}

void SensorVelocidade::incPulso(){
  contPulsos++;
}
void SensorVelocidade::reset(){
  tempoAnterior = millis();
  contPulsos = 0;
}

void SensorVelocidade::continuar(){  
  reset();  
  attachInterrupt(digitalPinToInterrupt(triggerPin), callBackFunc, FALLING);
}

void SensorVelocidade::parar(){
  detachInterrupt(digitalPinToInterrupt(triggerPin));
}
