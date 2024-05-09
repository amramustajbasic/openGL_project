#include <GL/glut.h>

#include "spheres.hpp"
#include "texture_earth.hpp"
#include "texture_moon.hpp"

// Main funkcija
int main(int argc, char** argv) {
    glutInit(&argc, argv);  // Inicijalizacija GLUT biblioteke i pocetak sesije
                            // sa window sistemom
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE |
                        GLUT_DEPTH);       // Postavke prozora
    glutInitWindowSize(800, 600);          // Velicina prozora
    glutCreateWindow("Zavrsni projekat");  // Kreiranje prozora
    initialize();                          // Inicijalizacija OPENGL parametara
    glutDisplayFunc(
        drawScene);  // Postavlja display callback funkciju za trenutni prozor
    glutMouseFunc(mouse);  // Postavlja callback funkciju za mis
    glutKeyboardFunc(
        keyboard);  // Postavlja callback funkciju za unos sa tastature
    glutTimerFunc(0, updateAnimation,
                  0);  // Postavlja tajmer koji redovno azurira animaciju
    glutMainLoop();    // Zapocinje GLUT event processing petlju
    return 0;
}

