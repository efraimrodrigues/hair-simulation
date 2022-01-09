/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Ponto.cpp
 * Author: adrion
 * 
 * Created on October 31, 2016, 7:58 PM
 */

#include "Ponto.h"
#include "Cabelo.h"

Ponto::Ponto() {
}

Ponto::Ponto(const Ponto& orig) {
}

Ponto::~Ponto() {
}

void Ponto::set(float x, float y) {
    this->setX(x);
    this->setY(y);
}

void Ponto::set(float x, float y, float z) {
    this->setX(x);
    this->setY(y);
    this->setZ(z);
}

void Ponto::setX(float x) {
        this->x = x;
}

float Ponto::getX() {
    return this->x;
}

void Ponto::setY(float y) {
        this->y = y;
}

float Ponto::getY() {
    return this->y;
}

void Ponto::setZ(float z) {
    this->z = z;
}

float Ponto::getZ() {
    return this->z;
}

double Ponto::distance(Ponto* ponto) {
    return sqrt(pow(this->getX() - ponto->getX(), 2) +
            pow(this->getY() - ponto->getY(), 2) + pow(this->getZ() - ponto->getZ(),2));
}

double Ponto::distance(float x, float y, float z) {
    return sqrt(pow(this->getX() - x, 2) +
            pow(this->getY() - y, 2) + pow(this->getZ() - z,2));
}

void Ponto::setMassa(float massa) {
    this->massa = massa;
}

float Ponto::getMassa() {
    return this->massa;
}

void Ponto::toString() {
    std::cout << "(x,y) = " << "(" << x << "," << y << ")" << std::endl;
}