#include <GL/glut.h>

#include "functions.hpp"
#include "texture_earth.hpp"
#include "texture_moon.hpp"

// Funkcija za crtanje sfere
void drawSphere(GLfloat radius) {
    GLUquadric* quad = gluNewQuadric();
    gluQuadricDrawStyle(quad, GLU_FILL);
    gluQuadricTexture(quad, GL_TRUE);
    gluQuadricNormals(quad, GLU_SMOOTH);
    gluSphere(quad, radius, 32, 32);
    gluDeleteQuadric(quad);
}

// Postavke svjetla
void enableLighting() {
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);  // Ukljucivanje svjetla

    GLfloat lightAmbient[] = {0.2f, 0.2f, 0.2f, 1.0f};
    GLfloat lightDiffuse[] = {1.0f, 1.0f, 1.0f, 1.0f};
    GLfloat lightSpecular[] = {1.0f, 1.0f, 1.0f, 1.0f};
    GLfloat lightPosition[] = {0.0f, 1.0f, 0.0f, 1.0f};

    glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular);
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
}

void disableLighting() {
    glDisable(GL_LIGHTING);
    glDisable(GL_LIGHT0);  // Iskljucivanje svjetla
}

// Crtanje Sunca
void drawSun() {
    if (lightingEnabled) {
        enableLighting();

    } else {
        disableLighting();
        glColor3f(0.7, 0.7, 0.7);
    }

    // Postavke materijala za sunce
    GLfloat sunMaterialAmbient[] = {0.8f, 0.8f, 0.8f, 1.0f};
    GLfloat sunMaterialDiffuse[] = {0.8f, 0.8f, 0.8f, 1.0f};
    GLfloat sunMaterialSpecular[] = {1.0f, 1.0f, 1.0f, 1.0f};
    glMaterialfv(GL_FRONT, GL_AMBIENT, sunMaterialAmbient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, sunMaterialDiffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, sunMaterialSpecular);
    glMaterialf(GL_FRONT, GL_SHININESS, 50.0f);

    drawSphere(0.5);
}

// Crtanje Zemlje
void drawEarth() {
    // Translacija i rotacija Zemlje
    Texture_e.TextureBegin();
    glRotatef(earthRotation, 0.0, 0.0, 1.0);
    glTranslatef(1.0, 0.0, 0.0);
    glPushMatrix();
    glRotatef(earthAxisRotation, 0.0, 0.0, 1.0);

    // Postavke materijala za Zemlju
    GLfloat earthAmbient[] = {0.0f, 0.2f, 0.2f, 1.0f};
    GLfloat earthDiffuse[] = {0.0f, 0.5f, 0.5f, 1.0f};
    GLfloat earthSpecular[] = {0.0f, 0.0f, 0.0f, 1.0f};
    glMaterialfv(GL_FRONT, GL_AMBIENT, earthAmbient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, earthDiffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, earthSpecular);
    glMaterialf(GL_FRONT, GL_SHININESS, 50.0f);

    glColor3f(0.0, 0.0, 0.8);
    drawSphere(0.2);
    Texture_e.TextureEnd();
}

// Crtanje Mjeseca
void drawMoon() {
    Texture_m.TextureBegin();
    glPopMatrix();

    // Translacija i rotacija Mjeseca
    glRotatef(moonRotation, 0.0, 0.0, 1.0);
    glTranslatef(0.3, 0.0, 0.0);

    // Postavke materijala za Mjesec
    GLfloat moonAmbient[] = {0.5f, 0.5f, 0.5f, 1.0f};
    GLfloat moonDiffuse[] = {0.5f, 0.5f, 0.5f, 1.0f};
    GLfloat moonSpecular[] = {1.0f, 1.0f, 1.0f, 1.0f};

    glMaterialfv(GL_FRONT, GL_AMBIENT, moonAmbient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, moonDiffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, moonSpecular);
    glMaterialf(GL_FRONT, GL_SHININESS, 100.0f);

    glColor3f(0.4, 0.4, 0.4);
    drawSphere(0.05);
    Texture_m.TextureEnd();
}

// Funkcija za iscrtavanje scene
void drawScene() {
    glClear(GL_COLOR_BUFFER_BIT |
            GL_DEPTH_BUFFER_BIT);  // Ciscenje framebuffer-a
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();  // Postavljanje jedinicne matrice za trenutnu

    updateCamera();  // Postavljanje kamere
    drawSun();
    drawEarth();
    drawMoon();
    glutSwapBuffers();  // Operacija zamjene buffer-a
}
