#include <GL/glut.h>
#include "Cabelo.h"
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

using namespace std;

int fios = 50;

Cabelo * cabelo = new Cabelo[fios];
int posVetor = -1;
int directionX;
int directionY;

Ventilador * ventilador = new Ventilador();

CampoVetorial * gravidade = new CampoVetorial();

int delay = 35;

bool mostrarPontosControle = false;
bool mostrarCampoVetorial = false;
bool mostrarCampoVetorialVento = false;

int menuBrancoId, menuVentiladorId, menuVentiladorVelocidadeId, menuCampoVetorialId;

void orthogonalStart() {
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
}

void orthogonalEnd() {
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
}

GLuint texture = 0;

void background1() {
    glBindTexture(GL_TEXTURE_2D, texture);

    orthogonalStart();

    // texture width/height
    const int iw = 1000;
    const int ih = 1000;

    glPushMatrix();
    glTranslatef(-iw / 2, -ih / 2, 0);
    glBegin(GL_QUADS);
    glTexCoord2i(0, 0);
    glVertex2i(0, 0);
    glTexCoord2i(1, 0);
    glVertex2i(iw, 0);
    glTexCoord2i(1, 1);
    glVertex2i(iw, ih);
    glTexCoord2i(0, 1);
    glVertex2i(0, ih);
    glEnd();
    glPopMatrix();

    orthogonalEnd();
}

void background() {
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glOrtho(0.0, glutGet(GLUT_WINDOW_WIDTH), 0.0, glutGet(GLUT_WINDOW_HEIGHT), -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();


    glLoadIdentity();
    glDisable(GL_LIGHTING);


    glColor3f(1, 1, 1);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTranslatef(300, 0, 0);

    int zoom = 3;

    // Draw a textured quad
    glBegin(GL_QUADS);
    glTexCoord2f(0, 0);
    glVertex3f(0, 0, 0);
    glTexCoord2f(0, 1);
    glVertex3f(0, 100 * zoom, 0);
    glTexCoord2f(1, 1);
    glVertex3f(100 * zoom, 100 * zoom, 0);
    glTexCoord2f(1, 0);
    glVertex3f(100 * zoom, 0, 0);
    glEnd();


    glDisable(GL_TEXTURE_2D);
    glPopMatrix();


    glMatrixMode(GL_PROJECTION);
    glPopMatrix();

    glMatrixMode(GL_MODELVIEW);
}

void drawVectorField() {
    glPointSize(1.0f);
    if (mostrarCampoVetorialVento || mostrarCampoVetorial) {
        for (int i = -1000; i < 1000; i += ventilador->getForce() + 10) {
            for (int j = -1000; j < 1000; j += ventilador->getForce() + 10) {
                double x = mostrarCampoVetorialVento ? ventilador->getShiftX(i, j, 0) : 0.0;
                double y = mostrarCampoVetorialVento ? ventilador->getShiftY(i, j, 0) : 0.0;

                x += mostrarCampoVetorial ? gravidade->getShiftX(i, j, 0) : 0.0;
                y += mostrarCampoVetorial ? gravidade->getShiftY(i, j, 0) : 0.0;


                glPointSize(1.0f);
                glColor3f(0.0, 1.0, 0.0);

                glBegin(GL_LINES);
                glVertex2f(i, j);
                glVertex2f(i + x, j + y);
                glEnd();

                glColor3f(1.0, 0.0, 0.0);

                glPointSize(5.0f);

                glBegin(GL_POINTS);
                glVertex2f(i + x, j + y);
                glEnd();
            }
        }
    }
}

void display() {
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glClear(GL_COLOR_BUFFER_BIT);
    
    int i = 0;
    
    #pragma omp parallel for private(i)
    for (i = 0; i < fios; i++)
        cabelo[i].draw(mostrarPontosControle);

    ventilador->draw();

    drawVectorField();

    glPushMatrix();

    glutSwapBuffers();

    glutPostRedisplay();

    background();
}

bool movimentando = false;
bool movimentandoVentilador = false;

void escolha(int botao, int estado, int x, int y) {
    glutDetachMenu(GLUT_RIGHT_BUTTON);
    //y = 500 - y;
    if ((botao == GLUT_LEFT_BUTTON) && (estado == GLUT_DOWN)) {
        posVetor = cabelo[0].ponto(x, y);
        if (posVetor != -1) {
            directionX = x;
            directionY = y;
        }

        if (x > ventilador->getX() - 11.0 && x < ventilador->getX() + 11.0
                && y > ventilador->getY() - 11.0 && y < ventilador->getY() + 11.0) {
            cout << "\nVentilador " << ", x = " << ventilador->getX() << "; y = "
                    << ventilador->getY() << "\n";
            movimentandoVentilador = true;
        }
        movimentando = true;
    } else if ((botao == GLUT_LEFT_BUTTON) && (estado == GLUT_UP)) {
        movimentando = false;
        movimentandoVentilador = false;
    } else if (botao == GLUT_RIGHT_BUTTON) {
        if (x > ventilador->getX() - 11.0 && x < ventilador->getX() + 11.0
                && y > ventilador->getY() - 11.0 && y < ventilador->getY() + 11.0)
            glutAttachMenu(GLUT_RIGHT_BUTTON);
    }
}

void captura(int x, int y) {
    //y = 500 - y;

    //for (int i = 0; i < fios; i++)
        cabelo[0].atualiza(posVetor, x, y);

    if (movimentandoVentilador)
        ventilador->set(x, y);
}

void AlteraTamanhoJanela(GLsizei w, GLsizei h) {
    // Evita a divisao por zero
    if (h == 0)
        h = 1;

    // Especifica as dimens�es da Viewport
    glViewport(0, 0, w, h);

    // Inicializa o sistema de coordenadas
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    //0.0f -> 900.0f <> 500.0f -> 0.0f
    // Estabelece a janela de sele��o (left, right, bottom, top)
    //if (w <= h)
    //    gluOrtho2D(0.0f, 900.0f, 0.0f, 500.0f /**h/w*/);
    //else
    gluOrtho2D(0.0f, w/**w/h*/, h, 0.0f);
}

//Ideia para velocidade -> diminuir o tempo de delay entre uma interação e outra.

void ventilar() {
    //double alpha = 0.1 / (rand() % 2 + 1.0);
    double alpha = 0.2;
    
    int i = 0;
    //pragma openmp parallel for
    #pragma omp parallel for private(i)
    for (i = 0; i < fios; i++) {
        cabelo[i].ventilar(ventilador);
        cabelo[i].repouso(alpha);
        //cabelo[i].move(ventilador, alpha);
    }
}

//thread t(ventilar, "assa");
//bool sw = true;

void timer(int value) {
    //glutPostRedisplay(); // Post re-paint request to activate display()

    //double alpha = 0.1 / (rand() % 2 + 1.0);
    ventilar();

    glutTimerFunc(delay, timer, 0); // next timer call milliseconds later
}

void menuVentilador(int value) {
    if (value == 0)
        exit(0);
    if (value == 1)
        ventilador->setAtivo(false);
    else if (value == 2)
        ventilador->setAtivo(true);
    else if (value == 3)
        for (int i = 0; i < fios; i++)
            cabelo[i].setDebug(!cabelo[i].getDebug());
    else if (value == 4)
        mostrarPontosControle = !mostrarPontosControle;
    else if (value == 5)
        mostrarCampoVetorial = !mostrarCampoVetorial;
    else if (value == 6)
        mostrarCampoVetorialVento = !mostrarCampoVetorialVento;
}

void menuVentiladorVelocidade(int value) {
    if (value == 0)
        ventilador->setForce(10.0);
    else if (value == 1)
        ventilador->setForce(20.0);
    else if (value == 2)
        ventilador->setForce(30.0);
}

void menuCampoVetorial(int value) {
    switch (value) {
        case 0:
            mostrarCampoVetorial = !mostrarCampoVetorial;
            break;
        case 1:
            gravidade->next();
            break;
        case 2:
            gravidade->setCampo(0);
            break;
        case 3:
            gravidade->setCampo(1);
            break;
        case 4:
            gravidade->setCampo(2);
            break;
        case 5:
            gravidade->setCampo(3);
            break;
        case 6:
            gravidade->setCampo(4);
            break;
        case 7:
            gravidade->setCampo(5);
    }

}

void criaMenu(void) {
    menuVentiladorVelocidadeId = glutCreateMenu(menuVentiladorVelocidade);
    glutAddMenuEntry("Min.", 0);
    glutAddMenuEntry("Med.", 1);
    glutAddMenuEntry("Max.", 2);

    menuCampoVetorialId = glutCreateMenu(menuCampoVetorial);
    glutAddMenuEntry("Ver", 0);
    glutAddMenuEntry("Prox.", 1);
    glutAddMenuEntry("Op. 1", 2);
    glutAddMenuEntry("Op. 2", 3);
    glutAddMenuEntry("Op. 3", 4);
    glutAddMenuEntry("Op. 4", 5);
    glutAddMenuEntry("Op. 5", 6);
    glutAddMenuEntry("Op. 6", 7);

    menuVentiladorId = glutCreateMenu(menuVentilador);
    glutAddMenuEntry("Desligar", 1);
    glutAddMenuEntry("Ligar", 2);
    glutAddSubMenu("Velocidade", menuVentiladorVelocidadeId);
    glutAddMenuEntry("Debug", 3);
    glutAddMenuEntry("Pontos", 4);
    glutAddSubMenu("Campo Vetorial", menuCampoVetorialId);
    glutAddMenuEntry("Campo Ventilador", 6);
    glutAddMenuEntry("Sair", 0);
}

GLuint loadTexture(const char * fileName) {
    // Data read from the header of the BMP file
    unsigned char header[54]; // Each BMP file begins by a 54-bytes header
    unsigned int dataPos; // Position in the file where the actual data begins
    unsigned int width, height;
    unsigned int imageSize; // = width*height*3

    GLuint texture;
    unsigned char * data;

    FILE * file;

    //The following code will read in our RAW file
    file = fopen(fileName, "rb");
    if (file == NULL) return 0;
    if (fread(header, 1, 54, file) != 54) { // If not 54 bytes read : problem
        printf("Not a correct BMP file\n");
        return false;
    }
    if (header[0] != 'B' || header[1] != 'M') {
        printf("Not a correct BMP file\n");
        return 0;
    }

    // Read ints from the byte array
    dataPos = *(int*) &(header[0x0A]);
    imageSize = *(int*) &(header[0x22]);
    width = *(int*) &(header[0x12]);
    height = *(int*) &(header[0x16]);

    data = (unsigned char *) malloc(width * height * 3);
    fread(data, width * height * 3, 1, file);
    fclose(file);

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    //glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    //glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

    //even better quality, but this will do for now.
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    //to the edge of our shape. 
    //glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    //glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    //Generate the texture
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    return texture; //return whether it was successful
}

int main(int argc, char** argv) {

    //t.join();
    srand(time(NULL));

    ventilador->set(200, 300);
    ventilador->setForce(20);
    ventilador->setDelay(delay);

    gravidade->setForce(10);

    for (int i = 0; i < fios; i++)
        cabelo[i].setCampoVetorial(gravidade);

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(LARGURA, ALTURA);
    glutInitWindowPosition(20, 20);
    glutCreateWindow("Cabelo");
    glutReshapeFunc(AlteraTamanhoJanela);

    glutDisplayFunc(display);

    glutMouseFunc(escolha);
    glutMotionFunc(captura);

    glutTimerFunc(0, timer, 0);

    criaMenu();

    texture = loadTexture("backgroundImage.bmp");

    if (texture == 0)
        cout << "Arquivo Inválido." << endl;
    glutMainLoop();
}