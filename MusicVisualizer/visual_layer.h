#pragma once

#include <vector>

#include "SDL.h"

class VisualLayer {
public:
	typedef std::vector<float> packet;
	virtual void draw(SDL_Renderer * const renderer, const packet & packet_buffer) = 0;
	virtual ~VisualLayer() {};

	double rotation = 0.0;
	double scale = 1.0;
	SDL_Point translation = SDL_Point{ 0, 0 };
};

enum orientation{Horizontal, Vertical};

