#pragma once
#include "visual_layer.h"

#include <memory>
#include <random>

#include "../Utilities/color_palettes.h"

struct SignalBoxConfig;

// Enum representing the different layer types.
enum VisualLayerType {
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
    SacredSeal,
    MIN_VL_TYPE = Bars,
    MAX_VL_TYPE = SacredSeal,
    PeakTracker // For debugging only.
};

// Class for creating visual layers for the visualizer.
class VisualLayerFactory {
public:
    // VisualLayerFactory constructor.
    VisualLayerFactory();

    // Create a VisualLayer with random parameters
    // param: window_width                      - the pixel width of the window
    // param: window_height                     - the pixel height of the window
    // param: cfg                               - the configuration for the signal box, set by this function
    // param: palette                           - the color palette to use for the layer
    // return: std::unique_ptr<VisualLayer>     - a unique_ptr to the new VisualLayer
    std::unique_ptr<VisualLayer> random_visual_layer(int window_width, int window_height, SignalBoxConfig& cfg, color::ColorPalette palette);

private:
    // The random number generator.
    std::random_device m_rando;
    // The distribution for generating random layers.
    std::uniform_int_distribution<int> m_random_layer_type;
    // The distribution for generating random booleans.
    std::uniform_int_distribution<int> m_random_bool;
    // The distribution for generating random colours.
    std::uniform_int_distribution<int> m_random_color_int;
    // The previously used layer type.
    VisualLayerType m_previous_layer;

    // Functions for generating random values.
    VisualLayerType get_rand_layer_type();
    bool get_rand_bool();
    int get_rand_int(int min_val, int max_val); // inclusive
    double get_rand_double(double min_val, double max_val); // inclusive
    float get_rand_float(float min_val, float max_val); // inclusive
    SDL_Color get_rand_color();
    SDL_Color get_rand_palette_color(color::ColorPalette cp);
    template <typename T> std::vector<T> shuffle(std::vector<T> v);

    // Generate a random signal box config for waves.
    void wave_signal_config(SignalBoxConfig& cfg, bool always_taper = false, bool include_frequency = true);

    // Functions for generating random layers.
    // param: window_width                      - the width of the application window
    // param: window_height                     - the height of the application window
    // param: cfg                               - the signal box config, to be set by this function
    // param: palette                           - the color palette to use
    std::unique_ptr<VisualLayer> random_central_wave(int window_width, int window_height, SignalBoxConfig& cfg, color::ColorPalette palette);
    std::unique_ptr<VisualLayer> random_tunnel(int window_width, int window_height, SignalBoxConfig& cfg, color::ColorPalette palette);
    std::unique_ptr<VisualLayer> random_wave_spinner(int window_width, int window_height, SignalBoxConfig& cfg, color::ColorPalette palette);
    std::unique_ptr<VisualLayer> random_unknown_pleasure(int window_width, int window_height, SignalBoxConfig& cfg, color::ColorPalette palette);
    std::unique_ptr<VisualLayer> random_peak_tracker(int window_width, int window_height, SignalBoxConfig& cfg, color::ColorPalette palette);
    std::unique_ptr<VisualLayer> random_sacred_seal(int window_width, int window_height, SignalBoxConfig& cfg, color::ColorPalette palette);
    std::unique_ptr<VisualLayer> random_parametric_curve(int window_width, int window_height, SignalBoxConfig& cfg, color::ColorPalette palette);
    std::unique_ptr<VisualLayer> random_parametric_wave(int window_width, int window_height, SignalBoxConfig& cfg, color::ColorPalette palette);
    std::unique_ptr<VisualLayer> random_checker_board(int window_width, int window_height, SignalBoxConfig& cfg, color::ColorPalette palette);
    std::unique_ptr<VisualLayer> random_bars(int window_width, int window_height, SignalBoxConfig& cfg, color::ColorPalette palette);
    std::unique_ptr<VisualLayer> random_scrolling_lines(int window_width, int window_height, SignalBoxConfig& cfg, color::ColorPalette palette);
    std::unique_ptr<VisualLayer> random_polygon_spiral(int window_width, int window_height, SignalBoxConfig& cfg, color::ColorPalette palette);
};
