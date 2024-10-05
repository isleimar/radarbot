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
    unsigned long pulsosEsquerda;
    unsigned long pulsosDireita;
    int circRodas; //unidades
    float velocidade; //distancia da circunferencia das rodas por segundo    
    float rmpAlvo() const;
    void novoPwm(float alvo, Motor* ph, SensorVelocidade* sv);
    void mudarDirecao(DirecaoMotor direcaoDireita, DirecaoMotor direcaoEsquerda);
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