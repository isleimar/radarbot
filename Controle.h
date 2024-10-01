#ifndef CONTROLE_H
#define CONTROLE_H

#include "Carro.h"
#include "ServoMotor.h"
#include "SensorDistancia.h"
#include <Arduino.h>

#define DISTANCIA_SEGURA 30
#define TEMPO_CURVA 500
#define TEMPO_VOLTA 1000

enum StatusControle{
  C_PARADO         = 0,  
  C_FRENTE         = 1,
  C_OLHAR_DIREITA  = 2,
  C_OLHAR_ESQUERDA = 3,  
  C_GIRAR_DIREITA  = 4,
  C_GIRAR_ESQUERDA = 5,
  C_VOLTAR         = 6
};

class Controle {
    private:
        Carro* carro;
        ServoMotor* servo;
        SensorDistancia* sensor;        
        StatusControle status;
        long tempoEsperar;
        void esperar(int millisegundos);        
    public:
        Controle(Carro* c, ServoMotor* s, SensorDistancia* sens);        
        bool temObstaculo();        
        void parar();
        void paraFrente();
        void fazerCurvaDireta();
        void fazerCurvaEsquerda();
        void olharParaDireita();
        void olharParaEsquerda();        
        void loop();
        void iniciar();
};

#endif