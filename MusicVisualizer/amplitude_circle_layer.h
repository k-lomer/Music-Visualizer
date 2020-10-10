#pragma once

#include "visual_layer.h"

class AmplitudeCircleLayer : public VisualLayer {
public:
	AmplitudeCircleLayer(SDL_Point centre, int pixel_radius, SDL_Color circle_color) : max_pixel_radius(pixel_radius), color(circle_color) { translation = centre; }

	virtual void draw(SDL_Renderer * const renderer, const packet & packet_buffer) override;

private:
	int max_pixel_radius;
	SDL_Color color;
};