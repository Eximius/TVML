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
#ifndef VECTOR2_H
#define VECTOR2_H

#include <cmath>
#include "misc.h"

template<class T>
class Vector2 : public tvml::Printable<Vector2<T>, 2>
{
  typedef Vector2<T> Vec2T;
public:
  Vector2(){}

  Vector2(const T& x,const T& y):x(x),y(y){}

  template<class X>
  Vector2(const Vector2<X>& vec):x(vec.x),y(vec.y){}

  /// Math operators
  Vec2T operator-() const{
    return Vec2T(-x,-y);
  }

  template<class X>
  Vec2T operator+(const Vector2<X>& vec) const{
    return Vec2T(x+vec.x,y+vec.y);
  }
  template<class X>
  Vec2T operator-(const Vector2<X>& vec) const{
    return Vec2T(x-vec.x,y-vec.y);
  }
  template<class X>
  Vec2T operator*(const X& t) const{
    return Vec2T(x*t,y*t,z*t);
  }
  /// DOT PRODUCT
  template<class X>
  T operator*(const Vector2<X>& vec) const{
    return (x*vec.x+y*vec.y);
  }
  template<class X>
  Vec2T operator/(const X& t) const{
    return Vec2T(x/t,y/t);
  }
  /// COMPOUND
  template<class X>
  Vec2T& operator+=(const X& t){
    x +=t;  y+=t;
    return *this;
  }

  template<class X>
  Vec2T& operator-=(const X& t){
    x -=t;  y-=t;
    return *this;
  }

  template<class X>
  Vec2T& operator*=(const X& t){
    x *=t;  y*=t;
    return *this;
  }

  template<class X>
  Vec2T& operator/=(const X& t){
    x /=t;  y/=t;
    return *this;
  }

  /// Normal
  Vec2T normal() const{
    return (*this)/(magnitude());
  }
  // normalize in place
  void normalize(){
    (*this)/=magnitude();
  }

  T magnitude() const{
    return sqrt(x*x+y*y);
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
  operator const T*() const{
    return &x;
  }

  /// data
  T x,y;
};

template<typename T>
Vector2<T> normalize(const Vector2<T>& v){
  return v.normal();
}

typedef Vector2<int8_t> Vector2b;
typedef Vector2<int16_t> Vector2s;
typedef Vector2<int32_t> Vector2di;
typedef Vector2<int64_t> Vector2l;
typedef Vector2<float> Vector2f;
typedef Vector2<double> Vector2d;

#endif // VECTOR2_H
