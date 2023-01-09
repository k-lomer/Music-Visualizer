#pragma once

#pragma once

#include "visual_layer.h"

// Audio bars between two points.
class BarsLayer : public VisualLayer {
public:
    // Bars layer constructor.
    // param: divisions                         - the number of bars to draw
    // param: bars_start                        - the coordinates of the start of the bars
    // param: bars_end                          - the coordinates of the end of the bars
    // param: bars_amplitude                    - the the maximum pixel amplitude of the bars
    // param: bars_color                        - the color of the bars
    // param: bars_gap                          - the number of pixels between bars
    BarsLayer(int num_bars, SDL_Point bars_start, SDL_Point bars_end, int bars_amplitude, SDL_Color bars_color, int bars_gap )
        : divisions(num_bars), start(bars_start), end(bars_end), amplitude(bars_amplitude), color(bars_color), gap_pixels(bars_gap){}

    // Draw the BarsLayer.
    // param: renderer                          - the renderer to draw the BarsLayer
    // param: signal                            - the signal to draw
    virtual void draw(SDL_Renderer * renderer, const wave & signal) override;

private:
    // The number of divisions for the bars.
    int divisions;
    // The start point of the bars.
    SDL_Point start;
    // The end point of the bars.
    SDL_Point end;
    // The maximum amplitude of the bars.
    int amplitude;
    // The color to draw the bars.
    SDL_Color color;
    // The pixel gap between the bars.
    int gap_pixels;
};
