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
    volatile unsigned long pulsosParcial;
    unsigned long pulsosTotal;    
    unsigned long tempoAnterior;
  public:
    SensorVelocidade(int triggerPin, int pulsosPorVolta);
    void iniciar(void (*func)());
    void incPulso();
    unsigned long getPulsos() const;
    unsigned long getPulsosTotal() const;
    float getRPM(); 
    void reset(); 
    void parar();
    void continuar();
};

#endif