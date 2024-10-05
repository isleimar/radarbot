#include "Controle.h"

// Controle
Controle::Controle(Carro* c, ServoMotor* s, SensorDistancia* sens)
    : carro(c), servo(s), sensor(sens){
      estadoAtual = new EstadoParado(this);
}

void Controle::mudarEstado(EstadoControleBase* estadoNovo){
  estadoAtual->finalizar();
  delete estadoAtual;
  estadoAtual = estadoNovo;
  estadoNovo->iniciar();
  Serial.println(estadoNovo->getNomeEstado());
}

bool Controle::temObstaculo(){  
  return distanciaObstaculo() < DISTANCIA_SEGURA;
}

void Controle::iniciar(){}

void Controle::loop(){  
  estadoAtual->loop();
}

float Controle::distanciaObstaculo(){
  float distancia = sensor->getDistancia();  
  return distancia;
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

void Controle::sensorFrente(){
  servo->girar(90);
  delay(500);
}

void Controle::sensorDireita(){
  servo->girar(45);
  delay(500);
}

void Controle::sensorEsquerda(){
  servo->girar(135);
  delay(500);
}

// --------------------------
//       ESTADO CONTROLE
//---------------------------

EstadoControle::EstadoControle(Controle* controle):
  controle(controle),
  tempoFinal(millis()+1000){}

void EstadoControle::esperar(unsigned long esperarMilisegundos){
  tempoFinal = millis() + esperarMilisegundos;
}

void EstadoControle::loop(){
  if (tempoFinal < millis()) {
    executar();
  }
}

String EstadoControle::getNomeEstado(){}
void EstadoControle::iniciar(){}
void EstadoControle::obstaculoEncontrado(){}
void EstadoControle::finalizar(){}
void EstadoControle::executar(){}

// --------------------------
//       ESTADO PARADO
//---------------------------
EstadoParado::EstadoParado(Controle* controle):  EstadoControle(controle){}

String EstadoParado::getNomeEstado(){
  return "Estado Parado";
}

void EstadoParado::executar(){
  controle->mudarEstado(new EstadoAndando(controle));
}

void EstadoParado::iniciar(){
  controle->carroParar();
  controle->sensorFrente();
  esperar(1000);
}

// --------------------------
//       ESTADO ANDANDO
//---------------------------
EstadoAndando::EstadoAndando(Controle* controle):  EstadoControle(controle){}

String EstadoAndando::getNomeEstado(){
  return "Estado Andando";
}

void EstadoAndando::iniciar(){
  if (controle->temObstaculo()){
    obstaculoEncontrado();
  } else {
    controle->carroAndar();
    controle->sensorFrente();
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
  controle->mudarEstado(new EstadoOlhandoDireita(controle));
}

// --------------------------
//   ESTADO OLHANDO DIREITA
//---------------------------
EstadoOlhandoDireita::EstadoOlhandoDireita(Controle* controle):  EstadoControle(controle){}

String EstadoOlhandoDireita::getNomeEstado(){
  return "Estado Olhando Direita";
}

void EstadoOlhandoDireita::iniciar(){
  controle->sensorDireita();
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
EstadoOlhandoEsquerda::EstadoOlhandoEsquerda(Controle* controle):  EstadoControle(controle){}

String EstadoOlhandoEsquerda::getNomeEstado(){
  return "Estado Olhando Esquerda";
}

void EstadoOlhandoEsquerda::iniciar(){
  controle->sensorEsquerda();
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

EstadoGirandoDireita::EstadoGirandoDireita(Controle* controle):  EstadoControle(controle){}

String EstadoGirandoDireita::getNomeEstado(){
  return "Estado Girando Direita";
}

void EstadoGirandoDireita::iniciar(){
  controle->sensorFrente();
  controle->carroVirarDireita();
  esperar(100);
}

void EstadoGirandoDireita::executar(){
  controle->carroParar();
  if (controle->temObstaculo()){
    controle->carroVirarDireita();
    esperar(1000);    
  }else{
     controle->mudarEstado(new EstadoParado(controle));   
  }
}

// --------------------------
//  ESTADO GIRANDO ESQUERDA
//---------------------------

EstadoGirandoEsquerda::EstadoGirandoEsquerda(Controle* controle):  EstadoControle(controle){}

String EstadoGirandoEsquerda::getNomeEstado(){
  return "Estado Girando Esquerda";
}

void EstadoGirandoEsquerda::iniciar(){
  controle->sensorFrente();
  controle->carroVirarEsquerda();
  esperar(100);
}

void EstadoGirandoEsquerda::executar(){
  controle->carroParar();
  if (controle->temObstaculo()){
    controle->carroVirarEsquerda();
    esperar(1000);    
  }else{
     controle->mudarEstado(new EstadoParado(controle));   
  }
}


// --------------------------
//       ESTADO VOLTAR
//---------------------------

EstadoVoltar::EstadoVoltar(Controle* controle):  EstadoControle(controle){}

String EstadoVoltar::getNomeEstado(){
  return "Estado Voltando";
}

void EstadoVoltar::iniciar(){
  controle->sensorFrente();
  controle->carroVoltar();
  esperar(100);
}

void EstadoVoltar::executar(){
  controle->carroParar();
  if (controle->temObstaculo()){
    controle->mudarEstado(new EstadoOlhandoDireita(controle));    
    esperar(100);    
  }else{
     controle->mudarEstado(new EstadoParado(controle));
  }
}
