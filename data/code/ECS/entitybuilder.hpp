#pragma once

#include "components.hpp"

/*

Purpose of this file is to create a set of entity templates that can be called in order to generate an entity dynamically
*/

Entity& buildWorld(Entity* entityTemplate, const int size, const int numChunks);

Entity& buildPlayer();