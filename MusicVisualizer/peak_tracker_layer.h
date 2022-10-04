#pragma once

#include "SDL.h"
#include "visual_layer.h"
#include "../Utilities/prominent_peaks.h"

// A class which displays the peaks from a wave
class PeakTrackerLayer : public VisualLayer {
public:
    PeakTrackerLayer(int num_peaks, int window_width, int window_height, SDL_Color peak_color);

    void draw(SDL_Renderer * const renderer, const wave & signal) override;

private:
    ProminentPeaks peaks;
    int window_width;
    int window_height;
    SDL_Color color;
    SDL_Point start;
    SDL_Point end;
};