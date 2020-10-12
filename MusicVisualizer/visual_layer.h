#pragma once

#include <vector>

#include "SDL.h"

class VisualLayer {
public:
    typedef std::vector<float> packet; // a packet of audio data
    
    // Draw the layer
    // param: renderer - the SDL renderer to draw the layer on
    // pararm: packet_buffer - a packet of audio data, each frame ranges in value from -1 to 1
    virtual void draw(SDL_Renderer * const renderer, const packet & packet_buffer) = 0;
    virtual ~VisualLayer() {};

    double rotation = 0.0;
    double scale = 1.0;
    SDL_Point translation = SDL_Point{ 0, 0 };
};

enum orientation{Horizontal, Vertical};
