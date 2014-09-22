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
#ifndef VECTOR4_H
#define VECTOR4_H

#include "misc.h"

template<typename T>
class Vector4 : public tvml::Printable<Vector4<T>, 4>
{
  typedef Vector4<T> Vec4T;
public:
  Vector4(){}
  Vector4(const T& x,const T& y,const T& z,const T& w)
    :x(x),y(y),z(z),w(w){}

  template<class X>
  Vector4(const Vector4<X>& vec)
    :x(vec.x),y(vec.y),z(vec.z),w(vec.w){}

  template<class X>
  Vec4T& operator = (const Vector4<X>& vec){
    x = vec.x; y = vec.y; z = vec.z; w = vec.w;
    return *this;
  }

  /// Math operators
  Vec4T operator-() const{
    return Vec4T(-x,-y,-z,-w);
  }

  template<class X>
  Vec4T operator+(const Vector4<X>& vec) const{
    return Vec4T(x+vec.x,y+vec.y,z+vec.z,w+vec.w);
  }
  template<class X>
  Vec4T operator-(const Vector4<X>& vec) const{
    return Vec4T(x-vec.x,y-vec.y,z-vec.z,w-vec.w);
  }
  Vec4T operator*(const T& t) const{
    return Vec4T(x*t,y*t,z*t,w*t);
  }
  Vec4T operator/(const T& t) const{
    return Vec4T(x/t,y/t,z/t,w/t);
  }

  /// DOT PRODUCT
  template<class X>
  T operator*(const Vector4<X>& vec) const{
    return (x*vec.x+y*vec.y+z*vec.z + w*vec.w);
  }

  /// COMPOUND
  template<class X>
  Vec4T& operator+=(const Vector4<X>& vec){
    x+=vec.x; y+=vec.y; z+=vec.z; w+=vec.w;
    return *this;
  }
  template<class X>
  Vec4T& operator-=(const Vector4<X>& vec){
    x-=vec.x; y-=vec.y; z-=vec.z; w-=vec.w;
    return *this;
  }
  template<class X>
  Vec4T& operator*=(const Vector4<X>& vec){
    x*=vec.x; y*=vec.y; z*=vec.z; w*=vec.w;
    return *this;
  }
  template<class X>
  Vec4T& operator/=(const Vector4<X>& vec){
    x/=vec.x; y/=vec.y; z/=vec.z; w/=vec.w;
    return *this;
  }
  /// Normal
  Vec4T normal() const{
    return (*this)/(magnitude());
  }
  // normalize in place
  void normalize(){
    (*this)/=magnitude();
  }

  T magnitude() const{
    return sqrt(x*x+y*y+z*z+w*w);
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
  T x,y,z,w;
};

template<typename T>
Vector4<T> normalize(const Vector4<T>& v){
  return v.normal();
}

typedef Vector4<int8_t> Vector4b;
typedef Vector4<int16_t> Vector4s;
typedef Vector4<int32_t> Vector4i;
typedef Vector4<int64_t> Vector4l;
typedef Vector4<float> Vector4f;
typedef Vector4<double> Vector4d;
#endif // VECTOR4_H
