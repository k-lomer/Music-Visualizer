#include "visual_layer_factory.h"

#include "color_palettes.h"
// Visual Layers
#include "wave_layer.h"
#include "screen_box_layer.h"
#include "polygon_layer.h"
#include "moving_wave_layer.h"
#include "amplitude_circle_layer.h"

VisualLayerFactory::VisualLayerFactory(): random_layer_type(0, MAX_VL_TYPE), random_bool(0,1), random_color_int(0, 255) {}

visual_layer_type VisualLayerFactory::get_rand_layer_type(){
    return (visual_layer_type)random_layer_type(rando);
}

bool VisualLayerFactory::get_rand_bool(){
    return (bool)random_bool(rando);
}

int VisualLayerFactory::get_rand_int(int min_val, int max_val) {
    std::uniform_int_distribution<int> random_int(min_val, max_val);
    return random_int(rando);
}

double VisualLayerFactory::get_rand_double(double min_val, double max_val) {
    std::uniform_real_distribution<> random_double(min_val, max_val);
    return random_double(rando);
}

SDL_Color VisualLayerFactory::get_rand_color() {
    return SDL_Color{ (Uint8)random_color_int(rando), (Uint8)random_color_int(rando), (Uint8)random_color_int(rando), SDL_ALPHA_OPAQUE };
}

SDL_Color VisualLayerFactory::get_rand_palette_color(Color::color_palette cp) {
    int palette_length = (int)Color::palette_lookup.at(cp).size();
    if (palette_length > 0) {
        return Color::palette_lookup.at(cp)[get_rand_int(0, palette_length - 1)];
    }
    else { // if there are no colors in the pallette, return a random color
        return get_rand_color();
    }
}

std::unique_ptr<VisualLayer> VisualLayerFactory::random_visual_layer(int window_width, int window_height, Color::color_palette palette) {
    visual_layer_type new_vl_type = get_rand_layer_type();
    
    int wave_amplitude = window_height / get_rand_int(10, 20);
    SDL_Color wave_color = get_rand_palette_color(palette);

    switch (new_vl_type) {
    case Wave:
    {
        int num_waves = get_rand_int(1, 8);
        SDL_Point wave_start{ 0, window_height / 2 };
        SDL_Point wave_end{ window_width, window_height / 2 };
        return std::make_unique<WaveLayer>(num_waves, wave_start, wave_end, wave_amplitude * 3, wave_color);
    }
    case ScreenBox:
    {
        int num_waves = get_rand_int(1, 5);
        return std::make_unique<ScreenBoxLayer>(num_waves, window_width, window_height, wave_amplitude, wave_color);
    }
    case PolygonWave:
    {
        int num_sides = get_rand_int(3, 12);
        int radius = get_rand_int(30, std::min(window_width, window_height) / 2);
        SDL_Point centre{ window_width / 2, window_height / 2 };
        double rotation_rate = get_rand_double(-0.05, 0.05);
        return std::make_unique<PolygonLayer>(num_sides, radius, centre, rotation_rate, wave_amplitude/3, wave_color);
    }
    case MovingWave:
    {
        int num_waves = get_rand_int(2, 5);
        orientation wave_orientation = get_rand_bool() ? Horizontal : Vertical;
        double wave_movement = get_rand_double(-5.0, 5.0);
        return std::make_unique<MovingWaveLayer>(num_waves, wave_orientation, wave_movement, window_width, window_height, wave_amplitude, wave_color);
    }
    case AmplitudeCircle:
    default:
    {
        SDL_Point centre{ window_width / 2, window_height / 2 };
        return std::make_unique<AmplitudeCircleLayer>(centre, wave_amplitude * 5, wave_color);
    }
    }
}
