#ifndef SENSORDISTANCIA_H
#define SENSORDISTANCIA_H

enum StatusSensorDistancia{
    SD_PARADO = 0,
    SD_AGUARDAR = 1,
    SD_TRIGGER = 2,
    SD_LER = 3
};

class SensorDistancia {
    private:
        int pinoTrigger;
        int pinoEcho;
        StatusSensorDistancia status;
        int distancia;
        unsigned long esperar;        
    public:
        SensorDistancia(int trigger, int echo);
        void iniciar();
        void parar();
        void continuar();        
        int getDistancia();
        void loop();
};

#endif