#pragma once

#include "composite_layer.h"

// A sacred geometric combination of concentric rotating regular polygons.
class SacredSealLayer : public virtual CompositeLayer {
public:
    // The config for each polygon in the seal.
    // Other parameters will be the same or calculated on creation.
    typedef struct SacredSealConfig {
        // The number of sides of the polygon.
        int num_sides;
        // The rotation rate for the polygon.
        double rotation_rate;
        // The color of the polygon.
        SDL_Color color;
    } SacredSealConfig;

    // SacredSealLayer constructor.
    // param: config                    - a vector of the configuration for each polygon in the seal (outwards to inwards)
    // param: centre                  - the coordinates of the centre of the seal
    // param: radius                    - the radius of the outermost polygon in the seal
    // param: wave_amplitude - the amplitude of the outermost polygon in the seal
    SacredSealLayer(const std::vector<SacredSealConfig> & config, SDL_Point centre, int radius, int wave_amplitude);

private:
    // Compute the radius of the next polygon such that its vertex reaches the midpoint of the outer polygon.
    // param: previous_radius           - the radius of the outer polygon
    // param: previous_sides            - the number of sides of the outer polygon
    // return: int                      - the radius of the inner polygon
    int compute_next_radius(int previous_radius, int previous_sides) const;
};
