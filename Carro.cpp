#include "Carro.h"

Carro::Carro(Motor* mtDireita, Motor* mtEsquerda, SensorMotor* smDireita, SensorMotor* smEsquerda, int circRodas):
    mtDireita(mtDireita),
    mtEsquerda(mtEsquerda),
    smDireita(smDireita),
    smEsquerda(smEsquerda),
    circRodas(circRodas),
    velocidade(0),
    pulsosDireita(0),
    pulsosEsquerda(0){}

float Carro::rmpAlvo() const{
  return (this->velocidade * 60.0) / this->circRodas;
}

void Carro::novoPwm(float alvo, Motor* mt, SensorMotor* sv){
  float rpm = sv->getRPM();
  int error = constrain((alvo - rpm), -100, 100);  
  int novoPwm = map(error, -100, 100, 0, 255);  
  mt->definirPwm(novoPwm);
}

void Carro::mudarDirecao(DirecaoMotor direcaoDireita, DirecaoMotor direcaoEsquerda){
  pulsosDireita += smDireita->getPulsos();
  pulsosEsquerda += smEsquerda->getPulsos();
  smDireita->continuar();
  smEsquerda->continuar();
  mtDireita->definirDirecaoMotor(direcaoDireita);
  mtEsquerda->definirDirecaoMotor(direcaoEsquerda);
}

void Carro::definirVelocidade(float velocidade){
  this->velocidade = velocidade;
}

long Carro::getDistanciaPercorrida() const{  
  float distDireita = smDireita->getVoltasTotal() * circRodas;
  float distEsquerda = smEsquerda->getVoltasTotal() * circRodas;
  return (long)((distDireita + distEsquerda) / 2);
}

void Carro::moverFrente(){
  mudarDirecao(FRENTE, FRENTE);
}

void Carro::moverTras(){
  mudarDirecao(TRAS, TRAS);
}

void Carro::girarDireita(){
  mudarDirecao(TRAS, FRENTE);  
}

void Carro::girarEsquerda(){
  mudarDirecao(FRENTE, TRAS);
}

void Carro::frear(){
  mtDireita->pararMotor();
  mtEsquerda->pararMotor();
  smDireita->parar();
  smEsquerda->parar();
}

void Carro::loop(){
  float alvo = rmpAlvo();  
  if (mtDireita->lerDirecaoMotor() != PARADO){    
    novoPwm(alvo, mtDireita, smDireita);
  }
  if (mtEsquerda->lerDirecaoMotor() != PARADO){    
    novoPwm(alvo, mtEsquerda, smEsquerda);
  }
}

