/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Ventilador.h
 * Author: adrion
 *
 * Created on 3 de Novembro de 2016, 18:08
 */

#include "CampoVetorial.h"

#ifndef VENTILADOR_H
#define VENTILADOR_H

class Ventilador : public Ponto, public CampoVetorial {
public:
    using Ponto::getX;
    using Ponto::getY;
    using Ponto::getZ;

    //using CampoVetorial::getX;
    //using CampoVetorial::getY;
    //using CampoVetorial::getZ;

    //using CampoVetorial::getShiftX;
    //using CampoVetorial::getShiftY;
    //using CampoVetorial::getShiftZ;

    Ventilador();
    Ventilador(const Ventilador& orig);
    virtual ~Ventilador();
    void draw();
    
    double getForce() {
        return CampoVetorial::getForce();
    }

    double getForce(Ponto* ponto) {
        return this->getForce(ponto->getX(), ponto->getY(), ponto->getY());
    }

    double getForce(float x, float y, float z) {
        double dist = this->distance(x, y, z);
        
        dist/= 50;
        dist++;
        
        return CampoVetorial::getForce()/(dist);
    }
    
    //double getForce();
    //double getForce(Ponto*);
    //double getForce(float, float, float);

    double getShiftX(Ponto*); //Retorna a força que o Ventilador exerce em um Ponto na coordenada X.
    double getShiftY(Ponto*); //Retorna a força que o Ventilador exerce em um Ponto na coordenada Y.
    double getShiftZ(Ponto*); //Retorna a força que o Ventilador exerce em um Ponto na coordenada Z.

    double getShiftX(float x, float y, float z);
    double getShiftY(float x, float y, float z);
    double getShiftZ(float x, float y, float z);

private:

};

#endif /* VENTILADOR_H */

