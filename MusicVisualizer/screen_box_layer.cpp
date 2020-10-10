#include "screen_box_layer.h"

#include "draw_utilities.h"

void ScreenBoxLayer::draw(SDL_Renderer * const renderer, const packet & packet_buffer) {
	int wave_amplitude = int(amplitude * scale);
	draw_wave(renderer, packet_buffer, SDL_Point{ 0, 0 }, SDL_Point{ 0, window_height }, wave_amplitude, color);
	draw_wave(renderer, packet_buffer, SDL_Point{ 0, 0 }, SDL_Point{ window_width, 0}, wave_amplitude, color);
	draw_wave(renderer, packet_buffer, SDL_Point{ 0, window_height}, SDL_Point{ window_width, window_height }, wave_amplitude, color);
	draw_wave(renderer, packet_buffer, SDL_Point{ window_width, 0 }, SDL_Point{ window_width, window_height }, wave_amplitude, color);
}