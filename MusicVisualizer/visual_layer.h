#pragma once

#include <vector>
#include "../Utilities/dsp_utilities.h"
#include "SDL.h"

class VisualLayer {
public:
    // Draw the VisualLayer.
    // param: renderer                      - the renderer to draw the VisualLayer
    // param: signal                        - the signal to draw
    virtual void draw(SDL_Renderer * const renderer, const wave & signal) = 0;
    // VisualLayer destructor.
    virtual ~VisualLayer() {};
};

// The orientation of an object.
enum Orientation{Horizontal, Vertical};
