#include <state.hpp>

State::State(Input *i) : input(i) {};

void State::start() {};
void State::update(float dt) {};
void State::render() {};
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
