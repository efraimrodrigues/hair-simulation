/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Cabelo.h
 * Author: adrion
 *
 * Created on October 31, 2016, 7:58 PM
 */

#ifndef CABELO_H
#define CABELO_H

#include "Ventilador.h"

using namespace std;

class Cabelo {
public:
    Cabelo();
    Cabelo(const Cabelo& orig);
    virtual ~Cabelo();
    void draw(bool);
    void drawRepouso();
    int ponto(int x, int y);
    int getNumPontos();
    bool atualiza(int pos, double x, double y); //Atualiza a posição do ponto pos para as coordenadas x e y
    void repouso(double); //Faz com que o cabelo volte a sua posição de repouso
    void ventilar(Ventilador*); //Recebe uma referência a um ventilador e ventila mudando a posição dos pontos
    void move(Ventilador*, double);
    void setDebug(bool);
    bool getDebug();
    void setCampoVetorial(CampoVetorial *);
    CampoVetorial* getCampoVetorial();
private:
    double comprimento;
    double * distanciaPadrao;
    double * distanciaPadraoX;
    double * distanciaPadraoY;
    double * distanciaPadraoZ;
    int numPontos;
    Ponto * pontos;
    Ponto * pontosOriginais;
    Ponto * pontosAtuais;
    bool debug;
    CampoVetorial * campoVetorial;
    float fatorial(int);
    float combinacao(int, int);
    bool aproximar(int, int, float); //Aproxima o ponto do segundo parâmetro ao ponto do primeiro parâmetro.
    bool aproximar(int, int);
    //bool aproximarRepouso(int, double); //Aproxima aos pontos da forma original de repouso.
    bool aproximarRepouso(int, double); //Aproxima aos pontos da forma original de repouso;
    double distancia(int, int); //Calcula a distância entre dois pontos do cabelo.
    double distanciaX(int, int);
    double distanciaY(int, int);
    double distanciaZ(int, int);
    double distanciaRepouso(int); //Calcula a distância entre um ponto e sua forma de repouso.
    double distanciaRepousoX(int);
    double distanciaRepousoY(int);
    double distanciaRepousoZ(int);
};

#endif /* CABELO_H */

