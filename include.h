#ifndef INCLUDE_H
#define INCLUDE_H

#include <cmath>
#include <cstdlib>
#include <limits>
#include <memory>

// usings
using std::shared_ptr;
using std::make_shared;
using std::sqrt;

// constants
const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

// utility function(s)
inline double degrees_to_radians(double degrees) {
    return degrees * pi / 180.;
}

inline double random_double() {
    // returns random real number in [0, 1)
    return rand() / (RAND_MAX + 1.0);
}

inline double random_double(double min, double max) {
    // returns random real number in [min, max)
    return min + (max - min) * random_double();
}

// common headers
#include "ray.h"
#include "vec3.h"
#include "interval.h"

#endif