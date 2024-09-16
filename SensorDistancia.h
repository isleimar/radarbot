#ifndef SENSORDISTANCIA_H
#define SENSORDISTANCIA_H

class SensorDistancia {
    private:
        int pinoTrigger;
        int pinoEcho;
    public:
        SensorDistancia(int trigger, int echo);
        void iniciar();
        long medirDistancia();
};

#endif