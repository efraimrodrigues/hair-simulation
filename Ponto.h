/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Ponto.h
 * Author: adrion
 *
 * Created on October 31, 2016, 7:54 PM
 */

#ifndef PONTO_H
#define PONTO_H

#include <GL/freeglut.h>
#include <cmath>
#include <cstdlib>
#include <iostream>

#define ALTURA 500
#define LARGURA 900

class Ponto {
public:
    Ponto();
    Ponto(const Ponto& orig);
    virtual ~Ponto();
    void set(float x, float y);
    void set(float x, float y, float z);
    
    void setX(float x);
    float getX();
    
    void setY(float y);
    float getY();
    
    void setZ(float z);
    float getZ();
    
    double distance(Ponto*);
    double distance(float x, float y, float z);
    
    void setMassa(float massa);
    float getMassa();
    
    void toString();
private:
    float x;
    float y;
    float z;
    float massa;
};

#endif /* PONTO_H */

