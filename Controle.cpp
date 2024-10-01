#include "Controle.h"

Controle::Controle(Carro* c, ServoMotor* s, SensorDistancia* sens)
    : carro(c), servo(s), sensor(sens){}

void Controle::iniciar(){
  servo->girar(90);  
}

void Controle::esperar(int millisegundos){
  tempoEsperar = millis() + millisegundos;
}

void Controle::paraFrente(){
  servo->girar(90);
  carro->moverFrente();
  esperar(100);
}

void Controle::olharParaDireita(){
  carro->frear();
  servo->girar(45); //Girar ServoMotor para a Direita
  status = C_OLHAR_DIREITA;
  esperar(2000);
}

void Controle::olharParaEsquerda(){
  carro->frear();
  servo->girar(135); //Girar ServoMotor para a Esquerda
  status = C_OLHAR_ESQUERDA;
  esperar(2000);
}

void Controle::fazerCurvaDireta(){
  servo->girar(90);
  carro->frear();
  status = C_GIRAR_DIREITA;  
  carro->girarDireita();
  esperar(TEMPO_CURVA);  
}

void Controle::fazerCurvaEsquerda(){
  servo->girar(90);
  carro->frear();
  status = C_GIRAR_ESQUERDA;  
  carro->girarEsquerda();
  esperar(TEMPO_CURVA);
}

bool Controle::temObstaculo(){
  return sensor->getDistancia() < DISTANCIA_SEGURA;
}

void Controle::parar(){
  carro->frear();
  status = C_PARADO;  
  esperar(1000);
}

void Controle::loop(){  
  if (tempoEsperar <= millis()){    
    switch(status) {
      case C_PARADO:
        // Serial.println("PARADO");
        status=C_FRENTE;
        paraFrente();
      break;
      case C_FRENTE:        
        // Serial.println("FRENTE");
        if (temObstaculo()) {
          olharParaDireita();            
        } else {
          esperar(100);
        }        
        break;
      case C_OLHAR_DIREITA: //Depois de olhar para a Direita
        // Serial.println("OLHAR DIREITA");
        if (temObstaculo()) {
          olharParaEsquerda();          
        } else {
          fazerCurvaDireta();          
        }
        break;
      case C_OLHAR_ESQUERDA: //Depois de olhar para Esquerda        
        // Serial.println("OLHAR ESQUERDA");
        fazerCurvaEsquerda();
        break;  
      case C_GIRAR_DIREITA:
        // Serial.println("GIRAR DIREITA");
      case C_GIRAR_ESQUERDA:
        // Serial.println("GIRAR ESQUERDA");
        carro->frear();
        if (temObstaculo()) {          
          status=C_OLHAR_DIREITA;
          esperar(1000);          
        } else {
          status=C_PARADO;
          esperar(500);
        }        
        break;                
    }    
  }
  carro->loop();
  sensor->loop();
}

