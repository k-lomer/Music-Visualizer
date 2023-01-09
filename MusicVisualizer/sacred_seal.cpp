#include "sacred_seal.h"

#include "polygon_layer.h"

SacredSealLayer::SacredSealLayer(const std::vector<SacredSealConfig> & config, SDL_Point centre, int radius, int wave_amplitude) {
    for (const auto & config : config) {
        add_layer(std::make_unique<PolygonLayer>(config.num_sides, radius, centre, config.rotation_rate, wave_amplitude, config.color));
        // Scale radius and amplitude accordingly.
        int next_radius = compute_next_radius(radius, config.num_sides);
        wave_amplitude = wave_amplitude * next_radius / radius;
        radius = next_radius;
    }
}

int SacredSealLayer::compute_next_radius(int previous_radius, int previous_sides) const{
    double theta = 2.0 * M_PI / double(previous_sides * 2);
    return int(cos(theta) * double(previous_radius));
}
