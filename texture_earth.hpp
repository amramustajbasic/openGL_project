#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <GL/glut.h>

#include "earth.c"
// Kod koji implementira teksturu
class Texture_earth {
   public:
    void TextureBegin() {
        glEnable(GL_TEXTURE_2D);

        glBindTexture(GL_TEXTURE_2D, texture_);
        // pattern slika koja je putem GIMP alata konvertirana u .c format
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, gimp_image.width,
                     gimp_image.height, 0, GL_RGBA, GL_UNSIGNED_BYTE,
                     gimp_image.pixel_data);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
    }
    void TextureEnd() { glDisable(GL_TEXTURE_2D); }

    void TextureInit() {
        glGenTextures(1, &texture_);
        glEnable(GL_TEXTURE_2D);
    }

   private:
    GLuint texture_;
};

#endif
