#include "Controle.h"

Controle::Controle(Carro* c, ServoMotor* s, SensorDistancia* sens)
    : carro(c), servo(s), sensor(sens) {}

void Controle::verificarObstaculo(){
    if (verificarFrente()) {
        carro->parar();
        bool obstaculoEsquerda = verificarLado(45);
        bool obstaculoDireita = verificarLado(135);
        if (!obstaculoEsquerda) {
            fazerCurva(45);
        }
        else if (!obstaculoDireita) {
            fazerCurva(135);
        }
        else {
            fazerCurva(180);
        }
        carro->moverFrente();
    }
}

bool Controle::verificarFrente(){
    long distancia = sensor->medirDistancia();
    return distancia < distanciaSegura;
}

bool Controle::verificarLado(int angulo) {
    servo->girar(angulo);
    delay(500);
    long distancia = sensor->medirDistancia();
    servo->girar(90);
    return distancia < distanciaSegura;
}

void Controle::fazerCurva(int angulo) {
    if (angulo == 45) {
        carro->virarEsquerda();
        carro->parar();
        delay(500);    
    } else if (angulo == 135){
        carro->virarDireita();
        carro->parar();
        delay(500);
    } else if (angulo == 180) {
        carro->virar180();
        carro->parar();
        delay(500);
        carro->moverFrente();        
    } 
}

