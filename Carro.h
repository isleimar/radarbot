#ifndef CARRO_H
#define CARRO_H

#include <Arduino.h>

class Carro{
    private:
        int pinoMotorEsq;
        int pinoMotorDir;
    public:
        Carro(int motorEsq, int motorDir);
        void iniciar();
        void moverFrente();
        void parar();
        void virarEsquerda();
        void virarDireita();
        void virar180();
};

#endif;