/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Ventilador.cpp
 * Author: adrion
 * 
 * Created on 3 de Novembro de 2016, 18:08
 */

#include "Ventilador.h"

Ventilador::Ventilador() {
}

Ventilador::Ventilador(const Ventilador& orig) {
}

Ventilador::~Ventilador() {
}

void Ventilador::draw() {
    glPointSize(10.0f);
    glBegin(GL_POINTS);
    glVertex2f(this->getX(), this->getY());
    glEnd();
}

double Ventilador::getShiftX(Ponto* ponto) {
    if (this->getAtivo()) {
        if (ponto->getX() > this->getX())
            return (this->getForce(ponto) / ponto->getMassa()) * pow(CampoVetorial::getDelay() / 1000.0, 2);
        else if (ponto->getX() < this->getX())
            return (-this->getForce(ponto) / ponto->getMassa()) * pow(CampoVetorial::getDelay() / 1000.0, 2);
        return 0.0;
    }
}

double Ventilador::getShiftY(Ponto* ponto) {
    if (this->getAtivo()) {
        if (ponto->getY() > this->getY())
            return (this->getForce(ponto) / ponto->getMassa()) * pow(CampoVetorial::getDelay() / 1000.0, 2);
        else if (ponto->getY() < this->getY())
            return (-this->getForce(ponto) / ponto->getMassa()) * pow(CampoVetorial::getDelay() / 1000.0, 2);
        return 0.0;
    }
}

double Ventilador::getShiftZ(Ponto* ponto) {
    if (this->getAtivo()) {
        if (ponto->getZ() > this->getZ())
            return (this->getForce(ponto) / ponto->getMassa()) * pow(CampoVetorial::getDelay() / 1000.0, 2);
        else if (ponto->getZ() < this->getZ())
            return (-this->getForce(ponto) / ponto->getMassa()) * pow(CampoVetorial::getDelay() / 1000.0, 2);
        return 0.0;
    }
}

double Ventilador::getShiftX(float x, float y, float z) {
    if (x > this->getX())
        return this->getForce(x, y, z);
    else if (x < this->getX())
        return -this->getForce(x, y, z);

    return 0.0;
}

double Ventilador::getShiftY(float x, float y, float z) {
    if (y > this->getY())
        return this->getForce(x, y, z);
    else if (y < this->getY())
        return -this->getForce(x, y, z);

    return 0.0;
}

double Ventilador::getShiftZ(float x, float y, float z) {
    if (z > this->getZ())
        return this->getForce(x, y, z);
    else if (z < this->getZ())
        return -this->getForce(x, y, z);

    return 0.0;
}