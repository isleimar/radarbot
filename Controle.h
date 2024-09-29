#ifndef CONTROLE_H
#define CONTROLE_H

#include "Carro.h"
#include "ServoMotor.h"
#include "SensorDistancia.h"
#include <Arduino.h>

enum StatusControle{
  C_PARADO         = 0,
  C_FRENTE         = 1,
  C_OBSTACULO      = 2,
  C_GIRAR_DIREITA  = 3,
  C_GIRAR_ESQUERDA = 4,
  C_VOLTAR         = 5
};

class Controle {
    private:
        Carro* carro;
        ServoMotor* servo;
        SensorDistancia* sensor;
        const int distanciaSegura = 30;
        StatusControle status;
        long esperar;
    public:
        Controle(Carro* c, ServoMotor* s, SensorDistancia* sens);
        void verificarObstaculo();
        bool verificarFrente();
        bool verificarLado(int angulo);
        void parar();
        void fazerCurvaDireta();
        void fazerCurvaEsquerda();
        void voltar();
        void loop();
        void iniciar();
};

#endif