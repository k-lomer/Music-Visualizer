#include "visual_layer_factory.h"

#include <iostream>
#include <numeric>

#include "signal_box.h"
#include "../Utilities/color_palettes.h"
#include "../Utilities/parametric.h"
// Visual Layers
#include "wave_layer.h"
#include "screen_box_layer.h"
#include "polygon_layer.h"
#include "moving_wave_layer.h"
#include "parametric_wave_layer.h"
#include "peak_tracker_layer.h"
#include "bars_layer.h"
#include "unknown_pleasure_layer.h"
#include "parametric_curve_layer.h"
// Composite Layers
#include "sacred_seal.h"
#include "polygon_spiral.h"
#include "tunnel.h"

VisualLayerFactory::VisualLayerFactory(): m_random_layer_type(MIN_VL_TYPE, MAX_VL_TYPE), m_random_bool(0,1), m_random_color_int(0, 255) {}

VisualLayerType VisualLayerFactory::get_rand_layer_type(){
    VisualLayerType new_layer = m_previous_layer;
    // Do not use the same layer twice in a row.
    while (new_layer == m_previous_layer) {
        new_layer = (VisualLayerType)m_random_layer_type(m_rando);
    }
    m_previous_layer = new_layer;
    return new_layer;
}

bool VisualLayerFactory::get_rand_bool(){
    return (bool)m_random_bool(m_rando);
}

int VisualLayerFactory::get_rand_int(int min_val, int max_val) {
    std::uniform_int_distribution<int> random_int(min_val, max_val);
    return random_int(m_rando);
}

double VisualLayerFactory::get_rand_double(double min_val, double max_val) {
    std::uniform_real_distribution<double> random_double(min_val, max_val);
    return random_double(m_rando);
}

float VisualLayerFactory::get_rand_float(float min_val, float max_val) {
    std::uniform_real_distribution<float> random_float(min_val, max_val);
    return random_float(m_rando);
}


SDL_Color VisualLayerFactory::get_rand_color() {
    return SDL_Color{ (Uint8)m_random_color_int(m_rando), (Uint8)m_random_color_int(m_rando), (Uint8)m_random_color_int(m_rando), SDL_ALPHA_OPAQUE };
}

SDL_Color VisualLayerFactory::get_rand_palette_color(color::ColorPalette cp) {
    int palette_length = (int)color::palette_lookup.at(cp).size();
    if (palette_length > 0) {
        return color::palette_lookup.at(cp)[get_rand_int(0, palette_length - 1)];
    }
    else {
        // If there are no colors in the pallette, return a random color.
        return get_rand_color();
    }
}

template <typename T> std::vector<T> VisualLayerFactory::shuffle(std::vector<T> v) {
    for (int i = int(v.size()) - 1; i >= 0; --i) {
        int swap_i = get_rand_int(0, i);
        std::swap(v[i], v[swap_i]);
    }
    return v;
}

std::unique_ptr<VisualLayer> VisualLayerFactory::random_visual_layer(int window_width, int window_height, SignalBoxConfig& cfg, color::ColorPalette palette) {
    VisualLayerType new_vl_type = get_rand_layer_type();

    switch (new_vl_type) {
    case Bars:
    {
        return random_bars(window_width, window_height, cfg, palette);
    }
    case CheckerBoard:
    {
        return random_checker_board(window_width, window_height, cfg, palette);
    }
    case ParametricCurve:
    {
        return random_parametric_curve(window_width, window_height, cfg, palette);

    }
    case ParametricWave:
    {
        return random_parametric_wave(window_width, window_height, cfg, palette);
    }
    case ScrollingLines:
    {
        return random_scrolling_lines(window_width, window_height, cfg, palette);
    }
    case CentralWave:
    {
        return random_central_wave(window_width, window_height, cfg, palette);
    }
    case PolygonSpiral:
    {
        return random_polygon_spiral(window_width, window_height, cfg, palette);
    }
    case Tunnel:
    {
        return random_tunnel(window_width, window_height, cfg, palette);
    }
    case WaveSpinner:
    {
        return random_wave_spinner(window_width, window_height, cfg, palette);
    }
    case UnknownPleasure:
    {
        return random_unknown_pleasure(window_width, window_height, cfg, palette);
    }
    case PeakTracker:
    {
        return random_peak_tracker(window_width, window_height, cfg, palette);
    }
    case SacredSeal:
    {
        return random_sacred_seal(window_width, window_height, cfg, palette);
    }
    }
}

void VisualLayerFactory::wave_signal_config(SignalBoxConfig& cfg, bool always_taper, bool include_freq ) {
    cfg.absolute = true;
    cfg.normalize = false;
    cfg.fix_base = false;
    cfg.reflect = get_rand_bool();
    cfg.taper_edges = (get_rand_bool() || always_taper ? get_rand_float(0.1f, 0.5f) : 0.0f);

    cfg.frequency_wave = get_rand_bool() && include_freq;
    if (cfg.frequency_wave) {
        cfg.time_window = get_rand_float(0.5f, 1.0f);
        cfg.decay_factor = get_rand_float(0.5f, 0.99f);
        cfg.smoothing_window = get_rand_float(0.005f, 0.02f);
    }
    else {
        bool long_time = get_rand_bool();
        if (long_time) {
            cfg.time_window = get_rand_float(0.5f, 1.0f);
            cfg.decay_factor = get_rand_float(0.94f, 0.99f);
            cfg.smoothing_window = get_rand_float(0.005f, 0.02f);
        }
        else {
            cfg.time_window = 0.0f;
            cfg.decay_factor = get_rand_float(0.94f, 0.99f);
            cfg.smoothing_window = get_rand_float(0.0f, 0.2f);
        }
    }
}

std::unique_ptr<VisualLayer> VisualLayerFactory::random_central_wave(int window_width, int window_height, SignalBoxConfig& cfg, color::ColorPalette palette) {
    wave_signal_config(cfg);

    std::unique_ptr<CompositeLayer> composite = std::make_unique<CompositeLayer>();
    int num_colors = get_rand_int(1, 3);
    int max_height = window_height;
    for (int i = 0; i < num_colors; ++i) {
        int wave_amplitude = get_rand_int(max_height / 3, max_height);
        SDL_Color wave_color = get_rand_palette_color(palette);
        int num_waves = get_rand_int(1, 10 / num_colors);
        SDL_Point wave_start{ 0, window_height / 2 };
        SDL_Point wave_end{ window_width, window_height / 2 };
        if (get_rand_bool()) {
            std::swap(wave_start, wave_end);
        }
        composite->add_layer(std::make_unique<WaveLayer>(num_waves, wave_start, wave_end, wave_amplitude, wave_color));
        max_height = wave_amplitude;
    }
    return composite;
}

std::unique_ptr<VisualLayer> VisualLayerFactory::random_tunnel(int window_width, int window_height, SignalBoxConfig& cfg, color::ColorPalette palette) {
    wave_signal_config(cfg, true);
    
    int num_waves = get_rand_int(3, 5);
    int levels = get_rand_int(2, 4);
    int wave_amplitude = std::min(window_height, window_width) / 2 / levels;
    double scale_rate = get_rand_double(-0.005, 0.005);
    SDL_Color wave_color  = get_rand_palette_color(palette);
    return std::make_unique<TunnelLayer>(window_width, window_height, num_waves, levels, wave_amplitude, wave_color, scale_rate);
}

std::unique_ptr<VisualLayer> VisualLayerFactory::random_wave_spinner(int window_width, int window_height, SignalBoxConfig& cfg, color::ColorPalette palette) {
    wave_signal_config(cfg);
    cfg.reflect = true;

    int num_spinners = get_rand_int(2, 6);
    SDL_Point wave_start{ 0, 0 };
    SDL_Point wave_end{ window_width, window_height };
    int wave_amplitude = std::min(window_height, window_width) / get_rand_int(3, 10);
    bool even_spacing = get_rand_bool();
    int wave_count = get_rand_int(2, 4);
    double rotation_rate = get_rand_double(-0.03, 0.03);
    std::unique_ptr<CompositeLayer> composite = std::make_unique<CompositeLayer>();

    if (even_spacing) {
        int num_sets = get_rand_int(1, 3);
        for (int s = 0; s < num_sets; ++s) {
            SDL_Color wave_color = get_rand_palette_color(palette);
            double offset = get_rand_double(0.0, M_PI / num_spinners);
            for (int i = 0; i < num_spinners; ++i) {
                double initial_rotation = i * M_PI / num_spinners;
                composite->add_layer(std::make_unique<WaveLayer>(wave_count, wave_start, wave_end, wave_amplitude, wave_color, initial_rotation + offset, rotation_rate));
            }
        }
    }
    else {
        for (int i = 0; i < num_spinners; ++i) {
            SDL_Color wave_color = get_rand_palette_color(palette);
            double initial_rotation = get_rand_double(0.0, 2.0 * M_PI);
            composite->add_layer(std::make_unique<WaveLayer>(wave_count, wave_start, wave_end, wave_amplitude, wave_color, initial_rotation, rotation_rate / (i + 1)));
        }
    }
    return composite;
}

std::unique_ptr<VisualLayer> VisualLayerFactory::random_unknown_pleasure(int window_width, int window_height, SignalBoxConfig& cfg, color::ColorPalette palette) {
    wave_signal_config(cfg);

    int num_waves = get_rand_int(8, 15);
    int wave_amplitude = window_height / 6;
    SDL_Point first_wave_start{ window_width / 8, 6 * window_height / 8 };
    SDL_Point first_wave_end{ 7 * window_width / 8, 6 * window_height / 8 };
    SDL_Point last_wave_start{ 2 * window_width / 8, window_height / 8 };
    SDL_Point last_wave_end{ 6 * window_width / 8, window_height / 8 };
    int frame_delay = 10;

    // Randomly pick single color or multiple colors.
    std::vector<SDL_Color> colors = get_rand_bool() ? std::vector<SDL_Color>{get_rand_palette_color(palette)} : shuffle(color::palette_lookup.at(palette));

    int layer_type = get_rand_int(1, 2);
    if (layer_type == int(UnknownPleasureLayer::UnknownPleasureFill::Black)) {
        return std::make_unique<UnknownPleasureLayer>(num_waves, frame_delay, first_wave_start, first_wave_end, last_wave_start, last_wave_end, wave_amplitude, colors, UnknownPleasureLayer::UnknownPleasureFill::Black);
    }
    else { // UnknownPleasureLayer::UnknownPleasureFill::Color
        return std::make_unique<UnknownPleasureLayer>(num_waves, frame_delay, first_wave_start, first_wave_end, last_wave_start, last_wave_end, wave_amplitude, colors, UnknownPleasureLayer::UnknownPleasureFill::Color);
    }
}

std::unique_ptr<VisualLayer> VisualLayerFactory::random_peak_tracker(int window_width, int window_height, SignalBoxConfig& cfg, color::ColorPalette palette) {
    cfg.frequency_wave = false; get_rand_bool();
    cfg.absolute = true;
    cfg.normalize = false;
    cfg.fix_base = false;
    cfg.reflect = false;
    cfg.taper_edges = 0.0;
    if (cfg.frequency_wave) {
        cfg.time_window = get_rand_float(0.5f, 1.0f);
        cfg.decay_factor = get_rand_float(0.5f, 0.99f);
        cfg.smoothing_window = get_rand_float(0.005f, 0.02f);
    }
    else {
        cfg.time_window = get_rand_float(1.0f, 2.0f);
        cfg.decay_factor = 0.8f;
        cfg.smoothing_window = get_rand_float(0.005f, 0.02f);
    }
    int peaks = 2;
    SDL_Color wave_color = get_rand_palette_color(palette);

    return std::make_unique<PeakTrackerLayer>(peaks, window_width, window_height, wave_color);
}

std::unique_ptr<VisualLayer> VisualLayerFactory::random_sacred_seal(int window_width, int window_height, SignalBoxConfig& cfg, color::ColorPalette palette) {
    wave_signal_config(cfg, true);

    int layers = get_rand_int(5, 10);
    int wave_amplitude = std::min(window_width, window_height) / layers * get_rand_int(2, 4);
    wave_amplitude *= (get_rand_bool() ? 1 : -1);
    int radius = std::min(window_width, window_height);
    std::vector<SacredSealLayer::SacredSealConfig> config;
    for (int i = 0; i < layers; ++i) {
        int num_sides = get_rand_int(3, 6);
        double rotation_rate = get_rand_double(-0.03, 0.03);
        SDL_Color wave_color = get_rand_palette_color(palette);
        config.push_back(SacredSealLayer::SacredSealConfig{ num_sides, rotation_rate, wave_color });
    }
    bool double_seals = get_rand_bool();
    if (double_seals) {
        std::unique_ptr<CompositeLayer> composite = std::make_unique<CompositeLayer>();
        SDL_Point centre_left{ window_width / 4, window_height / 2 };
        SDL_Point centre_right{ 3 * window_width / 4, window_height / 2 };

        composite->add_layer(std::make_unique<SacredSealLayer>(config, centre_left, radius, wave_amplitude));
        // Reverse rotation for other seal.
        for (auto & conf : config) {
            conf.rotation_rate *= -1.0;
        }
        composite->add_layer(std::make_unique<SacredSealLayer>(config, centre_right, radius, wave_amplitude));
        return composite;
    }
    else {
        bool quad_seals = get_rand_bool();
        if (quad_seals) {
            std::unique_ptr<CompositeLayer> composite = std::make_unique<CompositeLayer>();
            SDL_Point centre_tl{ window_width / 4, window_height / 4 };
            SDL_Point centre_tr{ 3 * window_width / 4, window_height / 4 };
            SDL_Point centre_bl{ window_width / 4, 3 * window_height / 4 };
            SDL_Point centre_br{ 3 * window_width / 4, 3 * window_height / 4 };
            composite->add_layer(std::make_unique<SacredSealLayer>(config, centre_tl, radius, wave_amplitude));
            composite->add_layer(std::make_unique<SacredSealLayer>(config, centre_br, radius, wave_amplitude));
            // Reverse rotation for other seal.
            for (auto & conf : config) {
                conf.rotation_rate *= -1.0;
            }
            composite->add_layer(std::make_unique<SacredSealLayer>(config, centre_tr, radius, wave_amplitude));
            composite->add_layer(std::make_unique<SacredSealLayer>(config, centre_bl, radius, wave_amplitude));
            return composite;
        }
        else {
            SDL_Point centre{ window_width / 2, window_height / 2 };
            return std::make_unique<SacredSealLayer>(config, centre, radius, wave_amplitude);
        }
    }
}

std::unique_ptr<VisualLayer> VisualLayerFactory::random_parametric_curve(int window_width, int window_height, SignalBoxConfig& cfg, color::ColorPalette palette) {
    cfg.frequency_wave = false;
    cfg.absolute = true;
    cfg.normalize = false;
    cfg.fix_base = false;
    cfg.reflect = false;
    cfg.taper_edges = 0.0f;
    cfg.time_window = get_rand_float(2.0, 5.0);
    cfg.decay_factor = 0.0f;
    cfg.smoothing_window = 0.0f;

    double x_coeff = get_rand_double(2.0, 3.0);
    double y_coeff = get_rand_double(2.0, 3.0);
    double coeff_baseline = get_rand_double(0.5, 1.5);
    SDL_Point centre{ window_width / 2, window_height / 2 };
    int raw_curve_division = 64;
    int curve_scale = std::min(window_height, window_width) / raw_curve_division;
    std::unique_ptr<CompositeLayer> composite = std::make_unique<CompositeLayer>();

    int scale_layers = get_rand_int(2, 4);
    double min_scale = get_rand_double(double(raw_curve_division) / 16.0, double(raw_curve_division) / 4.0);
    double max_scale = get_rand_double(min_scale * 2.0, double(raw_curve_division) / 2.0);
    std::vector<double> layer_scales;
    for (int i = 0; i < scale_layers; ++i) {
        layer_scales.push_back(min_scale + (max_scale - min_scale) * double(i) / double(scale_layers));
    }
    auto colors = shuffle(color::palette_lookup.at(palette));
    bool horizontal_direction = get_rand_bool();

    ParametricEquation2d para_curve(x_coeff, y_coeff, curve_scale);
    composite->add_layer(std::make_unique<ParametricCurveLayer>(colors, para_curve, coeff_baseline, centre, layer_scales, horizontal_direction));
    ParametricEquation2d inverted_para_curve(x_coeff, y_coeff, -curve_scale);
    composite->add_layer(std::make_unique<ParametricCurveLayer>(colors, inverted_para_curve, coeff_baseline, centre, layer_scales, horizontal_direction));
    return composite;
}

std::unique_ptr<VisualLayer> VisualLayerFactory::random_parametric_wave(int window_width, int window_height, SignalBoxConfig& cfg, color::ColorPalette palette) {
    wave_signal_config(cfg, true);

    std::unique_ptr<CompositeLayer> composite = std::make_unique<CompositeLayer>();
    auto colors = shuffle(color::palette_lookup.at(palette));
    int para_wave_layers = get_rand_int(1, 3);
    for (int i = 0; i < para_wave_layers; ++i) {
        double x_coeff_1 = get_rand_double(1.0, 5.0);
        double x_coeff_2 = get_rand_double(1.0, 5.0);
        double y_coeff_1 = get_rand_double(1.0, 3.0);
        double y_coeff_2 = get_rand_double(1.0, 3.0);
        int curve_scale_1 = get_rand_int(std::min(window_height, window_width) / 5, std::min(window_height, window_width) / 2);
        int curve_scale_2 = get_rand_int(std::min(window_height, window_width) / 5, std::min(window_height, window_width) / 2);
        ParametricEquation2d para_curve_1(x_coeff_1, y_coeff_1, curve_scale_1);
        ParametricEquation2d para_curve_2(x_coeff_2, y_coeff_2, curve_scale_2);

        SDL_Point centre_1{ get_rand_int(window_width / 3, 2 * window_width / 3), get_rand_int(window_height / 3, 2 * window_height / 3) };
        SDL_Point centre_2{ get_rand_int(window_width / 3, 2 * window_width / 3), get_rand_int(window_height / 3, 2 * window_height / 3) };
        int num_waves = get_rand_int(40 / (para_wave_layers + 1), 120 / (para_wave_layers + 1));
        double step = get_rand_double(M_PI / 80, M_PI / 50);
        double span = step * num_waves;
        double step_size = M_PI / get_rand_double(4.0, 8.0) / 60.0;
        int amplitude = std::min(window_height, window_width) / get_rand_int(10, 18);

        composite->add_layer(std::make_unique<ParametricWaveLayer>(num_waves, span, colors[i % colors.size()], para_curve_1, para_curve_2, centre_1, centre_2, step_size, amplitude));
    }
    return composite;
}

std::unique_ptr<VisualLayer> VisualLayerFactory::random_bars(int window_width, int window_height, SignalBoxConfig& cfg, color::ColorPalette palette)
{
    wave_signal_config(cfg);

    int num_bars = get_rand_int(20, 80);
    int amplitude = window_height / 2;
    int gap_width = 0;
    if (get_rand_int(1, 5) > 1)
    {
        if (get_rand_bool())
        {
            // Small gap.
            gap_width = get_rand_int(1, 10);
        }
        else
        {
            // Big gap.
            int max_gap_width = window_width / num_bars;
            gap_width = get_rand_int(1, max_gap_width);
        }
    }
    else
    {
        // No gap.
    }

    std::unique_ptr<CompositeLayer> composite = std::make_unique<CompositeLayer>();

    int num_layers = get_rand_int(1, 3);
    double reduction_factor = get_rand_double(0.4, 0.8);
    if (get_rand_bool())
    {
        // Central.
        SDL_Point bars_start{ 0, window_height / 2 };
        SDL_Point bars_end{ window_width, window_height / 2 };
        for (int i = 0; i < num_layers; ++i)
        {
            auto wave_color = get_rand_palette_color(palette);
            composite->add_layer(std::make_unique<BarsLayer>(num_bars, bars_start, bars_end, amplitude, wave_color, gap_width));
            composite->add_layer(std::make_unique<BarsLayer>(num_bars, bars_start, bars_end, -amplitude, wave_color, gap_width));
            amplitude = int(double(amplitude) * reduction_factor);
        }
    }
    else
    {
        // Top and bottom.
        SDL_Point bars_top_start{ 0, 0 };
        SDL_Point bars_top_end{ window_width, 0 };
        SDL_Point bars_bottom_start{ 0, window_height };
        SDL_Point bars_bottom_end{ window_width, window_height };
        for (int i = 0; i < num_layers; ++i)
        {
            auto wave_color = get_rand_palette_color(palette);
            composite->add_layer(std::make_unique<BarsLayer>(num_bars, bars_top_start, bars_top_end, -amplitude, wave_color, gap_width));
            composite->add_layer(std::make_unique<BarsLayer>(num_bars, bars_bottom_start, bars_bottom_end, amplitude, wave_color, gap_width));
            amplitude = int(double(amplitude) * reduction_factor);
        }
    }
    return composite;
}

std::unique_ptr<VisualLayer> VisualLayerFactory::random_checker_board(int window_width, int window_height, SignalBoxConfig& cfg, color::ColorPalette palette)
{
    wave_signal_config(cfg, false, false);
    
    cfg.absolute = get_rand_bool();
    cfg.smoothing_window = get_rand_float(0.005f, 0.01f);

    int amplitude = std::min(window_height, window_width) / get_rand_int(5, 12);

    int num_line_sets = get_rand_int(3, 6);
    std::unique_ptr<CompositeLayer> composite = std::make_unique<CompositeLayer>();

    for (int i = 0; i < num_line_sets; ++i) {
        int num_waves = get_rand_int(2, 5);
        Orientation wave_orientation = i % 2 ? Horizontal : Vertical;
        double wave_movement = get_rand_double(-3.0, 3.0);
        auto wave_color = get_rand_palette_color(palette);
        composite->add_layer(
            std::make_unique<MovingWaveLayer>(num_waves, wave_orientation, wave_movement, window_width, window_height, amplitude, wave_color));
    }
    return composite;
}

std::unique_ptr<VisualLayer> VisualLayerFactory::random_scrolling_lines(int window_width, int window_height, SignalBoxConfig& cfg, color::ColorPalette palette)
{
    wave_signal_config(cfg, false, false);

    int num_line_sets = get_rand_int(2, 6);
    Orientation wave_orientation = get_rand_bool() ? Horizontal : Vertical;
    std::unique_ptr<CompositeLayer> composite = std::make_unique<CompositeLayer>();

    for (int i = 0; i < num_line_sets; ++i) {
        int num_waves = get_rand_int(2, 8);
        double wave_movement = get_rand_double(-4.0, 4.0);
        auto wave_color = get_rand_palette_color(palette);
        int wave_amplitude = std::min(window_height, window_width) / get_rand_int(5, 12);
        composite->add_layer(
            std::make_unique<MovingWaveLayer>(num_waves, wave_orientation, wave_movement, window_width, window_height, wave_amplitude, wave_color));
    }

    return composite;
}

std::unique_ptr<VisualLayer> VisualLayerFactory::random_polygon_spiral(int window_width, int window_height, SignalBoxConfig& cfg, color::ColorPalette palette)
{
    wave_signal_config(cfg, false, false);

    int num_sides = get_rand_int(3, 6);
    double position = get_rand_double(0.3, 0.7);
    double scale_rate = get_rand_double(0.975, 1.025);
    int wave_amplitude = std::min(window_height, window_width) / get_rand_int(4, 6);
    auto wave_color = get_rand_palette_color(palette);
    double rotation_rate = get_rand_double(-0.02, 0.02);
    return std::make_unique<PolygonSpiralLayer>(num_sides, window_width, window_height, position, rotation_rate, scale_rate, wave_amplitude, wave_color);
}