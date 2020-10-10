#include "amplitude_circle_layer.h"

#include <algorithm>

#include "draw_utilities.h"

void AmplitudeCircleLayer::draw(SDL_Renderer * const renderer, const packet & packet_buffer) {
	if (!packet_buffer.empty()) {
		float max_amplitude = *max_element(std::begin(packet_buffer), std::end(packet_buffer));
		int radius = int(max_amplitude * float(scale) * float(max_pixel_radius));
		draw_circle(renderer, translation, radius, color);
	}
}