/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   CampoVetorial.cpp
 * Author: adrion
 * 
 * Created on 14 de Novembro de 2016, 10:43
 */

#include "CampoVetorial.h"

CampoVetorial::CampoVetorial() {
    this->setAtivo(false);
}

CampoVetorial::CampoVetorial(const CampoVetorial& orig) {
}

CampoVetorial::~CampoVetorial() {
}

void CampoVetorial::draw() {
    glPointSize(1.0f);
    for (int i = -1000; i < 1000; i += force + 10)
        for (int j = -1000; j < 1000; j += force + 10) {
            glPointSize(1.0f);
            glColor3f(0.0, 1.0, 0.0);

            glBegin(GL_LINES);
            glVertex2f(i, j);
            glVertex2f(i + this->getShiftX(i, j, 0), j + this->getShiftY(i, j, 0));
            glEnd();

            //if(i==200 && j==200)
            //    glColor3f(1.0, 1.0, 0.0);
            //else
            glColor3f(1.0, 0.0, 0.0);

            glPointSize(5.0f);

            glBegin(GL_POINTS);
            glVertex2f(i + this->getShiftX(i, j, 0), j + this->getShiftY(i, j, 0));
            glEnd();

            //std::cout << this->getShiftX(i,j,0) << std::endl;
            //std::cout << this->getShiftY(i,j,0) << std::endl;
        }
}

double CampoVetorial::getForce() {
    return this->force;
}

double CampoVetorial::getForce(Ponto * ponto) {
    return this->force;
}

double CampoVetorial::getForce(float x, float y, float z) {
    return this->force;
}

void CampoVetorial::setForce(double force) {
    this->force = force;
}

void CampoVetorial::setDebug(bool debug) {
    this->debug = debug;
}

bool CampoVetorial::getDebug() {
    return this->debug;
}

void CampoVetorial::setAtivo(bool ativo) {
    this->ativo = ativo;
}

bool CampoVetorial::getAtivo() {
    return this->ativo;
}

void CampoVetorial::setDelay(int delay) {
    this->delay = delay;
}

int CampoVetorial::getDelay() {
    return this->delay;
}

double CampoVetorial::getShiftX(Ponto* ponto) {
    if (this->getAtivo()) {
        if (ponto->getX() > this->getX(ponto))
            return (this->getForce(ponto) / ponto->getMassa()) * pow(delay / 1000.0, 2);
        else if (ponto->getX() < this->getX(ponto))
            return (-this->getForce(ponto) / ponto->getMassa()) * pow(delay / 1000.0, 2);
        return 0.0;
    }
}

double CampoVetorial::getShiftY(Ponto* ponto) {
    if (this->getAtivo()) {
        if (ponto->getY() > this->getY(ponto))
            return (this->getForce(ponto) / ponto->getMassa()) * pow(delay / 1000.0, 2);
        else if (ponto->getY() < this->getY(ponto))
            return (-this->getForce(ponto) / ponto->getMassa()) * pow(delay / 1000.0, 2);
        return 0.0;
    }
}

double CampoVetorial::getShiftZ(Ponto* ponto) {
    if (this->getAtivo()) {
        if (ponto->getZ() > this->getZ(ponto))
            return (this->getForce(ponto) / ponto->getMassa()) * pow(delay / 1000.0, 2);
        else if (ponto->getZ() < this->getZ(ponto))
            return (-this->getForce(ponto) / ponto->getMassa()) * pow(delay / 1000.0, 2);
        return 0.0;
    }
}

double CampoVetorial::getX(Ponto* ponto) {
    return this->getX(ponto->getX(), ponto->getY(), ponto->getZ());
}

double CampoVetorial::getY(Ponto* ponto) {
    return this->getY(ponto->getX(), ponto->getY(), ponto->getZ());
}

double CampoVetorial::getZ(Ponto* ponto) {
    return this->getZ(ponto->getX(), ponto->getY(), ponto->getZ());
}

double CampoVetorial::getX(float x, float y, float z) {
    switch (campo) {
        case 0:
            return x;
        case 1:
            return x + y;
        case 2:
            return x;
        case 3:
            return x*x;
        case 4:
            return -x*x;
        case 5:
            return 1.0/x;
    }
}

double CampoVetorial::getY(float x, float y, float z) {
    switch (campo) {
        case 0:
            return y;
        case 1:
            return x + y;
        case 2:
            return -y*y;
        case 3:
            return y;
        case 4:
            return y;
        case 5:
            return 1.0/y;
    }
}

double CampoVetorial::getZ(float x, float y, float z) {
    return z;
}

double CampoVetorial::getShiftX(float x, float y, float z) {
    if (x > this->getX(x, y, z))
        return this->getForce(x, y, z);
    else if (x < this->getX(x, y, z))
        return -this->getForce(x, y, z);

    return 0.0;
}

double CampoVetorial::getShiftY(float x, float y, float z) {
    if (y > this->getY(x, y, z))
        return this->getForce(x, y, z);
    else if (y < this->getY(x, y, z))
        return -this->getForce(x, y, z);

    return 0.0;
}

double CampoVetorial::getShiftZ(float x, float y, float z) {
    if (z > this->getZ(x, y, z))
        return this->getForce(x, y, z);
    else if (z < this->getZ(x, y, z))
        return -this->getForce(x, y, z);

    return 0.0;
}

void CampoVetorial::setCampo(int i) {
    if (i >= 0 && i <= 5)
        this->campo = i;
}

int CampoVetorial::getCampo() {
    return this->campo;
}

void CampoVetorial::next() {
    campo++;
    if (campo > 5)
        campo = 0;
}