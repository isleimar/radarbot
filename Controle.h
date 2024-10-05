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
        unsigned long getDistanciaPercorrida() const;
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
    virtual unsigned long getDistanciaPercorrida() const;
    virtual void iniciar() = 0;
    virtual void obstaculoEncontrado() = 0;
    virtual void loop() = 0;
    virtual void finalizar() = 0;
};

class EstadoControle: public EstadoControleBase {
  private:
    unsigned long tempoFinal;
    unsigned long distanciaInicial;
    virtual void executar() = 0;
  protected:
    Controle* controle;
    String descricaoEstado = "Controle";
    void esperar(unsigned long esperarMilisegundos);
  public:
    EstadoControle(Controle* controle);
    virtual String getDescricaoEstado() override;
    virtual unsigned long getDistanciaPercorrida() const override;
    virtual void iniciar() override;
    virtual void obstaculoEncontrado();
    virtual void loop() override;
    virtual void finalizar() override;
};

class EstadoParado: public EstadoControle{
  private:    
    void executar() override;      
  public:
    EstadoParado(Controle* controle): EstadoControle(controle) {
      EstadoControle::descricaoEstado = "Estado Parado";
    };
    virtual void iniciar() override;
};


class EstadoAndando: public EstadoControle{
  private:    
    void executar() override;     
  public:
    EstadoAndando(Controle* controle): EstadoControle(controle) {
      EstadoControle::descricaoEstado = "Estado Andando";
    };
    virtual void iniciar() override;
    virtual void obstaculoEncontrado() override;
};

class EstadoOlhandoDireita: public EstadoControle{
  private:    
    void executar() override;
  public:
    EstadoOlhandoDireita(Controle* controle): EstadoControle(controle){
      EstadoControle::descricaoEstado = "Estado Olhando para Direita";
    };
    virtual void iniciar() override;
};

class EstadoOlhandoEsquerda: public EstadoControle{
  private:    
    void executar() override;
  public:
    EstadoOlhandoEsquerda(Controle* controle): EstadoControle(controle) {
      EstadoControle::descricaoEstado = "Estado Olhando para Esquerda";
    };
    virtual void iniciar() override;
};


class EstadoGirandoDireita: public EstadoControle{
  private:
    void executar() override;
  public:
    EstadoGirandoDireita(Controle* controle): EstadoControle(controle) {
      EstadoControle::descricaoEstado = "Estado Girando para Direita";
    };
    virtual void iniciar() override;
};


class EstadoGirandoEsquerda: public EstadoControle{
  private:
    void executar() override;
  public:
    EstadoGirandoEsquerda(Controle* controle): EstadoControle(controle) {
      EstadoControle::descricaoEstado = "Estado Girando para Esquerda";
    };
    virtual void iniciar() override;
};


class EstadoVoltar: public EstadoControle{
  private:
    void executar() override;
  public:
    EstadoVoltar(Controle* controle): EstadoControle(controle){
      EstadoControle::descricaoEstado = "Estado Voltando";
    };
    virtual void iniciar() override;
};

#endif