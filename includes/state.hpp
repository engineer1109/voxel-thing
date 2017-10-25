#ifndef STATE_H
#define STATE_H

#include <vector>

#include <entity.hpp>
#include <camera.hpp>
#include <input.hpp>

const float SCREEN_WIDTH=1600.0f;
const float SCREEN_HEIGHT=900.0f;

class State {
  public:
    explicit State(Input *i);

    // lifecycle
    virtual void start();
    virtual void update(float dt);
    virtual void render();
    virtual void exit();

    // entity mgmt
    void add(Entity *e);

    void changeState(State *s);

    State* nextState();

    Camera camera;
    Input *input;
  protected:
    std::vector<Entity*> entities;
  private:
    State* stateToSwap = NULL;
};

#endif
