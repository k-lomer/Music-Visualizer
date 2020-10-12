#include "amplitude_circle_layer.h"

#include <algorithm>

#include "draw_utilities.h"

void AmplitudeCircleLayer::draw(SDL_Renderer * const renderer, const packet & packet_buffer) {
    int new_radius = 0;
    if (!packet_buffer.empty()) {
        float max_amplitude = *max_element(std::begin(packet_buffer), std::end(packet_buffer));
        new_radius = int(max_amplitude * float(scale) * float(max_pixel_radius));
    }
    if (new_radius > current_radius){
        current_radius = new_radius;
    }
    else {
        current_radius = int(previous_weight * float(current_radius) + (1.0f - previous_weight) * float(new_radius));
    }
    draw_circle(renderer, translation, current_radius, color);
}
