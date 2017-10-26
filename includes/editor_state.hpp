#ifndef EDITOR_STATE_H
#define EDITOR_STATE_H

#include <state.hpp>

#include <shader.hpp>
#include <world.hpp>

// The editor state is where we're going to be building our game from. It'll do a couple of things:
//  - Provide a way to edit the different voxel types (texture, properties)
//  - Have a map editor (place blocks, remove blocks)
//  - Edit the story portion of the game (ie. navigation paths for characters, dialog)
class EditorState : public State {
  public:
    using State::State;

    void start();
    void render();
  private:
    Shader *worldShader;
    World *world;
};

#endif
