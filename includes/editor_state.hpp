#ifndef EDITOR_STATE_H
#define EDITOR_STATE_H

#include <E/state.hpp>

// The editor state is where we're going to be building our game from. It'll do a couple of things:
//  - Provide a way to edit the different voxel types (texture, properties)
//  - Have a map editor (place blocks, remove blocks)
//  - Edit the story portion of the game (ie. navigation paths for characters, dialog)
class EditorState : public E::State {
  public:
    using State::State;

    void start();
};

#endif
