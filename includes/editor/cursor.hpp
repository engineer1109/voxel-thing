#ifndef CURSOR_H
#define CURSOR_H

#include <glm/glm.hpp>

#include <E/entity.hpp>

namespace editor {
  struct Cursor : public E::Entity {
    float speed = 10.0f;

    glm::vec3 position = { 10.0f, 2.0f, 10.0f };
    glm::vec3 facing = { 0.0f, 0.0f, -1.0f };

    void init();
    void tick(float dt);

    private:
    float sensitivity = 0.3;
    float pitch = 0;
    float yaw = 0;
  };
};

#endif
