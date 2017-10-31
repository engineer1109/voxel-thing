#include <E/state.hpp>

E::State::State(Config *c, Input *i) : config(c), input(i) {
  renderer = new RenderManager();
};

void E::State::update(float dt) {
  for (int i = 0; i < entities.size(); i++) {
    entities[i]->tick(dt);
    entities[i]->debug();
  }
}

void E::State::start() {};
void E::State::exit() {};

void E::State::changeState(State *s) {
  stateToSwap = s;
}

E::State* E::State::nextState() {
  return stateToSwap;
}

void E::State::add(Entity *e) {
  e->_init(this);

  entities.push_back(e);
}
