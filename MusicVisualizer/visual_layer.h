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

    // Get the layer precedence.
    int get_precedence() { return m_precedence; }

    // Set the layer precedence.
    void set_precedence(int precedence) { m_precedence = precedence; }

private:
    // The drawing precedence for this layer.
    int m_precedence;
};

// The orientation of an object.
enum Orientation{Horizontal, Vertical};
