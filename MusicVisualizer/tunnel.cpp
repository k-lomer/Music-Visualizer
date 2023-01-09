#include "tunnel.h"

#include <memory>

#include "screen_box_layer.h"

TunnelLayer::TunnelLayer(int width, int height, int num_waves, int levels, int wave_amplitude, SDL_Color wave_color, double box_scale_rate)
    : m_wave_count(num_waves), m_window_width(width), m_window_height(height), m_amplitude(wave_amplitude), m_color(wave_color), m_scale_rate(box_scale_rate){
    add_layer(std::make_unique<ScreenBoxLayer>(m_wave_count, m_window_width, m_window_height, m_amplitude, m_color, 1.0, m_scale_rate));

    for (int i = 0; i <= levels; ++i) {
        add_layer(std::make_unique<ScreenBoxLayer>(m_wave_count, m_window_width, m_window_height, m_amplitude, m_color, double(levels - i) / double(levels + 1), m_scale_rate));
    }

    m_scale_difference = 1.0 / double(levels + 1);
}

void TunnelLayer::draw(SDL_Renderer * const renderer, const wave & signal) {
    if (m_scale_rate > 0.0) {
        // Check if the largest box is still visible.
        ScreenBoxLayer & largest_box = dynamic_cast<ScreenBoxLayer &>(*m_visual_layers.front());
        if (largest_box.get_scale() > 1.0 + m_scale_difference) {
            m_visual_layers.pop_front();
        }
        // Check if smaller box needs to be added.
        ScreenBoxLayer & smallest_box = dynamic_cast<ScreenBoxLayer &>(*m_visual_layers.back());
        if (smallest_box.get_scale() > 0.0) {
            add_layer(std::make_unique<ScreenBoxLayer>(m_wave_count, m_window_width, m_window_height, m_amplitude, m_color, smallest_box.get_scale() - m_scale_difference, m_scale_rate));
        }
    }
    else if (m_scale_rate < 0.0) {
        // Check if smallest box is still visible.
        ScreenBoxLayer & smallest_box = dynamic_cast<ScreenBoxLayer &>(*m_visual_layers.back());
        if (smallest_box.get_scale() <= 0.0) {
            m_visual_layers.pop_back();
        }
        // Check if larger box needs to be added.
        ScreenBoxLayer & largest_box = dynamic_cast<ScreenBoxLayer &>(*m_visual_layers.front());
        if (largest_box.get_scale() < 1.0) {
            m_visual_layers.push_front(std::make_unique<ScreenBoxLayer>(m_wave_count, m_window_width, m_window_height, m_amplitude, m_color, largest_box.get_scale() + m_scale_difference, m_scale_rate));
        }
    }

    CompositeLayer::draw(renderer, signal);
}
