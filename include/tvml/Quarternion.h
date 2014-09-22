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
#ifndef QUARTERNION_H
#define QUARTERNION_H

#include "Vector3.h"
#include "Vector4.h"

#include "Matrix3x3.h"
#include "Matrix4x4.h"

#include <cmath>
/// A few useful functions for angles

double rad(double degrees)
{
  return degrees * M_PI / 180;
}

double deg(double radians)
{
  return radians * 180 / M_PI;
}

template<typename T>
class Quarternion
{
	typedef Quarternion<T> QuartT;
public:
	Quarternion(){}
	Quarternion(const T& w, const T& x,const T& y,const T& z)
		:w(w),x(x),y(y),z(z){}

	template<typename X>
	Quarternion(const T& angle, const Vector3<X>& axis){
		T angle2 = angle/2;
		T sin2   = sin(angle2);
		w = cos(angle2);
		x = axis.x * sin2; y = axis.y * sin2; z = axis.z * sin2;
	}


	template<class X>
	explicit Quarternion(const Vector4<X>& vec)
		:w(vec.w),x(vec.x),y(vec.y),z(vec.z){}

	template<class X>
	Quarternion(const Quarternion<X>& q)
		:w(q.w), x(q.x), y(q.y), z(q.z){}

	template<class X>
	QuartT& operator = (const Quarternion<X>& quart){
		 w = quart.w; x = quart.x; y = quart.y; z = quart.z;
		return *this;
	}

  /// Math operators
	template<class X>
	QuartT operator+(const Quarternion<X>& quart) const{
		return QuartT(w+quart.w, x+quart.x ,y+quart.y, z+quart.z);
	}
	template<class X>
	QuartT operator-(const Quarternion<X>& quart) const{
		return QuartT(w-quart.w, x-quart.x,y-quart.y,z-quart.z);
	}
	QuartT operator-() const{
		return QuartT(-w,-x,-y,-z);
	}
	QuartT operator*(const T& t) const{
		return QuartT(w*t, x*t,y*t,z*t);
	}
	QuartT operator/(const T& t) const{
		return QuartT(w/t, x/t,y/t,z/t);
	}

	template<class X>
	QuartT operator*(const Quarternion<X>& q) const{
		return QuartT(w*q.w - x*q.x - y*q.y - z*q.z,
									w*q.x + x*q.w + y*q.z - z*q.y,
									w*q.y - x*q.z + y*q.w + z*q.x,
									w*q.z + x*q.y - y*q.x + z*q.w);
	}
	template<class X>
	QuartT operator/(const Quarternion<X>& t) const{
		return QuartT(w/t, x/t,y/t,z/t);
	}
	/// COMPOUND
	template<class X>
	void operator/=(const X& t){
		w/=t; x /=t;  y/=t;  z/=t;
	}
	template<class X>
	void operator+=(const Quarternion<X>& quart){
		w+=quart.w; x+=quart.x; y+=quart.y; z+=quart.z;
	}
	template<class X>
	void operator*=(const Quarternion<X>& q){
		w = w*q.w - x*q.x - y*q.y - z*q.z;
		x = w*q.x + x*q.w + y*q.z - z*q.y;
		y = w*q.y - x*q.z + y*q.w + z*q.x;
		z = w*q.z + x*q.y - y*q.x + z*q.w;
	}

	/// Normalization
  QuartT normal() const{
		return (*this)/(magnitude());
	}
  // normalizes in place
  void normalize(){
		(*this)/=magnitude();
	}
	T magnitude() const{
		return sqrt(w*w+x*x+y*y+z*z);
	}

	/// Accessor functions
	const T& operator [] (uint32_t i) const{
		return data()[i];
	}
	T& operator [] (uint32_t i){
		return data()[i];
	}
	const T* data() const{
		return (T*)this;
	}
	T* data(){
		return (T*)this;
	}

  /// To rotation matrix
	template<typename X>
    operator Matrix3x3<X>() const {
		Matrix3x3<X> mat;

    QuartT normal = this->normal();

		T &x = normal.x,&y = normal.y,
				&z = normal.z,&w = normal.w;
		T q = magnitude();
		T q2 = 2*q;
		T qpowx2 = 2*q*q;

		mat[0] = 1 - q2*(y*y + z*z);
		mat[1] = qpowx2*(x*y - z*w);
		mat[2] = qpowx2*(x*z + y*w);

		mat[3] = qpowx2*(x*y + z*w);
		mat[4] = 1 - q2*(x*x + z*z);
		mat[5] = qpowx2*(y*z - x*w);

		mat[6] = qpowx2*(x*z - y*w);
		mat[7] = qpowx2*(y*z + x*w);
		mat[8] = 1 - q2*(x*x + y*y);

		/** paste old

				mat[0] = 1 - 2*q*(y*y + z*z);
				mat[1] = 2*q*q*(x*y - z*w);
				mat[2] = 2*q*q*(x*z + y*w);

				mat[3] = 2*q*q*(x*y + z*w);
				mat[4] = 1 - 2*q*(x*x + z*z);
				mat[5] = 2*q*q*(y*z - x*w);

				mat[6] = 2*q*q*(x*z - y*w);
				mat[7] = 2*q*q*(y*z + x*w);
				mat[8] = 1 - 2*q*(x*x + y*y);

				**/
		return mat;
	}
	template<typename X>
    operator Matrix4x4<X>() const {
		Matrix4x4<X> mat;

		QuartT normal = this->norm();

		float &x = normal.x,&y = normal.y,
						&z = normal.z,&w = normal.w;
		float q = magnitude();
		float q2 = 2*q;
		float qpowx2 = 2*q*q;

		mat[0] = 1 - q2*(y*y + z*z);
		mat[1] = qpowx2*(x*y - z*w);
		mat[2] = qpowx2*(x*z + y*w);

		mat[4] = qpowx2*(x*y + z*w);
		mat[5] = 1 - q2*(x*x + z*z);
		mat[6] = qpowx2*(y*z - x*w);

		mat[8] = qpowx2*(x*z - y*w);
		mat[9] = qpowx2*(y*z + x*w);
		mat[10] = 1 - q2*(x*x + y*y);

		mat[3] = mat[7] = mat[11] =  mat[12] =
						mat[13] = mat[14] = 0;

		mat[15] = 1;

		return mat;
	}

	/// data
	T w,x,y,z;
};
#endif // QUARTERNION_H
