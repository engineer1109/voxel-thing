#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>
#include <glad/glad.h>

namespace E {
  class Texture {
    public:
      Texture(std::string fname);

      int width;
      int height;

      void use(unsigned int unit=GL_TEXTURE0);
    private:
      unsigned int id;
  };
}

#endif
