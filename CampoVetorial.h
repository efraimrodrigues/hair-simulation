/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   CampoVetorial.h
 * Author: adrion
 *
 * Created on 14 de Novembro de 2016, 10:43
 */

#include "Ponto.h"

#ifndef CAMPOVETORIAL_H
#define CAMPOVETORIAL_H

class CampoVetorial {
public:
    CampoVetorial();
    CampoVetorial(const CampoVetorial& orig);
    virtual ~CampoVetorial();
    void draw();

    double getForce();
    double getForce(Ponto*);
    double getForce(float, float, float);
    void setForce(double);

    double getShiftX(Ponto*); //Retorna a força que o CampoVetorial exerce em um Ponto na coordenada X.
    double getShiftY(Ponto*); //Retorna a força que o CampoVetorial exerce em um Ponto na coordenada Y.
    double getShiftZ(Ponto*);
    
    double getShiftX(float x, float y, float z);
    double getShiftY(float x, float y, float z);
    double getShiftZ(float x, float y, float z);
    
    double getX(Ponto*);
    double getY(Ponto*);
    double getZ(Ponto*);
    
    double getX(float x, float y, float z);
    double getY(float x, float y, float z);
    double getZ(float x, float y, float z);
    
    int getDelay();
    void setDelay(int);

    void setDebug(bool);
    bool getDebug();

    void setAtivo(bool);
    bool getAtivo();
    
    void setCampo(int i);
    int getCampo();
    void next();
    
private:
    double force;
    int delay;
    bool debug;
    bool ativo;
    int campo;
};

#endif /* CAMPOVETORIAL_H */

