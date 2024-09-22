#ifndef CARRO_H
#define CARRO_H

#define TEMPO_CURVA 400
#define TEMPO_180   900

#include <Arduino.h>

class Carro{
    private:
        int pinoEnA;
        int pinoIn1;
        int pinoIn2;
        int pinoIn3;
        int pinoIn4;
        int pinoEnB;
        int velocidade;        
    public:
        Carro(int ena, int in1, int in2, int in3, int in4, int enb);
        int getVelocidade();
        void setVelocidade(int valor);
        void iniciar();
        void moverFrente();
        void parar();
        void virarEsquerda();
        void virarDireita();
        void virar180();
};

#endif;