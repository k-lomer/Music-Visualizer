#include "visual_layer_factory.h"

#include "color_palettes.h"
// Visual Layers
#include "wave_layer.h"
#include "screen_box_layer.h"
#include "polygon_layer.h"
#include "moving_wave_layer.h"
#include "amplitude_circle_layer.h"
// Composite Layers
#include "sacred_seal.h"
#include "circle_grid.h"
#include "polygon_spiral.h"
#include "tunnel.h"

VisualLayerFactory::VisualLayerFactory(): random_layer_type(MIN_VL_TYPE, MAX_VL_TYPE), random_bool(0,1), random_color_int(0, 255) {}

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
    visual_layer_type new_vl_type = WaveSpinner;//get_rand_layer_type();
    
    int wave_amplitude = window_height / get_rand_int(10, 30);
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
    {
        SDL_Point centre{ window_width / 2, window_height / 2 };
        return std::make_unique<AmplitudeCircleLayer>(centre, wave_amplitude * 5, wave_color);
    }
    case CheckerBoard:
    {
        int num_line_sets = get_rand_int(3, 5);
        std::unique_ptr<CompositeLayer> composite = std::make_unique<CompositeLayer>();

        for (int i = 0; i < num_line_sets; ++i) {
            int num_waves = get_rand_int(2, 5);
            orientation wave_orientation = i % 2 ? Horizontal : Vertical;
            double wave_movement = get_rand_double(-3.0, 3.0);
            wave_color = get_rand_palette_color(palette);
            composite->add_layer(
                std::make_unique<MovingWaveLayer>(num_waves, wave_orientation, wave_movement, window_width, window_height, wave_amplitude*2, wave_color));
        }
        return composite;
    }
    case ScrollingLines:
    {
        int num_line_sets = get_rand_int(2, 5);
        orientation wave_orientation = get_rand_bool() ? Horizontal : Vertical;
        std::unique_ptr<CompositeLayer> composite = std::make_unique<CompositeLayer>();

        // Add an optional pulsing circle
        if (wave_orientation == Horizontal) {
            if (get_rand_bool()) {
                SDL_Point centre{ window_width / 2, window_height / 2 };
                int circle_radius = std::min(window_height, window_width) / get_rand_int(2, 10);
                composite->add_layer(std::make_unique<AmplitudeCircleLayer>(centre, circle_radius, wave_color));
            }
        }

        for (int i = 0; i < num_line_sets; ++i) {
            int num_waves = get_rand_int(2, 8);
            double wave_movement = get_rand_double(-5.0, 5.0);
            wave_color = get_rand_palette_color(palette);
            wave_amplitude = window_height / get_rand_int(5, 20);
            composite->add_layer(
                std::make_unique<MovingWaveLayer>(num_waves, wave_orientation, wave_movement, window_width, window_height, wave_amplitude, wave_color));
        }

        return composite;
    }
    case BoxedCircle:
    {
        std::unique_ptr<CompositeLayer> composite = std::make_unique<CompositeLayer>();
        // circle
        SDL_Point centre{ window_width / 2, window_height / 2 };
        int num_circles = get_rand_int(1, 4);
        int circle_radius = std::min(window_height, window_width) / get_rand_int(3, 5);
        for (int i = 0; i < num_circles; ++i) {
            wave_color = get_rand_palette_color(palette);
            composite->add_layer(std::make_unique<AmplitudeCircleLayer>(centre, circle_radius / (i+1), wave_color));
        }
        // box
        int num_boxes = get_rand_int(1, 3);
        wave_amplitude = std::min(window_height, window_width) / 2 - circle_radius;
        for (int i = 0; i < num_boxes; ++i) {
            wave_color = get_rand_palette_color(palette);
            int num_waves = get_rand_int(1, 4);
            composite->add_layer(std::make_unique<ScreenBoxLayer>(num_waves, window_width, window_height, wave_amplitude, wave_color));
            wave_amplitude /= 2;
        }
        return composite;
    }
    case CentralWave:
    {
        std::unique_ptr<CompositeLayer> composite = std::make_unique<CompositeLayer>();
        int num_colors = get_rand_int(1, 3);
        for (int i = 0; i < num_colors; ++i) {
            int wave_amplitude = window_height / get_rand_int(5, 30);
            wave_color = get_rand_palette_color(palette);
            int num_waves = get_rand_int(1, 10 / num_colors);
            SDL_Point wave_start{ 0, window_height / 2 };
            SDL_Point wave_end{ window_width, window_height / 2 };
            composite->add_layer(std::make_unique<WaveLayer>(num_waves, wave_start, wave_end, wave_amplitude * 3, wave_color));
        }
        return composite;
    }
    case CircleGrid:
    {
        int cols = get_rand_int(2, 5);
        int rows = get_rand_int(1, cols);
        if (window_height > window_width) {
            std::swap(cols, rows);
        }
        int num_colors = get_rand_int(1, 3);
        std::vector<SDL_Color> colors;
        for (int i = 0; i < num_colors; ++i) {
            colors.push_back(get_rand_palette_color(palette));
        }
        return std::make_unique<CircleGridLayer>(colors, rows, cols, window_width, window_height);
    }
    case PolygonSpiral:
    {
        int num_sides = get_rand_int(3, 6);
        int iterations = get_rand_int(5, 30);
        double position = get_rand_double(0.2, 0.8);
        double rotation_rate = get_rand_double(-0.03, 0.03);
        return std::make_unique<PolygonSpiralLayer>(num_sides, window_width, window_height, iterations, position, rotation_rate, wave_amplitude, wave_color);
    }
    case Tunnel:
    {
        int num_boxes = get_rand_int(1, 3);
        int num_waves = get_rand_int(1, 4);
        int levels = get_rand_int(2, 6);
        double scale_rate = get_rand_double(-0.004, 0.004);
        return std::make_unique<TunnelLayer>(window_width, window_height, num_waves, levels, wave_amplitude, wave_color, scale_rate);
    }
    case WaveSpinner:
    {
        std::unique_ptr<CompositeLayer> composite = std::make_unique<CompositeLayer>();
        int num_spinners = get_rand_int(1, 6);
        SDL_Point wave_start{ 0, 0 };
        SDL_Point wave_end{ window_width, window_height };
        int wave_amplitude = window_height / get_rand_int(2, 10);
        bool even_spacing = get_rand_bool();
        int wave_count = get_rand_int(1, 5);

        if (even_spacing){
            double rotation_rate = get_rand_double(-0.03, 0.03);
            int num_sets = get_rand_int(1, 3);
            for (int s = 0; s < num_sets; ++s)
            {
                wave_color = get_rand_palette_color(palette);
                double offset = get_rand_double(0.0, M_PI / num_spinners);
                for (int i = 0; i < num_spinners; ++i) {
                    double initial_rotation = i * M_PI / num_spinners;
                    composite->add_layer(std::make_unique<WaveLayer>(wave_count, wave_start, wave_end, wave_amplitude, wave_color, initial_rotation + offset, rotation_rate));
                }
            }
        }
        else {
            double rotation_rate = get_rand_double(-0.03, 0.03);
            for (int i = 0; i < num_spinners; ++i) {
                wave_color = get_rand_palette_color(palette);
                double initial_rotation = get_rand_double(0.0, 2.0 * M_PI);
                composite->add_layer(std::make_unique<WaveLayer>(wave_count, wave_start, wave_end, wave_amplitude, wave_color, initial_rotation, rotation_rate / (i + 1)));
            }
        }
        return composite;
    }
    case SacredSeal:
    default:
    {
        int radius = get_rand_int(std::min(window_width, window_height) / 4, std::min(window_width, window_height) / 2);
        std::vector<SacredSealLayer::SacredSealConfig> config;
        int layers = get_rand_int(2, 5);
        for (int i = 0; i < layers; ++i) {
            int num_sides = get_rand_int(3, 8);
            double rotation_rate = get_rand_double(-0.03, 0.03);
            wave_color = get_rand_palette_color(palette);
            config.push_back(SacredSealLayer::SacredSealConfig{ num_sides, rotation_rate, wave_color });
        }
        bool double_seals = get_rand_bool();
        if (double_seals) {
            std::unique_ptr<CompositeLayer> composite = std::make_unique<CompositeLayer>();
            SDL_Point centre_left{ window_width / 4, window_height / 2 };
            SDL_Point centre_right{ 3 * window_width / 4, window_height / 2 };

            radius = get_rand_int(radius / 2, radius);
            composite->add_layer(std::make_unique<SacredSealLayer>(config, centre_left, radius, wave_amplitude));
            // reverse rotation for other seal
            for (auto & conf : config) {
                conf.rotation_rate *= -1.0;
            }
            composite->add_layer(std::make_unique<SacredSealLayer>(config, centre_right, radius, wave_amplitude));
            return composite;
        }
        else {
            SDL_Point centre{ window_width / 2, window_height / 2 };
            return std::make_unique<SacredSealLayer>(config, centre, radius, wave_amplitude);
        }
    }
    }
}
