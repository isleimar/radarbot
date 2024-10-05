#ifndef CONTROLE_H
#define CONTROLE_H

#include <Arduino.h>

#include "Carro.h"
#include "ServoMotor.h"
#include "SensorDistancia.h"

#define DISTANCIA_SEGURA 30

class EstadoControleBase;

class Controle {
    private:
        Carro* carro;
        ServoMotor* servo;
        SensorDistancia* sensor;
        EstadoControleBase* estadoAtual;
    public:
        Controle(Carro* c, ServoMotor* s, SensorDistancia* sens);
        void mudarEstado(EstadoControleBase* estadoNovo);        
        void loop();
        void iniciar();
        bool temObstaculo();
        float distanciaObstaculo();
        void carroParar();
        void carroAndar();
        void carroVoltar();
        void carroVirarDireita();
        void carroVirarEsquerda();
        void sensorFrente();
        void sensorDireita();
        void sensorEsquerda();
};

class EstadoControleBase {
  private:
    virtual void executar() = 0;
  public:    
    virtual ~EstadoControleBase()= default;
    virtual String getNomeEstado() = 0;
    virtual void iniciar() = 0;
    virtual void obstaculoEncontrado() = 0;
    virtual void loop() = 0;
    virtual void finalizar() = 0;
};

class EstadoControle: public EstadoControleBase {
  private:
    unsigned long tempoFinal;
    virtual void executar() = 0;
  protected:
    Controle* controle;
    void esperar(unsigned long esperarMilisegundos);
  public:
    virtual String getNomeEstado() override;
    EstadoControle(Controle* controle);
    virtual void iniciar() override;
    virtual void obstaculoEncontrado();
    virtual void loop() override;
    virtual void finalizar() override;
};

class EstadoParado: public EstadoControle{
  private:
    void executar() override;
  public:
    EstadoParado(Controle* controle);
    virtual String getNomeEstado() override;
    virtual void iniciar() override;
};


class EstadoAndando: public EstadoControle{
  private:
    void executar() override;
  public:
    EstadoAndando(Controle* controle);
    virtual String getNomeEstado() override;
    virtual void iniciar() override;
    virtual void obstaculoEncontrado() override;
};

class EstadoOlhandoDireita: public EstadoControle{
  private:
    void executar() override;
  public:
    EstadoOlhandoDireita(Controle* controle);
    virtual String getNomeEstado() override;
    virtual void iniciar() override;
};

class EstadoOlhandoEsquerda: public EstadoControle{
  private:
    void executar() override;
  public:
    EstadoOlhandoEsquerda(Controle* controle);
    virtual String getNomeEstado() override;
    virtual void iniciar() override;
};


class EstadoGirandoDireita: public EstadoControle{
  private:
    void executar() override;
  public:
    EstadoGirandoDireita(Controle* controle);
    virtual String getNomeEstado() override;
    virtual void iniciar() override;
};


class EstadoGirandoEsquerda: public EstadoControle{
  private:
    void executar() override;
  public:
    EstadoGirandoEsquerda(Controle* controle);
    virtual String getNomeEstado() override;
    virtual void iniciar() override;
};


class EstadoVoltar: public EstadoControle{
  private:
    void executar() override;
  public:
    EstadoVoltar(Controle* controle);
    virtual String getNomeEstado() override;
    virtual void iniciar() override;
};

#endif