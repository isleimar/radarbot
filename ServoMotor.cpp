#include "ServoMotor.h"

ServoMotor::ServoMotor(int pino): pino(pino){}

void ServoMotor::iniciar(){
    servo.attach(pino);
}

void ServoMotor::girar(int angulo){
    servo.write(angulo);
}