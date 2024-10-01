#ifndef SENSORVELOCIDADE_H
#define SENSORVELOCIDADE_H

#include<Arduino.h>

#define MILISSEGUNDOS_POR_MINUTO 60000.0
#define INTERVALO_TEMPO 500

class SensorVelocidade{
  private:
    void (*callBackFunc)();
    int triggerPin;
    int pulsosPorVolta;
    volatile int contPulsos;
    long tempoAnterior;
  public:
    SensorVelocidade(int triggerPin, int pulsosPorVolta);
    void iniciar(void (*func)());
    void reset(); 
    float getRPM(); 
    void incPulso();   
    void parar();
    void continuar();
};

#endif