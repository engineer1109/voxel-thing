#include <E/texture_atlas.hpp>

E::TextureAtlas::TextureAtlas(std::string fname, int cs) : Texture(fname), cellSize(cs) {}

std::vector<glm::vec2> E::TextureAtlas::uvs(glm::ivec2 coords) {
  static const GLfloat TEX_PER_ROW      = (GLfloat)width / (GLfloat)cellSize;
  static const GLfloat INDV_TEX_SIZE    = 1.0f / TEX_PER_ROW;
  static const GLfloat PIXEL_SIZE       = 1.0f / (float)width;

  GLfloat xMin = (coords.x * INDV_TEX_SIZE) + 0.5 * PIXEL_SIZE;
  GLfloat yMin = (coords.y * INDV_TEX_SIZE) + 0.5 * PIXEL_SIZE;

  GLfloat xMax = (xMin + INDV_TEX_SIZE) - 0.5 * PIXEL_SIZE;
  GLfloat yMax = (yMin + INDV_TEX_SIZE) - 0.5 * PIXEL_SIZE;

  return {
    glm::vec2(xMax, yMin),
    glm::vec2(xMax, yMax),
    glm::vec2(xMin, yMin),
    glm::vec2(xMax, yMax),
    glm::vec2(xMin, yMax),
    glm::vec2(xMin, yMin)
  };
}
