#include "Controle.h"

// Controle
Controle::Controle(Carro* c, ServoMotor* s, SensorDistancia* sens)
    : carro(c), servo(s), sensor(sens){
      estadoAtual = new EstadoParado(this);
}

void Controle::mudarEstado(EstadoControleBase* estadoNovo){
  delete estadoAtual;
  estadoAtual = estadoNovo;
}

bool Controle::temObstaculo(){
  return distanciaObstaculo() < DISTANCIA_SEGURA;
}

void Controle::iniciar(){}

void Controle::loop(){  
  estadoAtual->loop();
}

float Controle::distanciaObstaculo(){
  return sensor->getDistancia();
}

void Controle::carroParar(){
  carro->frear();
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
}

void Controle::sensorDireita(){
  servo->girar(45);
}

void Controle::sensorEsquerda(){
  servo->girar(135);
}

// --------------------------
//       ESTADO CONTROLE
//---------------------------

EstadoControle::EstadoControle(Controle* controle):
  controle(controle),
  tempoFinal(millis()){}

void EstadoControle::esperar(unsigned long esperarMilisegundos){
  tempoFinal = millis() + esperarMilisegundos;
}

void EstadoControle::loop(){
  if (tempoFinal < millis()) {
    executar();
  }
}

void EstadoControle::iniciar(){}
void EstadoControle::obstaculoEncontrado(){}
void EstadoControle::finalizar(){}
void EstadoControle::executar(){}

// --------------------------
//       ESTADO PARADO
//---------------------------
EstadoParado::EstadoParado(Controle* controle):  EstadoControle(controle){}

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
//       ESTADO OLHANDO DIREITA
//---------------------------
EstadoOlhandoDireita::EstadoOlhandoDireita(Controle* controle):  EstadoControle(controle){}

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
















// void Controle::esperar(int millisegundos){
//   tempoEsperar = millis() + millisegundos;
// }

// void Controle::paraFrente(){
//   servo->girar(90);
//   carro->moverFrente();
//   esperar(100);
// }

// void Controle::olharParaDireita(){
//   carro->frear();
//   servo->girar(45); //Girar ServoMotor para a Direita
//   status = C_OLHAR_DIREITA;
//   esperar(2000);
// }

// void Controle::olharParaEsquerda(){
//   carro->frear();
//   servo->girar(135); //Girar ServoMotor para a Esquerda
//   status = C_OLHAR_ESQUERDA;
//   esperar(2000);
// }

// void Controle::fazerCurvaDireta(){
//   servo->girar(90);
//   carro->frear();
//   status = C_GIRAR_DIREITA;  
//   carro->girarDireita();
//   esperar(TEMPO_CURVA);  
// }

// void Controle::fazerCurvaEsquerda(){
//   servo->girar(90);
//   carro->frear();
//   status = C_GIRAR_ESQUERDA;  
//   carro->girarEsquerda();
//   esperar(TEMPO_CURVA);
// }

// bool Controle::temObstaculo(){
//   return sensor->getDistancia() < DISTANCIA_SEGURA;
// }

// void Controle::parar(){
//   carro->frear();
//   status = C_PARADO;  
//   esperar(1000);
// }

// void Controle::loop(){  
//   if (tempoEsperar <= millis()){    
//     switch(status) {
//       case C_PARADO:
//         // Serial.println("PARADO");
//         status=C_FRENTE;
//         paraFrente();
//       break;
//       case C_FRENTE:        
//         // Serial.println("FRENTE");
//         if (temObstaculo()) {
//           olharParaDireita();            
//         } else {
//           esperar(100);
//         }        
//         break;
//       case C_OLHAR_DIREITA: //Depois de olhar para a Direita
//         // Serial.println("OLHAR DIREITA");
//         if (temObstaculo()) {
//           olharParaEsquerda();          
//         } else {
//           fazerCurvaDireta();          
//         }
//         break;
//       case C_OLHAR_ESQUERDA: //Depois de olhar para Esquerda        
//         // Serial.println("OLHAR ESQUERDA");
//         fazerCurvaEsquerda();
//         break;  
//       case C_GIRAR_DIREITA:
//         // Serial.println("GIRAR DIREITA");
//       case C_GIRAR_ESQUERDA:
//         // Serial.println("GIRAR ESQUERDA");
//         carro->frear();
//         if (temObstaculo()) {          
//           status=C_OLHAR_DIREITA;
//           esperar(1000);          
//         } else {
//           status=C_PARADO;
//           esperar(500);
//         }        
//         break;                
//     }    
//   }
//   carro->loop();
//   sensor->loop();
// }

