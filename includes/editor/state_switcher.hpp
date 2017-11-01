#ifndef STATE_SWITCHER_H
#define STATE_SWITCHER_H

#include <E/entity.hpp>

namespace editor {
  struct StateSwitcher : public E::Entity {
    void tick(float dt);
  };
};

#endif
