#include "amplitude_circle_layer.h"

#include "../Utilities/dsp_utilities.h"
#include "../Utilities/draw_utilities.h"

void AmplitudeCircleLayer::draw(SDL_Renderer * const renderer, const wave & signal) {
    int radius = int(abs_max(signal) * float(max_pixel_radius));
    draw_circle(renderer, translation, radius, color, radius / 2);
}
