#include <state.hpp>

State::State(Config *c, Input *i) : config(c), input(i) {
  renderer = new RenderManager();
};

void State::update(float dt) {
  for (int i = 0; i < entities.size(); i++) {
    entities[i]->tick(dt);
    entities[i]->debug();
  }
}

void State::start() {};
void State::exit() {};

void State::changeState(State *s) {
  stateToSwap = s;
}

State* State::nextState() {
  return stateToSwap;
}

void State::add(Entity *e) {
  e->_init(this);

  entities.push_back(e);
}
