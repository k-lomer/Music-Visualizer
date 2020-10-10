#pragma once

#include "visual_layer.h"

class PolygonLayer : public VisualLayer {
public:
	PolygonLayer(int num_sides, int radius, SDL_Point poly_centre, int wave_amplitude, SDL_Color wave_color);

	virtual void draw(SDL_Renderer * renderer, const packet & packet_buffer) override;

private:
	SDL_Point centre;
	int amplitude;
	SDL_Color color;
	std::vector<SDL_Point> vertices;
};