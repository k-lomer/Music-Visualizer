#pragma once

#include "composite_layer.h"
#include "SDL.h"

// A grid of pulsing circles
class CircleGridLayer : public virtual CompositeLayer {
public:
    // param: colors - a vector of the colors of layers of the circles from outer to inner
    // param: rows - the number of rows of circles
    // param: cols - the number of columns of circles
    // param: screen_width - the pixel width of the screen
    // param: screen_height - the pixel height of the screen
    CircleGridLayer(const std::vector<SDL_Color> & colors, int rows, int cols, int screen_width, int screen_height);
};
