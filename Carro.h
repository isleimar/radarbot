#ifndef CARRO_H
#define CARRO_H

#include <Arduino.h>
#include "Motor.h"
#include "SensorVelocidade.h"

class Carro{
  private:
    Motor* mtDireita;
    Motor* mtEsquerda;    
    SensorVelocidade* svDireta;
    SensorVelocidade* svEsquerda;
    int circRodas; //unidades
    float velocidade; //circunferencia das rodas por segundo    
    float rmpAlvo();
    void novoPwm(float alvo, Motor* ph, SensorVelocidade* sv);
  public:
    Carro(Motor* mtDireita, Motor* mtEsquerda, SensorVelocidade* svDireta, SensorVelocidade* svEsquerda, int circRodas);
    void definirVelocidade(float velocidade);
    void moverFrente();
    void moverTras();
    void girarDireita();
    void girarEsquerda();
    void frear();
    void loop();
};

#endif;