#ifndef TOOLTIP_H
#define TOOLTIP_H

#include <E/entity.hpp>
#include <E/utils.hpp>

#include <block.hpp>

namespace editor {
  struct Tooltip : public E::Entity {
    glm::vec3 position;
    BlockSide side;

    glm::vec3 color = { 1.0f, 0.0f, 0.0f };

    bool shouldRender = true;

    void init();
    void tick(float dt);

    void getBlockToPlace();

    private:
    BlockSide diff(E::Index c1, E::Index b1, E::Index c2, E::Index b2);
    int blockTypeToPlace = 1;
  };
};

#endif
