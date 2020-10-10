#include "polygon_layer.h"

#include "draw_utilities.h"

PolygonLayer::PolygonLayer(int num_sides, int radius, SDL_Point poly_centre, int wave_amplitude, SDL_Color wave_color)
	: centre(poly_centre), amplitude(wave_amplitude), color(wave_color) {
	SDL_Point first_point = rotate_point(SDL_Point{poly_centre.x, poly_centre.y + radius}, poly_centre, 2*M_PI/num_sides / 2);
	vertices.push_back(first_point);
	for (int i = 1; i < num_sides; ++i) {
		vertices.push_back(rotate_point(first_point, poly_centre, 2 * M_PI * i / num_sides));
	}
}

void PolygonLayer::draw(SDL_Renderer * renderer, const packet & packet_buffer) {
	for (int i = 0; i < vertices.size(); ++i) {
		draw_wave(renderer, packet_buffer, vertices[i], vertices[(i+1) % vertices.size()], amplitude, color);
	}
}
