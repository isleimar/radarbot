#include "Carro.h"
#include "ServoMotor.h"
#include "SensorDistancia.h"
#include "Controle.h"

//CARRO
#define PIN_ENA 5
#define PIN_IN1 4
#define PIN_IN2 7
#define PIN_IN3 8
#define PIN_IN4 9
#define PIN_ENB 6
#define VELOCIDADE 115

//SERVO
#define PIN_SERVO 10

//SENSOR
#define PIN_TRIGGER 12
#define PIN_ECHO    13


Carro carro(PIN_ENA, PIN_IN1, PIN_IN2, PIN_IN3, PIN_IN4, PIN_ENB);
ServoMotor servo(PIN_SERVO);
SensorDistancia sensor(PIN_TRIGGER,PIN_ECHO);
Controle controle(&carro, &servo, &sensor);

void setup(){
    // Serial.begin(9600);
    carro.iniciar();
    carro.setVelocidade(VELOCIDADE);
    servo.iniciar();    
    sensor.iniciar();
    servo.girar(90);    
    carro.moverFrente();
}

void loop(){
    controle.verificarObstaculo();
    delay(100);
}

