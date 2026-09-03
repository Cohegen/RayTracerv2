#pragma once

#include "../geometry/hittable_list.hpp"

class camera{
    public:
      double aspect_ratio = 1.0; //ratio between image width and height
      int image_width = 100; //rendered image width in pixel count
      int samples_per_pixel = 10;
      int max_depth =10; // maximum number of bounces into the scene

      double vfov = 90; //vertical view angle(field of view)
      point3 lookfrom = point3(0,0,0); //point camera is looking from
      point3 lookat = point3(0,0,-1); //point camera is looking at
      Vec3 vup = Vec3(0,1,0); //camera-relative "up" direction

      double defocus_angle =0; //variation angles of rays through each pixel
      double focus_dist = 10; //distance from camera lookfrom point to plane
      void render(const hittable& world){
        initialize();
        
        std::cout<<"P3\n" << image_width << ' ' << image_height << "\n255\n";

        for (int j = 0; j < image_height; j++) {
            std::clog << "\rScanlines remaining: " << (image_height - j) << ' ' << std::flush;
            for (int i = 0; i < image_width; i++) {
                color pixel_color(0,0,0);
                for(int sample=0;sample < samples_per_pixel;sample++){
                  ray r = get_ray(i,j);
                  pixel_color += ray_color(r,max_depth,world);
                }
                write_color(std::cout,pixel_samples_scale* pixel_color);
            }
        }
        std::clog << "rDone.       \n";
      }

    private:
      int image_height; // rendered image height
      double pixel_samples_scale; //color scale factor for a sum of pixel samples
      point3 center; // camera center
      point3 pixel00_loc; // location of pixel 0,0 i.e pixel at the origin
      Vec3 pixel_delta_u; // offset to pixel to the right
      Vec3 pixel_delta_v; // offset to pixel below
      Vec3 u,v,w; //camera frame basis vectors
      Vec3 defocus_disk_u; //defocus disk horizontal radius
      Vec3 defocus_disk_v; //defocus disk vertical radius;

      void initialize(){
        image_height = int(image_width / aspect_ratio);
        image_height = (image_height<1)?1:image_height;

        pixel_samples_scale = 1.0 / samples_per_pixel;

        center = lookfrom;

        //determining viewport dimensions
        auto theta = degrees_to_radians(vfov);
        auto h = std::tan(theta/2);
        auto viewport_height = 2*h*focus_dist;
        auto viewport_width = viewport_height*(double(image_width)/image_height);

        //calculating the u,v,w unit bais vectors for the camera coordinate frame
        w = unit_vector(lookfrom- lookat);
        u = unit_vector(cross(vup,w));
        v = cross(w,u);

        //calculating the vector across the horizontal and down the vertical viewport edges
        Vec3 viewport_u = viewport_width*u;
        Vec3 viewport_v = viewport_height *-v;
        
        //calculating the horizontal and vertical delta vectors from pixel to pixel
        pixel_delta_u = viewport_u / image_width;
        pixel_delta_v = viewport_v / image_height;

        //calculating the location of the upper left pixe
        auto viewport_upper_left = center - (focus_dist * w) - viewport_u/2 - viewport_v/2;
        pixel00_loc = viewport_upper_left + 0.5*(pixel_delta_u+pixel_delta_v);

          // Calculating the camera defocus disk basis vectors.
          auto defocus_radius = focus_dist * std::tan(degrees_to_radians(defocus_angle / 2));
          defocus_disk_u = u * defocus_radius;
          defocus_disk_v = v * defocus_radius;
      }

      ray get_ray(int i,int j) const{
        //constructing a camera ray from origin towards directly at randomly sampled
        //point around the pixel location i,j
  
        auto offset = sample_square();
        auto pixel_sample = pixel00_loc
                            + ((i + offset.x()) * pixel_delta_u)
                            + ((j + offset.y()) * pixel_delta_v);
  
        auto ray_origin = (defocus_angle <= 0) ? center : defocus_disk_sample();
        auto ray_direction = pixel_sample - ray_origin;
  
        return ray(ray_origin,ray_direction);
      }
  
      Vec3 sample_square() const{
        //return the vectors to a random point in the [-.5,-.5]-[+.5,+.5] unit square
      
        return Vec3(random_double()-0.5,random_double()-0.5,0);
      }

      point3 defocus_disk_sample() const{
        //returns a random point in the camera defocus disk
        auto p = random_in_unit_disk();
        return center + (p[0] * defocus_disk_u) + (p[1] * defocus_disk_v);
        
      }

      color ray_color(const ray& r,int depth,const hittable& world) {
        if(depth <=0){
          return color(0,0,0);
        }
        hit_record rec;
        if(world.hit(r,interval(0.001,infinity),rec)){
          ray scattered;
          color attenuation;
          if(rec.mat->scatter(r,rec,attenuation,scattered)){
            return attenuation*ray_color(scattered,depth-1,world);
          }
          return color(0,0,0);
            
        }
    
        Vec3 unit_direction = unit_vector(r.direction());
        auto a = 0.5*(unit_direction.y() + 1.0);
        return (1.0-a)*color(1.0, 1.0, 1.0) + a*color(0.5, 0.7, 1.0);
    }

    
};