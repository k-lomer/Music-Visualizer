#pragma once
#include "visual_layer.h"

#include <memory>
#include <random>

#include "../Utilities/color_palettes.h"

struct SignalBoxConfig;

enum visual_layer_type {
    Bars,
    CheckerBoard,
    ParametricCurve,
    ParametricWave,
    ScrollingLines,
    CentralWave,
    PolygonSpiral,
    Tunnel,
    WaveSpinner,
    UnknownPleasure,
    PeakTracker,
    SacredSeal,
    MIN_VL_TYPE = Bars,
    MAX_VL_TYPE = SacredSeal
};

// Class for creating visual layers for the visualizer
class VisualLayerFactory {
public:
    VisualLayerFactory();

    // Create a VisualLayer with random parameters
    // param: window_width - the pixel width of the window
    // param: window_height - the pixel height of the window
    // param: cfg - the configuration for the signal box, set by this function
    // param: palette - the color palette to use for the layer
    // return: std::unique_ptr<VisualLayer> - a unique_ptr to the new VisualLayer
    std::unique_ptr<VisualLayer> random_visual_layer(int window_width, int window_height, SignalBoxConfig& cfg, Color::color_palette palette = Color::Random);

private:
    std::random_device rando;
    std::uniform_int_distribution<int> random_layer_type;
    std::uniform_int_distribution<int> random_bool;
    std::uniform_int_distribution<int> random_color_int;

    // functions for generating random values
    visual_layer_type get_rand_layer_type();
    bool get_rand_bool();
    int get_rand_int(int min_val, int max_val); // inclusive
    double get_rand_double(double min_val, double max_val); // inclusive
    SDL_Color get_rand_color();
    SDL_Color get_rand_palette_color(Color::color_palette cp);
    template <typename T> std::vector<T> shuffle(std::vector<T> v);

    // functions for generating config
    void randomise_signal_config(SignalBoxConfig& cfg);
    void wave_signal_config(SignalBoxConfig& cfg, bool always_taper = false, bool include_frequency = true );

    // functions for generating random layers
    std::unique_ptr<VisualLayer> random_central_wave(int window_width, int window_height, SignalBoxConfig& cfg, Color::color_palette palette);
    std::unique_ptr<VisualLayer> random_tunnel(int window_width, int window_height, SignalBoxConfig& cfg, Color::color_palette palette);
    std::unique_ptr<VisualLayer> random_wave_spinner(int window_width, int window_height, SignalBoxConfig& cfg, Color::color_palette palette);
    std::unique_ptr<VisualLayer> random_unknown_pleasure(int window_width, int window_height, SignalBoxConfig& cfg, Color::color_palette palette);
    std::unique_ptr<VisualLayer> random_peak_tracker(int window_width, int window_height, SignalBoxConfig& cfg, Color::color_palette palette);
    std::unique_ptr<VisualLayer> random_sacred_seal(int window_width, int window_height, SignalBoxConfig& cfg, Color::color_palette palette);
    std::unique_ptr<VisualLayer> random_parametric_curve(int window_width, int window_height, SignalBoxConfig& cfg, Color::color_palette palette);
    std::unique_ptr<VisualLayer> random_parametric_wave(int window_width, int window_height, SignalBoxConfig& cfg, Color::color_palette palette);
    std::unique_ptr<VisualLayer> random_checker_board(int window_width, int window_height, SignalBoxConfig& cfg, Color::color_palette palette);
    std::unique_ptr<VisualLayer> random_scrolling_lines(int window_width, int window_height, SignalBoxConfig& cfg, Color::color_palette palette);
    std::unique_ptr<VisualLayer> random_polygon_spiral(int window_width, int window_height, SignalBoxConfig& cfg, Color::color_palette palette);
};
