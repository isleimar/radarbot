#include "Controle.h"

// Controle
Controle::Controle(Carro* c, ServoMotor* s, SensorDistancia* sens)
    : carro(c), servo(s), sensor(sens), distanciaInicialEstado(0){
      estadoAtual = new EstadoParado(this);
}

void Controle::mudarEstado(EstadoControleBase* estadoNovo){
  if (estadoAtual != nullptr){
    estadoAtual->finalizar();
    delete estadoAtual;  
  
  }    
  distanciaInicialEstado = getDistanciaTotalPercorrida();  
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
  return getDistanciaTotalPercorrida() - distanciaInicialEstado;
}

unsigned long Controle::getDistanciaTotalPercorrida() const {
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
  if (lerDistanciaReal() < DISTANCIA_SEGURA){
    obstaculoEncontrado();
  } else {
    controle->carroAndar();
  }
  esperar(500);
}

int EstadoAndando::lerDistanciaReal() {
  distanciaMedida = controle->distanciaObstaculo();  
  distanciaInicialPercorrida =  (int)controle->getDistanciaPercorrida();  
  return distanciaMedida;
}

int EstadoAndando::getDistanciaEsperada(){
  int distacia = (distanciaMedida + distanciaInicialPercorrida) - (int)controle->getDistanciaPercorrida();  
  return distacia;
}

void EstadoAndando::loop(){
  if (getDistanciaEsperada() <  DISTANCIA_SEGURA) {
    obstaculoEncontrado();
  }
  EstadoControle::loop();
}

void EstadoAndando::executar(){
  distanciaMedida = controle->distanciaObstaculo();  
  esperar(500);
}

void EstadoAndando::obstaculoEncontrado(){  
  controle->carroParar();
  delay(1000);  
  if (lerDistanciaReal() < DISTANCIA_SEGURA){
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
  if (getDistanciaPercorrida() > 10){
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
  if (getDistanciaPercorrida() > 10){
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
  if (getDistanciaPercorrida() > 20){
    controle->carroParar();  
    if (controle->temObstaculo()) {
      controle->mudarEstado(new EstadoOlhandoDireita(controle));
    } else {
      controle->mudarEstado(new EstadoParado(controle));
    }
  }  
}
