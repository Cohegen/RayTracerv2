#pragma once

#include "vector.hpp"
#include <iostream>

using color = Vec3;

void write_color(std::ostream& out,const color& pixel_color){
    auto r = pixel_color.x();
    auto g = pixel_color.y();
    auto b = pixel_color.z();

    //Translatng the [0,1] component values to the range [0,255]
    int rbyte = int(255.999*r);
    int gbyte = int(255.999*g);
    int bbyte = int(255.999*b);

    //writing out the pixel color components
    out << rbyte << ' ' << gbyte << ' ' << bbyte << '\n';
}