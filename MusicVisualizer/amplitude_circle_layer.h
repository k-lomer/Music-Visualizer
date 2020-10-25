#pragma once

#include "visual_layer.h"

// An animated circle whose size varies with the current amplitude
class AmplitudeCircleLayer : public VisualLayer {
public:
    // param: centre - the centre of the circle
    // param: pixel_radius - the maximum radius of the circle in pixels
    // param: circle_color - the color of the circle
    AmplitudeCircleLayer(SDL_Point centre, int pixel_radius, SDL_Color circle_color) : max_pixel_radius(pixel_radius), color(circle_color) { translation = centre; }

    virtual void draw(SDL_Renderer * const renderer, const SignalBox & signal_box) override;

private:
    int max_pixel_radius;
    SDL_Color color;
    SDL_Point translation;
};
