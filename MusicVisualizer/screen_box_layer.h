#pragma once

#include "visual_layer.h"

class ScreenBoxLayer : public VisualLayer {
public:
	ScreenBoxLayer(int width, int height, int wave_amplitude, SDL_Color wave_color)
		: window_width(width), window_height(height), amplitude(wave_amplitude), color(wave_color) {}

	virtual void draw(SDL_Renderer * renderer, const packet & packet_buffer) override;

private:
	int window_width;
	int window_height;
	int amplitude;
	SDL_Color color;
};
