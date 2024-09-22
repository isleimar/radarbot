#include "Carro.h"

Carro:: Carro(int ena, int in1, int in2, int in3, int in4, int enb)
    : pinoEnA(ena), 
      pinoIn1(in1), 
      pinoIn2(in2), 
      pinoIn3(in3), 
      pinoIn4(in4), 
      pinoEnB(enb)
      {
        velocidade = 32;
      }

int Carro::getVelocidade() {
    return velocidade;
}

void Carro::setVelocidade(int valor){
    velocidade = valor;
    analogWrite(pinoEnA, velocidade);
    analogWrite(pinoEnB, velocidade);    
}

void Carro::iniciar() {
    pinMode(pinoEnA, OUTPUT);
    pinMode(pinoIn1, OUTPUT);
    pinMode(pinoIn2, OUTPUT);
    pinMode(pinoIn3, OUTPUT);
    pinMode(pinoIn4, OUTPUT);
    pinMode(pinoEnB, OUTPUT);
    setVelocidade(velocidade);
}

void Carro::moverFrente() {
    analogWrite(pinoEnA, velocidade);
    analogWrite(pinoEnB, trunc(velocidade * 0.90));
    // analogWrite(pinoEnB, velocidade);    
    digitalWrite(pinoIn1, LOW);
    digitalWrite(pinoIn2, HIGH);
    digitalWrite(pinoIn3, LOW);    
    digitalWrite(pinoIn4, HIGH);
}

void Carro::parar() {
    digitalWrite(pinoIn1, LOW);
    digitalWrite(pinoIn2, LOW);
    digitalWrite(pinoIn3, LOW);
    digitalWrite(pinoIn4, LOW);
    delay(TEMPO_CURVA);
}

void Carro::virarEsquerda(){
    digitalWrite(pinoIn1, LOW);
    digitalWrite(pinoIn2, HIGH);
    digitalWrite(pinoIn3, HIGH);
    digitalWrite(pinoIn4, LOW);    
    delay(TEMPO_CURVA);
    parar();
}

void Carro::virarDireita(){
    digitalWrite(pinoIn1, HIGH);
    digitalWrite(pinoIn2, LOW);
    digitalWrite(pinoIn3, LOW);
    digitalWrite(pinoIn4, HIGH);    
    delay(TEMPO_CURVA);
    parar();
}

void Carro::virar180(){
    digitalWrite(pinoIn1, HIGH);
    digitalWrite(pinoIn2, LOW);
    digitalWrite(pinoIn3, LOW);
    digitalWrite(pinoIn4, HIGH);    
    delay(TEMPO_180);
    parar();
}