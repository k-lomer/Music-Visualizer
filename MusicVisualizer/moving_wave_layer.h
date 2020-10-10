#pragma once

#include "visual_layer.h"
#include <vector>

class MovingWaveLayer : public VisualLayer {
public:
	MovingWaveLayer(int num_waves, orientation wave_orientation, double wave_movement, int width, int height, int wave_amplitude, SDL_Color wave_color);

	virtual void draw(SDL_Renderer * renderer, const packet & packet_buffer) override;

private:
	orientation wave_orientation;
	double movement;
	int window_width;
	int window_height;
	int amplitude;
	SDL_Color color;
	std::vector<double> wave_positions;
};
