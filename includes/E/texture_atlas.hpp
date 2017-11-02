#pragma once

#include <vector>

#include <glm/glm.hpp>

#include <E/texture.hpp>

namespace E {
  class TextureAtlas : public Texture {
    public:
      TextureAtlas(std::string fname, int cs);

      std::vector<glm::vec2> uvs(glm::ivec2 coord);

    private:
      int cellSize;
  };
}
