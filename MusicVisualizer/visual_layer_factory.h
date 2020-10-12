#pragma once
#include "visual_layer.h"

#include <memory>
#include <random>

enum visual_layer_type {Wave,
                        ScreenBox,
                        PolygonWave,
                        MovingWave,
                        AmplitudeCircle,
                        MAX_VL_TYPE = AmplitudeCircle};

// Class for creating visual layers for the visualizer
class VisualLayerFactory {
public:
    VisualLayerFactory();

    // Create a VisualLayer with random parameters
    // param: window_width - the pixel width of the window
    // param: window_height - the pixel height of the window
    // return: std::unique_ptr<VisualLayer> - a unique_ptr to the new VisualLayer
    std::unique_ptr<VisualLayer> random_visual_layer(int window_width, int window_height);

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
};
