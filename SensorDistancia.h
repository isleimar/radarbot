#ifndef SENSORDISTANCIA_H
#define SENSORDISTANCIA_H

class SensorDistancia {
    private:
        int pinoTrigger;
        int pinoEcho;
        float lerSensor(); 
    public:
        SensorDistancia(int trigger, int echo);
        void iniciar();
        float getDistancia();
};

#endif