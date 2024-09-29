#include "Controle.h"

Controle::Controle(Carro* c, ServoMotor* s, SensorDistancia* sens)
    : carro(c), servo(s), sensor(sens){}

void Controle::verificarObstaculo(){
    if (verificarFrente()) {
        carro->frear();
        status = C_PARADO;
        delay(500);
        if (!verificarFrente()){
          return;        
        }
        delay(500);
        bool obstaculoEsquerda = verificarLado(135);
        delay(500);
        bool obstaculoDireita = verificarLado(45);
        delay(500);
        if (!obstaculoEsquerda) {
            fazerCurvaEsquerda();
        }
        else if (!obstaculoDireita) {
            fazerCurvaDireta();
        }
        else {
            voltar();
        }        
    } 
}

void Controle::iniciar(){
  servo->girar(90);  
}

bool Controle::verificarFrente(){   
    long distancia =  sensor->medirDistancia();    
    return distancia < distanciaSegura;
}

bool Controle::verificarLado(int angulo) {
    servo->girar(angulo);
    delay(500);
    long distancia = sensor->medirDistancia();
    servo->girar(90);
    return distancia < distanciaSegura;
}

void Controle::parar(){
  carro->frear();
  status = C_PARADO;
  delay(1000);
  esperar = millis() + 1000;  
}

void Controle::fazerCurvaDireta(){
  carro->frear();
  status = C_GIRAR_DIREITA;  
  carro->girarDireita();
  esperar = millis() + 450;  
}

void Controle::fazerCurvaEsquerda(){
  carro->frear();
  status = C_GIRAR_ESQUERDA;  
  carro->girarEsquerda();
  esperar = millis() + 450;    
}


void Controle::voltar(){
  carro->frear();
  status = C_VOLTAR;  
  carro->girarEsquerda();
  esperar = millis() + 750;  
}

void Controle::loop(){  
  if (esperar <= millis()){
    switch(status) {
      case C_PARADO:
      case C_FRENTE:
        esperar = millis() + 500;
        verificarObstaculo();        
        if (status == C_PARADO){
          status=C_FRENTE;
          carro->moverFrente();
        }        
        break;
      case C_GIRAR_DIREITA:
      case C_GIRAR_ESQUERDA:
      case C_OBSTACULO:
      case C_VOLTAR:            
            parar();
        break;          
    }    
  }
  carro->loop();
}

