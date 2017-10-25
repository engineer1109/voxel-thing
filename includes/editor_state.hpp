#ifndef EDITOR_STATE_H
#define EDITOR_STATE_H

#include <state.hpp>

#include <shader.hpp>
#include <world.hpp>

class EditorState : public State {
  public:
    using State::State;

    void start();
    void update(float dt);
    void render();
  private:
    Shader *worldShader;
    World *world;
};

#endif
