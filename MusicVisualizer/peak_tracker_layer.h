#pragma once

#include "SDL.h"
#include "visual_layer.h"
#include "../Utilities/prominent_peaks.h"

// A class which displays the peak positions overlayed on the wave.
class PeakTrackerLayer : public VisualLayer {
public:
    // PeakTrackerLayer constructor.
    // param: num_peaks                     - the number of peaks to track
    // param: window_width                  - the width of the window
    // param: window_height                 - the height of the window
    PeakTrackerLayer(int num_peaks, int window_width, int window_height, SDL_Color peak_color);

    // Draw the PeakTrackerLayer.
    // param: renderer                      - the renderer to draw the PeakTrackerLayer
    // param: signal                        - the signal to draw
    void draw(SDL_Renderer * const renderer, const wave & signal) override;

private:
    // The class which identifies the prominent peaks.
    ProminentPeaks m_peaks;
    // The width of the window.
    int m_window_width;
    // The height of the window.
    int m_window_height;
    // The color of the wave.
    SDL_Color m_color;
    // The start point of the wave.
    SDL_Point m_start;
    // The end point of the wave.
    SDL_Point m_end;
};