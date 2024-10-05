#include "Carro.h"
#include "Motor.h"
#include "SensorVelocidade.h"
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
#define VELOCIDADE 200

//SENSOR VELOCIDADE
#define SENS_DIREITA 2
#define SENS_ESQUERDA 3

//SERVO
#define PIN_SERVO 10
#define PIN_SERVO_2 11

//SENSOR
#define PIN_TRIGGER 12
#define PIN_ECHO    13

Motor motorDireita(PIN_ENB, PIN_IN3, PIN_IN4, true);
Motor motorEsquerda(PIN_ENA, PIN_IN1, PIN_IN2, true);

SensorVelocidade senVelDireita(SENS_DIREITA, 20);
SensorVelocidade senVelEsquerda(SENS_ESQUERDA, 20);

Carro carro(&motorDireita, &motorEsquerda, &senVelDireita, &senVelEsquerda, 20);

ServoMotor servo(PIN_SERVO);
ServoMotor servo2(PIN_SERVO_2);

SensorDistancia sensor(PIN_TRIGGER,PIN_ECHO);

Controle controle(&carro, &servo, &sensor);


void setup(){
    Serial.begin(9600);   

    servo2.iniciar();
    servo2.girar(60);

    motorDireita.iniciar();
    motorEsquerda.iniciar();
    
    senVelDireita.iniciar([](){ senVelDireita.incPulso(); });
    senVelEsquerda.iniciar([](){ senVelEsquerda.incPulso(); });

    carro.definirVelocidade(VELOCIDADE);

    servo.iniciar();
    sensor.iniciar();    

    controle.iniciar();
    delay(1000);
}

void loop(){
    controle.loop();    
    delay(5);
}

