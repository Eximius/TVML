/*
  Copyright (c) 2014, Vytautas Mickus (www.github.com/Eximius)
  All rights reserved.

  Redistribution and use in source and binary forms, with or without
  modification, are permitted provided that the following conditions are met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
  ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
  WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  DISCLAIMED. IN NO EVENT SHALL Vytautas Mickus BE LIABLE FOR ANY
  DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
  (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
  ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
  SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/
#ifndef VECTOR3_H
#define VECTOR3_H

#include <cmath>
#include <cassert>

#include "misc.h"

template <class T>
class Vector3 : public tvml::Printable<Vector3<T>, 3>
{
  typedef Vector3<T> Vec3T;
public:
  Vector3(){}

  Vector3(int zero)
  {
    assert(zero == 0);
    x = 0; y = 0; z = 0;
  }

  Vector3(const T& x,const T& y,const T& z):x(x),y(y),z(z){}

  template<class X>
  Vector3(const Vector3<X>& vec):x(vec.x),y(vec.y),z(vec.z){}

  /// Math operators
  Vec3T operator-() const{
    return Vec3T(-x,-y,-z);
  }

  template<class X>
  Vec3T operator+(const Vector3<X>& vec) const{
    return Vec3T(x+vec.x,y+vec.y,z+vec.z);
  }
  template<class X>
  Vec3T operator-(const Vector3<X>& vec) const{
    return Vec3T(x-vec.x,y-vec.y,z-vec.z);
  }
  template<class X>
  Vec3T operator*(const X& t) const{
    return Vec3T(x*t,y*t,z*t);
  }
  template<class X>
  Vec3T operator/(const X& t) const{
    return Vec3T(x/t,y/t,z/t);
  }

  /// DOT PRODUCT
  template<class X>
  T operator*(const Vector3<X>& vec) const{
    return (x*vec.x+y*vec.y+z*vec.z);
  }

  /// COMPOUND
  template<class X>
  Vec3T& operator+=(const X& t){
    x +=t;  y+=t; z+=t;
    return *this;
  }

  template<class X>
  Vec3T& operator-=(const X& t){
    x -=t;  y-=t; z+=t;
    return *this;
  }

  template<class X>
  Vec3T& operator*=(const X& t){
    x *=t;  y*=t; z+=t;
    return *this;
  }

  template<class X>
  Vec3T& operator/=(const X& t){
    x /=t;  y/=t; z+=t;
    return *this;
  }

  /// CROSS
  template<class X>
  Vec3T cross(const Vector3<X> vec) const{
    return Vec3T(y*vec.z - z*vec.y,
                 z*vec.x - x*vec.z,
                 x*vec.y - y*vec.x);
  }

  /// Normal
  Vec3T normal() const{
    return (*this)/(magnitude());
  }
  // normalize in place
  void normalize(){
    (*this)/=magnitude();
  }

  T magnitude() const{
    return sqrt(x*x+y*y+z*z);
  }

  /// Accessor functions
  T& operator [] (uint32_t i){
    return data()[i];
  }
  const T& operator [] (uint32_t i) const{
    return data()[i];
  }
  T* data(){
    return (&x);
  }
  const T* data() const{
    return (&x);
  }

  /// data
  T x,y,z;
};

template<typename T>
Vector3<T> normalize(const Vector3<T>& v){
  return v.normal();
}

typedef Vector3<int8_t> Vector3b;
typedef Vector3<int16_t> Vector3s;
typedef Vector3<int32_t> Vector3di;
typedef Vector3<int64_t> Vector3l;
typedef Vector3<float> Vector3f;
typedef Vector3<double> Vector3d;
#endif // VECTOR3_H
