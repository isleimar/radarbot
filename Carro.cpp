#include "Carro.h"

Carro::Carro(Motor* mtDireita, Motor* mtEsquerda, SensorVelocidade* svDireta, SensorVelocidade* svEsquerda, int circRodas):
    mtDireita(mtDireita),
    mtEsquerda(mtEsquerda),
    svDireta(svDireta),
    svEsquerda(svEsquerda),
    circRodas(circRodas),
    velocidade(0),
    pulsosDireita(0),
    pulsosEsquerda(0){}

float Carro::rmpAlvo() const{
  return (this->velocidade * 60.0) / this->circRodas;
}

void Carro::novoPwm(float alvo, Motor* mt, SensorVelocidade* sv){
  float rpm = sv->getRPM();
  int error = constrain((alvo - rpm), -100, 100);  
  int novoPwm = map(error, -100, 100, 0, 128);  
  mt->definirPwm(novoPwm);
}

void Carro::mudarDirecao(DirecaoMotor direcaoDireita, DirecaoMotor direcaoEsquerda){
  pulsosDireita += svDireta->getPulsos();
  pulsosEsquerda += svEsquerda->getPulsos();
  svDireta->continuar();
  svEsquerda->continuar();
  mtDireita->definirDirecaoMotor(direcaoDireita);
  mtEsquerda->definirDirecaoMotor(direcaoEsquerda);
}

void Carro::definirVelocidade(float velocidade){
  this->velocidade = velocidade;
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

