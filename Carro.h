#ifndef CARRO_H
#define CARRO_H

#include <Arduino.h>
#include "Motor.h"
#include "SensorMotor.h"

class Carro{
  private:
    Motor* mtDireita;
    Motor* mtEsquerda;    
    SensorMotor* smDireita;
    SensorMotor* smEsquerda;
    unsigned long pulsosEsquerda;
    unsigned long pulsosDireita;
    int circRodas; //unidades
    float velocidade; //distancia da circunferencia das rodas por segundo    
    float rmpAlvo() const;
    void novoPwm(float alvo, Motor* ph, SensorMotor* sm);
    void mudarDirecao(DirecaoMotor direcaoDireita, DirecaoMotor direcaoEsquerda);
  public:
    Carro(Motor* mtDireita, Motor* mtEsquerda, SensorMotor* smDireita, SensorMotor* smEsquerda, int circRodas);    
    void definirVelocidade(float velocidade);
    long getDistanciaPercorrida() const;
    void moverFrente();
    void moverTras();
    void girarDireita();
    void girarEsquerda();
    void frear();
    void loop();
};

#endif;