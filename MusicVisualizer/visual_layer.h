#pragma once

#include <vector>

#include "SDL.h"
#include "signal_box.h"

class VisualLayer {
public:
    typedef std::vector<float> packet; // a packet of audio data
    
    // Draw the layer
    // param: renderer - the SDL renderer to draw the layer on
    // pararm: signal_box - contains audio signal information
    virtual void draw(SDL_Renderer * const renderer, const SignalBox & signal_box) = 0;
    virtual ~VisualLayer() {};

protected:
    double rotation = 0.0;
    double scale = 1.0;
    SDL_Point translation = SDL_Point{ 0, 0 };
    SignalFlag signal_type = Decay | Reflect;
};

enum orientation{Horizontal, Vertical};
