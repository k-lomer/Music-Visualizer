#pragma once

#include <vector>
#include "../Utilities/dsp_utilities.h"
#include "SDL.h"

class VisualLayer {
public:
    typedef std::vector<float> packet; // a packet of audio data
    
    // Draw the layer
    // param: renderer - the SDL renderer to draw the layer on
    // pararm: signal - contains audio signal information
    virtual void draw(SDL_Renderer * const renderer, const wave & signal) = 0;
    virtual ~VisualLayer() {};
};

enum orientation{Horizontal, Vertical};
