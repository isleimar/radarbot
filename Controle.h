#ifndef CONTROLE_H
#define CONTROLE_H

#include "Carro.h"
#include "ServoMotor.h"
#include "SensorDistancia.h"
#include <Arduino.h>

class Controle {
    private:
        Carro* carro;
        ServoMotor* servo;
        SensorDistancia* sensor;
        const int distanciaSegura = 20;
    public:
        Controle(Carro* c, ServoMotor* s, SensorDistancia* sens);
        void verificarObstaculo();
        bool verificarFrente();
        bool verificarLado(int angulo);
        void fazerCurva(int angulo);
};

#endif