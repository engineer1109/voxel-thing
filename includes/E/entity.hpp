#ifndef ENTITY_H
#define ENTITY_H

namespace E {
  class State;

  struct Entity {
    E::State *state;

    unsigned int flags = 0;

    void _init(E::State *s) { state = s; init(); }

    virtual void init() {};
    virtual void tick(float dt) {};
    virtual void debug() {};
  };
};

#endif
