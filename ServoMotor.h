#ifndef SERVOMOTOR_H
#define SERVOMOTOR_H

#include <Servo.h>

class ServoMotor {
    private:
        Servo servo;
        int pino;
    public:
        ServoMotor(int pino);
        void iniciar();
        void girar(int angulo);
};

#endif