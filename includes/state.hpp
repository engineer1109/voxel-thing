#ifndef STATE_H
#define STATE_H

#include <vector>

#include <entity.hpp>
#include <camera.hpp>
#include <input.hpp>
#include <config.hpp>
#include <render_manager.hpp>
#include <world.hpp>

class State {
  public:
    explicit State(Config *c, Input *i);

    // lifecycle
    virtual void start();
    virtual void update(float dt);
    virtual void render();
    virtual void exit();

    // entity mgmt
    void add(Entity *e);

    // state mgmt
    void changeState(State *s);
    State* nextState();

    Camera camera;
    Input *input;
    Config *config;
    RenderManager *renderer;

    World *world;
  protected:
    std::vector<Entity*> entities;
  private:
    State* stateToSwap = NULL;
};

#endif
