#pragma once

#include <map>
#include <vector>

#include "colors.h"
#include "SDL.h"

namespace color {

// Enum for a color palette.
enum ColorPalette {
    Rainbow = 0,
    RGBRainbow,
    Ice,
    Forrest,
    Vaporwave,
    Outrun,
    Bathroom,
    Desert,
    Neon,
    Pastel,
    Cafe,
    Mars,
    Matrix,
    Fuschia,
    MAX_CP = Fuschia
};

// Define the color palettes.
const std::map < ColorPalette, std::vector<SDL_Color>> palette_lookup {
    {Rainbow, {red, orange, yellow, green, blue, indigo, violet}},
    {RGBRainbow, {red, yellow, lime, cyan, blue, magenta}},
    {Ice, {white, light_cyan, pale_turquoise, aqua, corn_flower_blue, dodger_blue}},
    {Forrest, {olive_drab, lawn_green, forest_green, lime_green, saddle_brown, burly_wood}},
    {Vaporwave, {magenta, deep_sky_blue, aqua_marine, dark_violet, light_sky_blue}},
    {Outrun, {midnight_blue, blue_violet, magenta, orange_red, dark_orange}},
    {Bathroom, {white, yellow_green, salmon, sea_shell}},
    {Desert, {pale_golden_rod, khaki, moccasin, tan, indian_red, medium_sea_green}},
    {Neon, {magenta, lime, yellow, deep_pink}},
    {Pastel, {pale_violet_red, azure, honeydew, pale_green, light_coral}},
    {Cafe, {dark_golden_rod, sienna, chocolate, peru, misty_rose, ghost_white}},
    {Mars, {silver, light_steel_blue, maroon, crimson, indian_red, rosy_brown}},
    {Matrix, {dark_green, lime_green, lime}},
    {Fuschia, {magenta, deep_pink, white, medium_spring_green}}
};
} // End namespace color.
