#include <GL/glut.h>

#include "texture_earth.hpp"
#include "texture_moon.hpp"

GLfloat earthRotation = 0.0f;
GLfloat earthAxisRotation = 0.0f;
GLfloat moonRotation = 0.0f;
GLfloat Interval = 15.0f;
GLfloat timeScale = 1.0f;
GLfloat earthRotationSpeed = 360.0f / (365.0f * Interval);
GLfloat earthAxisRotationSpeed = 360.0f / (1.0f * Interval);
GLfloat moonRotationSpeed = 360.0f / (30.0f * Interval);
int cameraMode = 1;
bool lightingEnabled = false;
Texture_earth Texture_e = Texture_earth{};
Texture_moon Texture_m = Texture_moon{};

// Inicijalizacija OpenGL parametara
void initialize() {
    glClearColor(0.0, 0.0, 0.0, 1.0);  // Podesava boju pozadine
    glEnable(GL_DEPTH_TEST);           // Efekat dubine u sceni
    glMatrixMode(GL_PROJECTION);  // Postavlja matricu za predstojece operacije
    glLoadIdentity();             // Postavlja jedinicnu matricu za trenutnu
    gluPerspective(45.0, 1.0, 1.0,
                   10.0);  // Definise matricu perspektivne projekcije
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0.0, 0.0, -5.0);
    Texture_e.TextureInit();
    Texture_m.TextureInit();
}

// Funkcija za azuriranje kamere
void updateCamera() {
    // Odabir postavke kamere na temelju trenutne vrijednosti cameraMode
    if (cameraMode == 1) {
        gluLookAt(0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
    } else if (cameraMode == 2) {
        gluLookAt(0.0, 3.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
    } else if (cameraMode == 3) {
        gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    }
}

// Funkcija za azuriranje animacije
void updateAnimation(int value) {
    earthRotation += earthRotationSpeed * timeScale;
    earthAxisRotation += earthAxisRotationSpeed * timeScale;
    moonRotation += moonRotationSpeed * timeScale;
    glutPostRedisplay();
    glutTimerFunc(1000 / 60, updateAnimation,
                  0);  // Postavljanje tajmera za datu funkciju
}

// Funkcija za ubrzavanje/usporavanje rotacija klikom misa
void mouse(int button, int state, int x, int y) {
    if (state == GLUT_DOWN) {
        if (button == GLUT_LEFT_BUTTON) {
            timeScale *= 2.0f;
        } else if (button == GLUT_RIGHT_BUTTON) {
            timeScale *= 0.5f;
        }
    }
    glutPostRedisplay();
}

// Funkcija za promjenu pozicije kamere klikom odgovarajucih tipki na tastaturi
void keyboard(unsigned char key, int x, int y) {
    if (key == '1') {
        cameraMode = 1;
    } else if (key == '2') {
        cameraMode = 2;
    } else if (key == '3') {
        cameraMode = 3;
    } else if (key == 'l' || key == 'L') {
        lightingEnabled = !lightingEnabled;
    }
    glutPostRedisplay();
}

