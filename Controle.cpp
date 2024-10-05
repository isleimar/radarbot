#include "Controle.h"

// Controle
Controle::Controle(Carro* c, ServoMotor* s, SensorDistancia* sens)
    : carro(c), servo(s), sensor(sens){
      estadoAtual = new EstadoParado(this);
}

void Controle::mudarEstado(EstadoControleBase* estadoNovo){
  if (estadoAtual != nullptr){
    estadoAtual->finalizar();
    delete estadoAtual;  
  }  
  // Serial.println(estadoNovo->getDescricaoEstado());
  estadoAtual = estadoNovo;  
  estadoNovo->iniciar();
}

float Controle::distanciaObstaculo() const{
  float distancia = sensor->getDistancia();  
  return distancia;
}

bool Controle::temObstaculo() const{  
  return distanciaObstaculo() < DISTANCIA_SEGURA;
}

void Controle::iniciar(){}

unsigned long Controle::getDistanciaPercorrida() const {
  return carro->getDistanciaPercorrida();
}

void Controle::loop(){
  if (estadoAtual != nullptr){
    estadoAtual->loop();
  }
  carro->loop();  
}

void Controle::carroParar(){
  carro->frear();
}

void Controle::carroVoltar(){
  carro->moverTras();
}

void Controle::carroAndar(){
  carro->moverFrente();
}

void Controle::carroVirarDireita(){
  carro->girarDireita();
}

void Controle::carroVirarEsquerda(){
  carro->girarEsquerda();
}

void Controle::girarSensorFrente(){
  servo->girar(90);  
}

void Controle::girarSensorDireita(){
  servo->girar(45);  
}

void Controle::girarSensorEsquerda(){
  servo->girar(135);  
}

// --------------------------
//       ESTADO CONTROLE
//---------------------------

EstadoControle::EstadoControle(Controle* controle):
  controle(controle),
  tempoFinal(millis()+100){
    distanciaInicial = controle->getDistanciaPercorrida();
  }

void EstadoControle::esperar(unsigned long esperarMilisegundos){
  tempoFinal = millis() + esperarMilisegundos;
}

void EstadoControle::loop(){
  // Serial.print("Distancia Percorrida: ");
  // Serial.println(getDistanciaPercorrida());
  if (tempoFinal < millis()) {
    executar();
  }
}

String EstadoControle::getDescricaoEstado(){
  return descricaoEstado;
}

unsigned long EstadoControle::getDistanciaPercorrida() const{
  return controle->getDistanciaPercorrida() - distanciaInicial;
}

void EstadoControle::iniciar(){}
void EstadoControle::obstaculoEncontrado(){}
void EstadoControle::finalizar(){}
void EstadoControle::executar(){}

// --------------------------
//       ESTADO PARADO
//---------------------------

void EstadoParado::iniciar(){
  controle->carroParar();
  controle->girarSensorFrente();
  esperar(1000);
}

void EstadoParado::executar(){
  controle->mudarEstado(new EstadoAndando(controle));
}

// --------------------------
//       ESTADO ANDANDO
//---------------------------

void EstadoAndando::iniciar(){
  controle->girarSensorFrente();
  delay(1000);
  if (controle->temObstaculo()){
    obstaculoEncontrado();
  } else {
    controle->carroAndar();
  }
}

void EstadoAndando::executar(){  
  if (controle->temObstaculo()){
    obstaculoEncontrado();
  }
  esperar(100);
}

void EstadoAndando::obstaculoEncontrado(){
  controle->carroParar();
  delay(500);
  if (controle->temObstaculo()){
    controle->mudarEstado(new EstadoOlhandoDireita(controle));
  } else {
    iniciar();
  }
}

// --------------------------
//   ESTADO OLHANDO DIREITA
//---------------------------

void EstadoOlhandoDireita::iniciar(){
  controle->girarSensorDireita();
  esperar(100);
}

void EstadoOlhandoDireita::executar(){
  if (controle->temObstaculo()){
    controle->mudarEstado(new EstadoOlhandoEsquerda(controle));
  } else {
    controle->mudarEstado(new EstadoGirandoDireita(controle));
  }  
}

// --------------------------
//  ESTADO OLHANDO ESQUERDA
//---------------------------

void EstadoOlhandoEsquerda::iniciar(){
  controle->girarSensorEsquerda();
  esperar(100);
}

void EstadoOlhandoEsquerda::executar(){
  if (controle->temObstaculo()){
    controle->mudarEstado(new EstadoVoltar(controle));
  } else {
    controle->mudarEstado(new EstadoGirandoEsquerda(controle));
  }
}

// --------------------------
//  ESTADO GIRANDO DIREITA
//---------------------------

void EstadoGirandoDireita::iniciar(){
  controle->girarSensorFrente();
  controle->carroVirarDireita();
  // esperar(100);
}

void EstadoGirandoDireita::executar(){
  if (getDistanciaPercorrida() > 0){
    controle->carroParar();  
    if (controle->temObstaculo()) {
      controle->mudarEstado(new EstadoOlhandoDireita(controle));
    } else {
      controle->mudarEstado(new EstadoParado(controle));
    }
  }
}

// --------------------------
//  ESTADO GIRANDO ESQUERDA
//---------------------------

void EstadoGirandoEsquerda::iniciar(){
  controle->girarSensorFrente();
  controle->carroVirarEsquerda();
  // esperar(100);
}

void EstadoGirandoEsquerda::executar(){
  if (getDistanciaPercorrida() > 0){
    controle->carroParar();  
    if (controle->temObstaculo()) {
      controle->mudarEstado(new EstadoOlhandoEsquerda(controle));
    } else {
      controle->mudarEstado(new EstadoParado(controle));
    }
  }
}

// --------------------------
//       ESTADO VOLTAR
//---------------------------

void EstadoVoltar::iniciar(){
  controle->girarSensorFrente();
  controle->carroVoltar();
  // esperar(100);
}

void EstadoVoltar::executar(){
  if (getDistanciaPercorrida() > 1){
    controle->carroParar();  
    if (controle->temObstaculo()) {
      controle->mudarEstado(new EstadoOlhandoDireita(controle));
    } else {
      controle->mudarEstado(new EstadoParado(controle));
    }
  }  
}
