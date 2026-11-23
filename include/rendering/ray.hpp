#pragma once

#include "../math/vector.hpp"

class ray{
    public:
    ray(){}
    ray(const point3& origin,const Vec3& direction,double time): orig(origin),dir(direction),tm(time){}
    ray(const point3& origin,const Vec3& direction):ray(origin,direction,0){}

    const point3& origin() const {return orig;}
    const Vec3& direction() const{return dir;}
    double time()const {return tm;}
    point3 at(double t) const {return orig + t*dir;}


    private:
      point3 orig;
      Vec3 dir;
      double tm;
};
