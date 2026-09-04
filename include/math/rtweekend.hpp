#pragma once

#include <cmath>
#include <iostream>
#include <limits>
#include <memory>
#include <cstdlib>
#include <random>

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

inline double random_double(){
   thread_local std::uniform_real_distribution<double> distribution(0.0, 1.0);
   thread_local std::mt19937 generator(std::random_device{}());
   return distribution(generator);
}

inline double random_double(double min,double max){
    //returns a random real in [min,max]
    return min + (max-min)*random_double();
}

// Common Headers

#include "color.hpp"
#include "../rendering/ray.hpp"
#include "vector.hpp"
#include "interval.hpp"