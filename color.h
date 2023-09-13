#ifndef COLOR_H
#define COLOR_H

#include <iostream>
#include "vec3.h"

using Color = Vec3;

void write_color(std::ostream& out, Color pixel_color) {
    // translate vector components into [0, 255] color values
    out << static_cast<int>(255.999 * pixel_color.x()) << ' '
        << static_cast<int>(255.999 * pixel_color.y()) << ' '
        << static_cast<int>(255.999 * pixel_color.z()) << '\n';
}

#endif