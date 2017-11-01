#ifndef EDITOR_INFO_PANE_H
#define EDITOR_INFO_PANE_H

#include <E/entity.hpp>

namespace editor {
  struct EditorInfoPane : public E::Entity {
    void tick(float dt);
  };
};

#endif
