#ifndef MOTOR_H
#define MOTOR_H

#include <Arduino.h>

#define SENTIDO_DIRETO    true
#define SENTIDO_INVERTIDO false

enum DirecaoMotor{
  PARADO = 0,
  FRENTE = 1,
  TRAS = 2
};

class Motor{
  private:
    int pinoEnb;
    int pinoIn1;
    int pinoIn2;
    boolean motorInvertido;
    DirecaoMotor direcaoMotor;
    int pwm;
    int r_in1();
    int r_in2();
    void atualizarMotor();
  public:
    Motor(int pinoEnb, int pinoIn1, int pinoIn2, boolean motorInvertido);
    int lerPwm();
    void definirPwm(int pwm);    
    DirecaoMotor lerDirecaoMotor();
    void definirDirecaoMotor(DirecaoMotor direcaoMotor);
    void iniciar();
    void pararMotor();    
    void frenteMaximo();
    void frentePWM(int pwm);
    void trasMaximo();
    void trasPWM(int pwm);
    void definirMotorInvertido(boolean invertido);
};


#endif