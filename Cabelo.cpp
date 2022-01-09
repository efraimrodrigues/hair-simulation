/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Cabelo.cpp
 * Author: adrion
 * 
 * Created on October 31, 2016, 7:58 PM
 */

#include "Cabelo.h"

Cabelo::Cabelo() {
    float massaPonto = 0.001;
    this->numPontos = 10;
    this->pontos = new Ponto[this->numPontos];
    this->pontosOriginais = new Ponto[this->numPontos];
    this->pontosAtuais = new Ponto[this->numPontos];

    this->distanciaPadrao = new double[this->numPontos];
    this->distanciaPadraoX = new double[this->numPontos];
    this->distanciaPadraoY = new double[this->numPontos];
    this->distanciaPadraoZ = new double[this->numPontos];

    int base = rand() % 125 + 400;

    for (int i = 0; i < numPontos; i++) {
        if (i == 0)
            pontos[i].setX(base);
        else
            pontos[i].setX(base + 1.0 * ((rand() + rand()) % 25));

        if (i == 0)
            pontos[i].setY(ALTURA - 200);
        else
            pontos[i].setY(pontos[i - 1].getY() - rand() % 50 - 5);

        pontos[i].setZ(0.0);

        pontosOriginais[i].set(pontos[i].getX(), pontos[i].getY(), pontos[i].getZ());

        //Massa dos pontos:
        pontos[i].setMassa(massaPonto);
        pontosOriginais[i].setMassa(massaPonto);
        pontosAtuais[i].setMassa(massaPonto);

    }

    for (int i = 0; i<this->numPontos - 1; i++) {
        this->distanciaPadrao[i] = distancia(i, i + 1) + 15.0;
        this->distanciaPadraoX[i] = distanciaX(i, i + 1);
        this->distanciaPadraoY[i] = distanciaY(i, i + 1);
        this->distanciaPadraoZ[i] = distanciaZ(i, i + 1);
    }
}

Cabelo::Cabelo(const Cabelo& orig) {
}

Cabelo::~Cabelo() {
    delete this->pontos;
    delete this->pontosAtuais;
    delete this->pontosOriginais;
}

float Cabelo::fatorial(int a) {
    int i;
    float produto;

    produto = 1.0f;
    for (i = a; i > 0; i--)
        produto *= (float) i;
    return produto;
}

float Cabelo::combinacao(int a, int b) {
    return fatorial(b) / (fatorial(a) * fatorial(b - a));
}

void Cabelo::draw(bool desenhaPontos) {
    GLint i;
    GLfloat u, x, y, z;

    if (desenhaPontos) {
        glColor3f(1.0f, 0.0f, 0.0f);
        glBegin(GL_LINE_STRIP);
        for (i = 0; i < numPontos; i++)
            glVertex3f(pontos[i].getX(), pontos[i].getY(), pontos[i].getZ());
        glEnd();

        glPointSize(4.0f);
        glBegin(GL_POINTS);

        for (int n = 0; n < numPontos; n++) {
            glVertex3f(pontos[n].getX(), pontos[n].getY(), pontos[n].getZ());
        }
        glEnd();
    }

    glPointSize(1.0f);
    glColor3f(0.988235294f, 0.905882353f, 0.717647059f);
    /*
     * Original: GL_POINTS
     * GL_LINE_STRIP permite que linhas sejam desenhadas de um ponto a outro, com isso pode-se reduzir o número de iterações,
     * porém a qualidade cai e o cabelo ficará com aliasing
     */
    glBegin(GL_LINE_STRIP);

    for (u = 0.0f; u <= 1.0f; u += 0.01f) {
        x = 0.0f;
        y = 0.0f;
        z = 0.0f;
        for (i = 0; i < numPontos; i++) {
            x += combinacao(i, numPontos - 1) * pow(u, i) * pow(1.0f - u, numPontos - 1 - i) * pontos[i].getX();
            y += combinacao(i, numPontos - 1) * pow(u, i) * pow(1.0f - u, numPontos - 1 - i) * pontos[i].getY();
            z += combinacao(i, numPontos - 1) * pow(u, i) * pow(1.0f - u, numPontos - 1 - i) * pontos[i].getZ();
        }
        glVertex3f(x, y, z);
    }
    glEnd();
}

void Cabelo::drawRepouso() {
    GLint i;
    GLfloat u, x, y, z;

    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_LINE_STRIP);
    for (i = 0; i < numPontos; i++)
        glVertex3f(pontosOriginais[i].getX(), pontosOriginais[i].getY(), pontosOriginais[i].getZ());
    glEnd();

    glPointSize(4.0f);
    glBegin(GL_POINTS);

    for (int n = 0; n < numPontos; n++) {
        glVertex3f(pontosOriginais[n].getX(), pontosOriginais[n].getY(), pontosOriginais[n].getZ());
    }
    glEnd();

    glPointSize(1.0f);
    glColor3f(0.0f, 1.0f, 0.0f);
    glBegin(GL_POINTS);

    for (u = 0.0f; u <= 1.0f; u += 0.001f) {
        x = 0.0f;
        y = 0.0f;
        z = 0.0f;
        for (i = 0; i < numPontos; i++) {
            x += combinacao(i, numPontos - 1) * pow(u, i) * pow(1.0f - u, numPontos - 1 - i) * pontosOriginais[i].getX();
            y += combinacao(i, numPontos - 1) * pow(u, i) * pow(1.0f - u, numPontos - 1 - i) * pontosOriginais[i].getY();
            z += combinacao(i, numPontos - 1) * pow(u, i) * pow(1.0f - u, numPontos - 1 - i) * pontosOriginais[i].getZ();
        }
        glVertex3f(x, y, z);
    }
    glEnd();
}

int Cabelo::ponto(int x, int y) {
    int ret = -1;
    float largura = 11.0f;
    cout << "(x,y) = " << x << "," << y << endl;
    for (int i = 0; i < numPontos; i++) {
        if (x > pontos[i].getX() - largura && x < pontos[i].getX() + largura
                && y > pontos[i].getY() - largura && y < pontos[i].getY() + largura) {
            ret = i;
            cout << "\nPonto " << i << ", x = " << pontos[i].getX() << "; y = "
                    << pontos[i].getY() << "\n";
            break;
        }
    }
    return ret;
}

int pontoMovido = 0;

bool Cabelo::atualiza(int pos, double x, double y) {
    bool atualizaZero = false;
    if (pos != -1 && pos != 0) {
        for (int i = 0; i<this->numPontos; i++)
            pontosAtuais[i].set(this->pontos[i].getX(), this->pontos[i].getY(), this->pontos[i].getZ());

        this->pontos[pos].setX(x);
        this->pontos[pos].setY(y);

        for (int i = pos; i > 0; i--)
            if (distancia(i - 1, i) > distanciaPadrao[i - 1])
                if (aproximar(i, i - 1) && i - 1 == 0)
                    atualizaZero = true;

        if (atualizaZero) {
            this->pontos[0].set(pontosAtuais[0].getX(), pontosAtuais[0].getY(), pontosAtuais[0].getZ());

            aproximar(0, 1);

            for (int i = 1; i<this->numPontos; i++)
                if (distancia(i + 1, i) > distanciaPadrao[i])
                    aproximar(i, i + 1);
        }

        if (!atualizaZero)
            for (int i = pos; i<this->numPontos; i++)
                if (distancia(i + 1, i) > distanciaPadrao[i])
                    aproximar(i, i + 1);

        //if (atualizaZero) {
        //    for (int i = 0; i<this->numPontos; i++)
        //        this->pontos[i].set(pontosAtuais[i].getX(), pontosAtuais[i].getY(), pontosAtuais[i].getZ());

        //or(int )
        //cout << "zero" << x << "," << y << endl;
        //}
    }
    return atualizaZero;
}

bool Cabelo::aproximar(int ponto1, int ponto2, float dist) {
    float shiftX = 0.0;
    float shiftY = 0.0;
    float shiftZ = 0.0;

    dist = abs(dist);
    pontoMovido = ponto1;

    if (this->pontos[ponto1].getX() > this->pontos[ponto2].getX())
        shiftX = dist;
    else if (this->pontos[ponto1].getX() < this->pontos[ponto2].getX())
        shiftX = -dist;

    if (this->pontos[ponto1].getY() > this->pontos[ponto2].getY())
        shiftY = dist;
    else if (this->pontos[ponto1].getY() < this->pontos[ponto2].getY())
        shiftY = -dist;

    if (this->pontos[ponto1].getZ() > this->pontos[ponto2].getZ())
        shiftZ = dist;
    else if (this->pontos[ponto1].getZ() < this->pontos[ponto2].getZ())
        shiftZ = -dist;

    if (this->pontos[ponto2].getX() + shiftX != this->pontos[ponto1].getX() &&
            this->pontos[ponto2].getY() + shiftY != this->pontos[ponto1].getY()) {
        this->pontos[ponto2].set(this->pontos[ponto2].getX() + shiftX, this->pontos[ponto2].getY() + shiftY);
        return true;
    } else
        return false;
}

bool Cabelo::aproximar(int ponto1, int ponto2) {
    float shiftX = abs(distanciaX(ponto1, ponto2) - (ponto1 > ponto2 ? distanciaPadraoX[ponto2] : distanciaPadraoX[ponto1]));
    float shiftY = abs(distanciaY(ponto1, ponto2) - (ponto1 > ponto2 ? distanciaPadraoY[ponto2] : distanciaPadraoY[ponto1]));
    float shiftZ = abs(distanciaZ(ponto1, ponto2) - (ponto1 > ponto2 ? distanciaPadraoZ[ponto2] : distanciaPadraoZ[ponto1]));

    if (this->pontos[ponto1].getX() < this->pontos[ponto2].getX())
        shiftX = -shiftX;

    if (this->pontos[ponto1].getY() < this->pontos[ponto2].getY())
        shiftY = -shiftY;

    if (this->pontos[ponto1].getZ() < this->pontos[ponto2].getZ())
        shiftZ = -shiftZ;

    //if (this->pontos[ponto2].getX() + shiftX != this->pontos[ponto1].getX() &&
    //        this->pontos[ponto2].getY() + shiftY != this->pontos[ponto1].getY()) {
    //if (ponto2 != 0) {
    this->pontos[ponto2].set(this->pontos[ponto2].getX() + shiftX, this->pontos[ponto2].getY() + shiftY, this->pontos[ponto2].getZ() + shiftZ);
    return true;
}

/*bool Cabelo::aproximarRepouso(int ponto, double dist) {
    double shiftX = 0.0;
    double shiftY = 0.0;
    double shiftZ = 0.0;

    if (this->pontosOriginais[ponto].getX() > this->pontos[ponto].getX())
        shiftX = dist;
    else if (this->pontosOriginais[ponto].getX() < this->pontos[ponto].getX())
        shiftX = -dist;

    if (this->pontosOriginais[ponto].getY() > this->pontos[ponto].getY())
        shiftY = dist;
    else if (this->pontosOriginais[ponto].getY() < this->pontos[ponto].getY())
        shiftY = -dist;

    if (this->pontosOriginais[ponto].getZ() > this->pontos[ponto].getZ())
        shiftZ = dist;
    else if (this->pontosOriginais[ponto].getZ() < this->pontos[ponto].getZ())
        shiftZ = -dist;

    //if (this->pontosOriginais[ponto].getX() != this->pontos[ponto].getX() + shiftX &&
    //        this->pontosOriginais[ponto].getY() != this->pontos[ponto].getY() + shiftY) {
    this->pontos[ponto].set(this->pontos[ponto].getX() + shiftX, this->pontos[ponto].getY() + shiftY);
    return true;
    //} else
    //    return false;

}*/

bool Cabelo::aproximarRepouso(int ponto, double alpha) {
    float shiftX = distanciaRepousoX(ponto);
    float shiftY = distanciaRepousoY(ponto);
    float shiftZ = distanciaRepousoZ(ponto);

    if (this->pontosOriginais[ponto].getX() < this->pontos[ponto].getX())
        shiftX = -shiftX;

    if (this->pontosOriginais[ponto].getY() < this->pontos[ponto].getY())
        shiftY = -shiftY;

    if (this->pontosOriginais[ponto].getZ() < this->pontos[ponto].getZ())
        shiftZ = -shiftZ;

    // if (this->pontosOriginais[ponto].getX()  != this->pontos[ponto].getX() + shiftX &&
    //        this->pontosOriginais[ponto].getY() != this->pontos[ponto].getY() + shiftY  &&
    //        this->pontosOriginais[ponto].getZ() != this->pontos[ponto].getZ() + shiftZ) {
    this->pontos[ponto].set(this->pontos[ponto].getX() + shiftX*alpha, this->pontos[ponto].getY() + shiftY*alpha, this->pontos[ponto].getZ() + shiftZ * alpha);
    return true;
    //} else
    //    return false;
}

int Cabelo::getNumPontos() {
    return this->numPontos;
}

/*
 * Retorna a distância entre dois pontos, os parâmetros são as posições dos pontos.
 */
double Cabelo::distancia(int ponto1, int ponto2) {
    return sqrt(pow(this->pontos[ponto1].getX() - this->pontos[ponto2].getX(), 2) +
            pow(this->pontos[ponto1].getY() - this->pontos[ponto2].getY(), 2) +
            pow(this->pontos[ponto1].getZ() - this->pontos[ponto2].getZ(), 2));
}

double Cabelo::distanciaX(int ponto1, int ponto2) {
    double ret = this->pontos[ponto1].getX() - this->pontos[ponto2].getX();

    return ret < 0 ? -ret : ret;
}

double Cabelo::distanciaY(int ponto1, int ponto2) {
    double ret = this->pontos[ponto1].getY() - this->pontos[ponto2].getY();

    return ret < 0 ? -ret : ret;
}

double Cabelo::distanciaZ(int ponto1, int ponto2) {
    double ret = this->pontos[ponto1].getZ() - this->pontos[ponto2].getZ();

    return ret < 0 ? -ret : ret;
}

/*
 * Retorna a distância entre dois pontos, os parâmetros são as posições dos pontos.
 */
double Cabelo::distanciaRepouso(int ponto) {
    return sqrt(pow(pontos[ponto].getX() - pontosOriginais[ponto].getX(), 2) +
            pow(pontos[ponto].getY() - pontosOriginais[ponto].getY(), 2) +
            pow(pontos[ponto].getZ() - pontosOriginais[ponto].getZ(), 2));
}

double Cabelo::distanciaRepousoX(int ponto) {
    double ret = this->pontos[ponto].getX() - this->pontosOriginais[ponto].getX();

    return ret < 0 ? -ret : ret;
}

double Cabelo::distanciaRepousoY(int ponto) {
    double ret = this->pontos[ponto].getY() - this->pontosOriginais[ponto].getY();

    return ret < 0 ? -ret : ret;
}

double Cabelo::distanciaRepousoZ(int ponto) {
    double ret = this->pontos[ponto].getZ() - this->pontosOriginais[ponto].getZ();

    return ret < 0 ? -ret : ret;
}

/*
 * Este parâmetro alpha deve variar entre 0.01 e 1.0. Ele indicará a porcentagem que os pontos se aproximaram do seu estado inicial.
 * Um valor de alpha igual a 1.0 significa que os pontos voltaram a sua forma original em uma chamada do método repouso.
 * Para que o Cabelo volte ao seu ponto de repouso gradativamente, o método repouso deve ser chamado várias vezes.
 */
void Cabelo::repouso(double alpha) {
    for (int i = 0; i<this->numPontos; i++)
        aproximarRepouso(i, alpha);
}

void Cabelo::ventilar(Ventilador * ventilador) {

    if (ventilador->getAtivo()) {
        double x = 0.0;
        double y = 0.0;
        double z = 0.0;
        int updatedPoints = 0;
        for (int i = this->numPontos - 1; i > 1; i--) {
            double constante = 1.0 + (i/(this->numPontos - i));
            if (true) {
                double shiftX = (ventilador->getShiftX(&this->pontos[i]) + campoVetorial->getShiftX(this->pontos[i].getX(), this->pontos[i].getY(), this->pontos[i].getZ()))*constante;
                double shiftY = (ventilador->getShiftY(&this->pontos[i]) + campoVetorial->getShiftY(this->pontos[i].getX(), this->pontos[i].getY(), this->pontos[i].getZ()))*constante;
                double shiftZ = (ventilador->getShiftZ(&this->pontos[i]) + campoVetorial->getShiftZ(this->pontos[i].getX(), this->pontos[i].getY(), this->pontos[i].getZ()))*constante;
                
                x = this->pontos[i].getX() + shiftX;
                y = this->pontos[i].getY() + shiftY;
                z = this->pontos[i].getZ() + shiftZ;

                if (this->debug) {
                    cout << "Shift[" << i << ": " << shiftX << ", " << shiftY << ", " << shiftZ << endl;
                    
                    glPointSize(1.0f);
                    glColor3f(0.0f, 1.0f, 0.0f);
                    glBegin(GL_LINES);
                    glVertex3f(this->pontos[i].getX(), this->pontos[i].getY(), this->pontos[i].getZ());
                    glVertex3f(x, y, z);
                    glEnd();

                    glColor3f(1.0, 0.0, 0.0);

                    glPointSize(5.0f);

                    glBegin(GL_POINTS);
                    glVertex2f(x, y);
                    glEnd();
                }

                //cout << "i = " << i << endl;
                //cout << x - this->pontos[i].getX() << endl;
                //cout << y - this->pontos[i].getY() << endl;
                //this->pontos[i].toString();
                
                //if(shiftX )

                if(atualiza(i, x, y))
                    updatedPoints++;
                //if (!atualiza(i, x, y))
                //    if (!atualiza(i, this->pontos[i].getX(), y))
                 //       atualiza(i, x, this->pontos[i].getY());

                //this->pontos[i].toString();
                //cout << "------" << endl;
            }
        }
        /*if(updatedPoints == 2)
                cout << "LOCKED!" << endl;
            else
                cout << "UNLOCKED" << endl;
            
            cout << "updatedPoints = " << updatedPoints << endl;*/
    }
}

void Cabelo::move(Ventilador* ventilador, double alpha) {
    bool moveu = false;
    for (int i = 0; i<this->numPontos; i++) {
        double x = 0.0;
        double y = 0.0;
        double z = 0.0;
        double c = 1.0;

        float shiftX = distanciaRepousoX(i) * alpha;
        float shiftY = distanciaRepousoY(i) * alpha;
        float shiftZ = distanciaRepousoZ(i) * alpha;

        float shiftXA = 0.0;
        float shiftYA = 0.0;
        float shiftZA = 0.0;



        if (ventilador->getAtivo()) {

            shiftXA = ventilador->getShiftX(&this->pontos[i]) * c; // + campoVetorial->getShiftX(this->pontos[i].getX(), this->pontos[i].getY(), this->pontos[i].getZ()) * c;
            shiftYA = ventilador->getShiftY(&this->pontos[i]) * c; // + campoVetorial->getShiftY(this->pontos[i].getX(), this->pontos[i].getY(), this->pontos[i].getZ()) * c;
            shiftZA = ventilador->getShiftZ(&this->pontos[i]) * c; // + campoVetorial->getShiftZ(this->pontos[i].getX(), this->pontos[i].getY(), this->pontos[i].getZ()) * c;



            /*if (this->pontosOriginais[i].getX() < this->pontos[i].getX())
                shiftX = -shiftX;

            if (this->pontosOriginais[i].getY() < this->pontos[i].getY())
                shiftY = -shiftY;

            if (this->pontosOriginais[i].getZ() < this->pontos[i].getZ())
                shiftZ = -shiftZ;*/

            if (this->pontosOriginais[i].getX() < this->pontos[i].getX() + shiftXA)
                shiftX = -shiftX;

            if (this->pontosOriginais[i].getY() < this->pontos[i].getY() + shiftYA)
                shiftY = -shiftY;

            if (this->pontosOriginais[i].getZ() < this->pontos[i].getZ() + shiftZA)
                shiftZ = -shiftZ;

            if (shiftX + shiftXA == 0) {
                cout << "what?!" << endl;
                cout << i << endl;
                shiftX += shiftXA;
                //shiftY += shiftYA;
            } else 


            x = this->pontos[i].getX() + shiftXA + shiftX;
            y = this->pontos[i].getY() + shiftYA + shiftY;
            z = this->pontos[i].getZ() + shiftZA + shiftZ;

            if (this->debug) {
                glPointSize(1.0f);
                glColor3f(0.0f, 1.0f, 0.0f);
                glBegin(GL_LINES);
                glVertex3f(this->pontos[i].getX(), this->pontos[i].getY(), this->pontos[i].getZ());
                glVertex3f(x, y, z);
                glEnd();

                glColor3f(1.0, 0.0, 0.0);

                glPointSize(5.0f);

                glBegin(GL_POINTS);
                glVertex2f(x, y);
                glEnd();
            }



            if (!atualiza(i, x, y))
                if (!atualiza(i, this->pontos[i].getX(), y))
                    atualiza(i, x, this->pontos[i].getY());

        }


        //this->pontos[i].set(this->pontos[i].getX() + shiftX, this->pontos[i].getY() + shiftY, this->pontos[i].getZ() + shiftZ);
    }
}

void Cabelo::setDebug(bool debug) {
    this->debug = debug;
}

bool Cabelo::getDebug() {
    return this->debug;
}

void Cabelo::setCampoVetorial(CampoVetorial * campoVetorial) {
    this->campoVetorial = campoVetorial;
}

CampoVetorial * Cabelo::getCampoVetorial() {
    return this->campoVetorial;
}