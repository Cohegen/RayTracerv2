#pragma once

#include <cmath>
#include <iostream>
#include <limits>
#include <memory>

//C++ std strings
using std::make_shared;
using std::shared_ptr;

//constants
const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385 ;

// Utility Functions

inline double degrees_to_radians(double degrees) {
    return degrees * pi / 180.0;
}

// Common Headers

#include "math/color.hpp"
#include "math/vector.hpp"
#include "rendering/ray.hpp"
