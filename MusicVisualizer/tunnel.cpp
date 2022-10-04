#include "tunnel.h"

#include <memory>

#include "screen_box_layer.h"

TunnelLayer::TunnelLayer(int width, int height, int num_waves, int levels, int wave_amplitude, SDL_Color wave_color, double box_scale_rate)
    : wave_count(num_waves), window_width(width), window_height(height), amplitude(wave_amplitude), color(wave_color), scale_rate(box_scale_rate){
    add_layer(std::make_unique<ScreenBoxLayer>(wave_count, window_width, window_height, amplitude, color, 1.0, scale_rate));

    for (int i = 0; i <= levels; ++i) {
        add_layer(std::make_unique<ScreenBoxLayer>(wave_count, window_width, window_height, amplitude, color, double(levels - i) / double(levels + 1), scale_rate));
    }

    scale_difference = 1.0 / double(levels + 1);
}

void TunnelLayer::draw(SDL_Renderer * const renderer, const wave & signal) {
    if (scale_rate > 0.0) {
        // check if largest box is still visible
        ScreenBoxLayer & largest_box = dynamic_cast<ScreenBoxLayer &>(*visual_layers.front());
        if (largest_box.get_scale() > 1.0 + scale_difference) {
            visual_layers.pop_front();
        }
        // check if smaller box needs to be added
        ScreenBoxLayer & smallest_box = dynamic_cast<ScreenBoxLayer &>(*visual_layers.back());
        if (smallest_box.get_scale() > 0.0) {
            add_layer(std::make_unique<ScreenBoxLayer>(wave_count, window_width, window_height, amplitude, color, smallest_box.get_scale() - scale_difference, scale_rate));
        }
    }
    else if (scale_rate < 0.0) {
        // check if smallest box is still visible
        ScreenBoxLayer & smallest_box = dynamic_cast<ScreenBoxLayer &>(*visual_layers.back());
        if (smallest_box.get_scale() <= 0.0) {
            visual_layers.pop_back();
        }
        // check if larger box needs to be added
        ScreenBoxLayer & largest_box = dynamic_cast<ScreenBoxLayer &>(*visual_layers.front());
        if (largest_box.get_scale() < 1.0) {
            visual_layers.push_front(std::make_unique<ScreenBoxLayer>(wave_count, window_width, window_height, amplitude, color, largest_box.get_scale() + scale_difference, scale_rate));
        }
    }

    CompositeLayer::draw(renderer, signal);
}
