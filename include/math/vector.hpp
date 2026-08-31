#pragma once



class Vec3{
    public:
    double e[3];

    Vec3() : e{0,0,0}{}
    Vec3(double e0,double e1,double e2):e{e0,e1,e2} {}

    double x() const {return e[0];}
    double y() const {return e[1];}
    double z() const {return e[2];}

    Vec3 operator-() const{return Vec3(-e[0],-e[1],-e[2]);}
    double operator[](int i) const{return e[i];}
    double& operator[](int i){return e[i];}

    //VECTOR arithmetic

    //vector Addition
    Vec3& operator+=(const Vec3& v){
        e[0] += v.e[0];
        e[1] += v.e[1];
        e[2]+= v.e[2];
        return *this;
    }

    //vector-scalar multiplication
    Vec3& operator*=(double t){
        e[0]*=t;
        e[1]*=t;
        e[2]*=t;
        return *this;
    }

    //vector-scalar division
    Vec3& operator/=(double t){
        return *this *= 1/t;
    }

    //VECTOR INFORMATION

    //magnitude of the vector
    double length() const{
        return std::sqrt(length_squared());
    }

    double length_squared() const {
        return e[0]*e[0] + e[1]*e[1] + e[2]*e[2];
    }
    bool near_zero() const{
        //returns true if the vector is close to zero in all dimensions
        auto s= 1e-8;
        return (std::fabs(e[0]) < s) && (std::fabs(e[1]) < s) && (std::fabs(e[2]) < s);

    }

    static Vec3 random(){
        return Vec3(random_double(),random_double(),random_double());
    }

    static Vec3 random(double min,double max){
        return Vec3(random_double(min,max),random_double(min,max),random_double(min,max));
    }

};

using point3 = Vec3;
using vec3 = Vec3;

//vector utility functions
inline std::ostream& operator << (std::ostream& out,const Vec3& v){
    return out << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2];
}

//vector to vector addition
inline Vec3 operator+(const Vec3& u, const Vec3& v){
    return Vec3(u.e[0]+v.e[0],u.e[1]+v.e[1],u.e[2]+v.e[2]);
}

//vector to vector subtraction
inline Vec3 operator-(const Vec3& u, const Vec3& v){
    return Vec3(u.e[0]-v.e[0],u.e[1]-v.e[1],u.e[2]-v.e[2]);
}

//vector to vector multiplication
inline Vec3 operator*(const Vec3&u,const Vec3&v){
    return Vec3(u.e[0]*v.e[0],u.e[1]*v.e[1],u.e[2]*v.e[2]);
}

//scalar to const multiplication
inline Vec3 operator*(double t,const Vec3& v){
    return Vec3(t*v.e[0],t*v.e[1],t*v.e[2]);
}

// vector to const multiplication
inline Vec3 operator*(const Vec3& v, double t) {
    return t * v;
}
 inline Vec3 operator/(const Vec3& v, double t){
    return (1/t)*v;
 }

//vector dot product
inline double dot(const Vec3& u,const Vec3& v){
    return u.e[0]*v.e[0] + u.e[1]*v.e[1] + u.e[2]*v.e[2];
}

//vector cross product
inline Vec3 cross(const Vec3& u,const Vec3& v){
    return Vec3(
        u.e[1]*v.e[2]- u.e[2]*v.e[1],
        u.e[2]*v.e[0] - u.e[0]*v.e[2],
        u.e[0]*v.e[1]-u.e[1]*v.e[0]
    );
}

//VECTOR UNIT LENGTH
inline Vec3 unit_vector(const Vec3& v){
    return v/v.length();
}

inline Vec3 random_unit_vector(){
    while(true){
        auto p = Vec3::random(-1,1);
        auto lensq = p.length_squared();
        if(1e-160 < lensq && lensq <=1){
            return p /sqrt(lensq);
        }
    }
}

//determine if the vector lies within the correct hemisphere
inline Vec3 random_on_hemisphere(const Vec3& normal){
    Vec3 on_unit_sphere = random_unit_vector();
    if(dot(on_unit_sphere,normal)>0.0) {
        return on_unit_sphere;
    }else{
        return -on_unit_sphere;
    }
        
}

inline Vec3 reflect(const Vec3& v,const Vec3& n){
    return v-2*dot(v,n)*n;
}

inline vec3 refract(const vec3& uv, const vec3& n, double etai_over_etat) {
    auto cos_theta = std::fmin(dot(-uv, n), 1.0);
    vec3 r_out_perp =  etai_over_etat * (uv + cos_theta*n);
    vec3 r_out_parallel = -std::sqrt(std::fabs(1.0 - r_out_perp.length_squared())) * n;
    return r_out_perp + r_out_parallel;
}
