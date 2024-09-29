#include "Carro.h"

Carro::Carro(Motor* mtDireita, Motor* mtEsquerda, SensorVelocidade* svDireta, SensorVelocidade* svEsquerda, int circRodas):
    mtDireita(mtDireita),
    mtEsquerda(mtEsquerda),
    svDireta(svDireta),
    svEsquerda(svDireta),
    circRodas(circRodas),
    velocidade(0){}

void Carro::definirVelocidade(float velocidade){
  this->velocidade = velocidade;
}

float Carro::rmpAlvo(){
  return (this->velocidade * 60.0) / this->circRodas;
}

void Carro::moverFrente(){
  svDireta->iniciar();
  svEsquerda->iniciar();
  mtDireita->definirDirecaoMotor(FRENTE);
  mtEsquerda->definirDirecaoMotor(FRENTE);
}

void Carro::moverTras(){
  svDireta->iniciar();
  svEsquerda->iniciar();
  mtDireita->definirDirecaoMotor(TRAS);
  mtEsquerda->definirDirecaoMotor(TRAS);
}

void Carro::girarDireita(){
  svDireta->iniciar();
  svEsquerda->iniciar();
  mtDireita->definirDirecaoMotor(TRAS);
  mtEsquerda->definirDirecaoMotor(FRENTE);
}

void Carro::girarEsquerda(){
  svDireta->iniciar();
  svEsquerda->iniciar();
  mtDireita->definirDirecaoMotor(FRENTE);
  mtEsquerda->definirDirecaoMotor(TRAS);
}

void Carro::frear(){
  mtDireita->pararMotor();
  mtEsquerda->pararMotor();
  svDireta->parar();
  svEsquerda->parar();
}

void Carro::loop(){
  float alvo = rmpAlvo();  
  if (mtDireita->lerDirecaoMotor() != PARADO){    
    novoPwm(alvo, mtDireita, svDireta);
  }
  if (mtEsquerda->lerDirecaoMotor() != PARADO){    
    novoPwm(alvo, mtEsquerda, svEsquerda);
  }
}

void Carro::novoPwm(float alvo, Motor* mt, SensorVelocidade* sv){
  float rpm = sv->getRPM();
  int error = alvo - rpm;
  // int pwm = mt->lerPwm();
  int novoPwm = constrain(map(error, -100, 100, 0, 255), 0, 128);  
  mt->definirPwm(novoPwm);
}