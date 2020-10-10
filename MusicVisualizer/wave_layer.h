#pragma once

#include "visual_layer.h"

class WaveLayer : public VisualLayer {
public:
	WaveLayer(int num_waves, SDL_Point wave_start, SDL_Point wave_end, int wave_amplitude, SDL_Color wave_color)
		: wave_count(num_waves), start(wave_start), end(wave_end), amplitude(wave_amplitude), color(wave_color) {}

	virtual void draw(SDL_Renderer * renderer, const packet & packet_buffer) override;

private:
	int wave_count;
	SDL_Point start;
	SDL_Point end;
	int amplitude;
	SDL_Color color;
};