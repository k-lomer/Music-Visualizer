#include "amplitude_circle_layer.h"

#include "draw_utilities.h"

void AmplitudeCircleLayer::draw(SDL_Renderer * const renderer, const SignalBox & signal_box) {
    int radius = int(signal_box.get_max(true) * float(max_pixel_radius));
    draw_circle(renderer, translation, radius, color);
}
