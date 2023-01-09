#include "unknown_pleasure_layer.h"

#include "../Utilities/draw_utilities.h"

UnknownPleasureLayer::UnknownPleasureLayer(int num_waves, int frame_delay, SDL_Point first_wave_start, SDL_Point first_wave_end,
    SDL_Point last_wave_start, SDL_Point last_wave_end, int wave_amplitude, const std::vector<SDL_Color> & wave_colors, UnknownPleasureFill fill_waves)
    : wave_count(num_waves), delay(frame_delay), front_start(first_wave_start), front_end(first_wave_end),
    back_start(last_wave_start), back_end(last_wave_end), amplitude(wave_amplitude), line_colors()
{
    for (int i = 0; i < wave_count * delay + 1; ++i) {
        waveforms.emplace_back();
    }

    switch (fill_waves) {
    case UnknownPleasureFill::None: {
        line_colors = wave_colors;
        break;
    }
    case UnknownPleasureFill::Black: {
        line_colors = wave_colors;
        fill_colors.push_back(SDL_Color{ 0, 0, 0, SDL_ALPHA_OPAQUE });
        break;
    }
    case UnknownPleasureFill::Color: {
        line_colors.push_back(SDL_Color{ 0, 0, 0, SDL_ALPHA_OPAQUE });
        fill_colors = wave_colors;
        break;
    }
    }
}

void UnknownPleasureLayer::draw(SDL_Renderer * renderer, const wave & signal) {
    waveforms.push_front(signal);
    waveforms.pop_back();

    auto starts = interpolate_line(front_start, back_start, wave_count);
    auto ends = interpolate_line(front_end, back_end, wave_count);
    for (int i = int(starts.size()) - 1; i >= 0 ; --i) {
        if (!fill_colors.empty()) {
            draw_wave_fill(renderer, waveforms[i * delay], starts[i], ends[i], amplitude, fill_colors[i % fill_colors.size()]);
        }
        if (!line_colors.empty()) {
            draw_wave(renderer, waveforms[i * delay], starts[i], ends[i], amplitude, line_colors[i % line_colors.size()]);
        }
    }
}
