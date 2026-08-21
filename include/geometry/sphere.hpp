#pragma once

#include "hittable.hpp"
#include "math/vector.hpp"

class sphere:public hittable{
    public:
      sphere(const point3& center,double radius):center(center),radius(std::fmax(0,radius)){}

      bool hit(const ray& r, double ray_tmin, double ray_tmax, hit_record& rec) const override{
        Vec3 oc = center - r.origin();
        auto a = r.direction().length_squared();
        auto h = dot(r.direction(),oc);
        auto c = oc.length_squared() - radius*radius;

        auto discriminant = h*h - a*c;
        if(discriminant < 0){
            return false;
        }

        auto sqrtd = std::sqrt(discriminant);

        //finding if the nearest root lies in the range
        auto root = (h-sqrtd) /a;
        if(root <= ray_tmin || ray_tmax <= root){
            root = (h+sqrtd) / a;
            if(root <= ray_tmin || ray_tmax <= root){
                return false;
            }
        }
        rec.t = root;
        rec.p = r.at(rec.t);
        rec.normal = (rec.p-center) /radius;
        Vec3 outward_normal = (rec.p - center) /radius;
        rec.set_face_normal(r,outward_normal);

        return true;
      }
    private:
      //sphere center
      point3 center;

      //sphere's radius
      double radius;
};
