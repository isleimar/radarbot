#include "Carro.h"
#include "ServoMotor.h"
#include "SensorDistancia.h"
#include "Controle.h"

Carro carro(9, 10);
ServoMotor servo(11);
SensorDistancia sensor(12,13);
Controle controle(&carro, &servo, &sensor);

void setup(){
    carro.iniciar();
    servo.iniciar();
    sensor.iniciar();
    servo.girar(90);
    carro.moverFrente();
}

void loop(){
    controle.verificarObstaculo();
    delay(100);
}
