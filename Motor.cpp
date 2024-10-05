#include "Motor.h"

Motor::Motor(int pinoEnb, int pinoIn1, int pinoIn2, boolean motorInvertido):
 pinoEnb(pinoEnb),
 pinoIn1(pinoIn1),
 pinoIn2(pinoIn2),
 motorInvertido(motorInvertido),
 direcaoMotor(PARADO),
 pwm(0){}

int Motor::r_in1() const{
  return motorInvertido ? pinoIn2 : pinoIn1;
}

int Motor::r_in2() const{
  return motorInvertido ? pinoIn1 : pinoIn2;
}

void Motor::atualizarMotor(){
  switch(direcaoMotor) {
    case PARADO:
      pararMotor();
      break;
    case FRENTE:
      (pwm >= 255) ? frenteMaximo() : frentePWM(pwm);
      break;
    case TRAS:
      (pwm >= 255) ? trasMaximo() : trasPWM(pwm);
      break;
  }
}

int Motor::lerPwm() const{
  return this->pwm;
}

void Motor::definirPwm(int pwm){
  this->pwm = constrain(pwm, 0, 255);
  atualizarMotor();
}

DirecaoMotor Motor::lerDirecaoMotor() const{  
  return direcaoMotor;  
}

void Motor::definirDirecaoMotor(DirecaoMotor direcaoMotor){
  this->direcaoMotor = direcaoMotor;
  atualizarMotor();  
}

void Motor::iniciar(){
  pinMode(pinoEnb, OUTPUT);
  pinMode(pinoIn1, OUTPUT);
  pinMode(pinoIn2, OUTPUT);
  pararMotor();
}

void Motor::pararMotor(){  
  this->pwm = 0;
  this->direcaoMotor = PARADO;
  digitalWrite(pinoEnb, LOW);
  digitalWrite(r_in1(),LOW);
  digitalWrite(r_in2(),LOW);
}

void Motor::frenteMaximo(){
  this->pwm = 255;
  this->direcaoMotor = FRENTE;
  digitalWrite(pinoEnb, HIGH);
  digitalWrite(r_in1(),HIGH);
  digitalWrite(r_in2(),LOW);  
}

void Motor::frentePWM(int pwm){
  this->pwm = constrain(pwm, 0, 255);
  this->direcaoMotor = FRENTE;
  analogWrite(pinoEnb, this->pwm);
  digitalWrite(r_in1(), HIGH);
  digitalWrite(r_in2(), LOW);
}

void Motor::trasMaximo(){  
  this->pwm = 255;
  this->direcaoMotor = TRAS;
  digitalWrite(pinoEnb,HIGH);
  digitalWrite(r_in1(),LOW);
  digitalWrite(r_in2(),HIGH);
}

void Motor::trasPWM(int pwm){
  this->pwm = constrain(pwm, 0, 255);
  this->direcaoMotor = TRAS;
  analogWrite(pinoEnb, this->pwm);
  digitalWrite(r_in1(),LOW);
  digitalWrite(r_in2(),HIGH);  
}

void Motor::definirMotorInvertido(boolean invertido){
  this->motorInvertido = invertido;
}