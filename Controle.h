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
        float distanciaObstaculo() const;
        bool temObstaculo() const;
        void carroParar();
        void carroAndar();
        void carroVoltar();
        void carroVirarDireita();
        void carroVirarEsquerda();
        void girarSensorFrente();
        void girarSensorDireita();
        void girarSensorEsquerda();
};

class EstadoControleBase {
  private:
    virtual void executar() = 0;
  public:    
    virtual ~EstadoControleBase()= default;
    virtual String getDescricaoEstado() = 0;
    virtual void iniciar() = 0;
    virtual void obstaculoEncontrado() = 0;
    virtual void loop() = 0;
    virtual void finalizar() = 0;
};

class EstadoControle: public EstadoControleBase {
  private:
    const String descricaoEstado = "Estado Controle";
    unsigned long tempoFinal;
    virtual void executar() = 0;
  protected:
    Controle* controle;
    void esperar(unsigned long esperarMilisegundos);
  public:
    virtual String getDescricaoEstado() override;
    EstadoControle(Controle* controle);
    virtual void iniciar() override;
    virtual void obstaculoEncontrado();
    virtual void loop() override;
    virtual void finalizar() override;
};

class EstadoParado: public EstadoControle{
  private:
    const String descricaoEstado = "Estado Parado";
    void executar() override;
  public:
    EstadoParado(Controle* controle);    
    virtual void iniciar() override;
};


class EstadoAndando: public EstadoControle{
  private:
    const String descricaoEstado = "Estado Andando";
    void executar() override;
  public:
    EstadoAndando(Controle* controle);
    virtual void iniciar() override;
    virtual void obstaculoEncontrado() override;
};

class EstadoOlhandoDireita: public EstadoControle{
  private:
    const String descricaoEstado = "Estado Olhando para Direita";
    void executar() override;
  public:
    EstadoOlhandoDireita(Controle* controle);
    virtual void iniciar() override;
};

class EstadoOlhandoEsquerda: public EstadoControle{
  private:
    const String descricaoEstado = "Estado Olhando para Esquerda";
    void executar() override;
  public:
    EstadoOlhandoEsquerda(Controle* controle);
    virtual void iniciar() override;
};


class EstadoGirandoDireita: public EstadoControle{
  private:
    const String descricaoEstado = "Estado Girando para Direita";
    void executar() override;
  public:
    EstadoGirandoDireita(Controle* controle);
    virtual void iniciar() override;
};


class EstadoGirandoEsquerda: public EstadoControle{
  private:
    const String descricaoEstado = "Estado Girando para Esquerda";
    void executar() override;
  public:
    EstadoGirandoEsquerda(Controle* controle);
    virtual void iniciar() override;
};


class EstadoVoltar: public EstadoControle{
  private:
    const String descricaoEstado = "Estado Voltando";
    void executar() override;
  public:
    EstadoVoltar(Controle* controle);
    virtual void iniciar() override;
};

#endif