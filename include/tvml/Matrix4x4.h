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
#ifndef MATRIX4X4_H
#define MATRIX4X4_H

#include <algorithm>
#include <stdexcept>

#include "misc.h"
#include "Matrix3x3.h"
#include "Vector3.h"
#include "Vector4.h"

/**
  Matrix is row major.
**/

template<typename T>
class Matrix4x4 : public tvml::Printable<Matrix4x4<T>, 4, 4>
{
  typedef Matrix4x4<T> Mat4T;
public:
  Matrix4x4() = default;

  Matrix4x4(std::initializer_list<T> l)
  {
    assert(l.size() == 16 && "Matrix4x4 initializer list must have 16 elements.");
    for(int i=0; i<16; i++)
      m[i] = l.begin()[i];
  }

  explicit Matrix4x4(const T* mat){
    std::copy(mat,mat+16,m);
  }

  template<typename X>
  Matrix4x4(const Matrix4x4<X>& mat){
    std::copy(mat.data(),mat.data()+16,m);
  }

  template< typename Z, typename X = T>
  explicit Matrix4x4(const Vector3<Z> translation, const Vector3<X> scale = Vector3<X>(1,1,1)){
    m[0]  = scale.x;
    m[5]  = scale.y;
    m[10] = scale.z;

    m[3]  = translation.x;
    m[7]  = translation.y;
    m[11] = translation.z;

    m[1] = m[2] = m[4] = m[6] = m[8] = m[9] = m[12] = m[13] = m[14] =0;
    m[15] = 1;
  }

  static const
  Mat4T Zero;

  static const
  Mat4T Identity;

  /// Math operators
  Mat4T operator -()
  {
    Mat4T ret;
    for(int i=0; i<16; i++)
      ret[i] = -(*this)[i];
    return ret;
  }

  template<typename X>
  Mat4T operator +(Matrix4x4<X>& mat)
  {
    Mat4T ret;
    for(int i=0; i<16; i++)
      ret[i] = (*this)[i] + mat[i];
    return ret;
  }

  template<typename X>
  Mat4T operator -(Matrix4x4<X>& mat)
  {
    Mat4T ret;
    for(int i=0; i<16; i++)
      ret[i] = (*this)[i] - mat[i];
    return ret;
  }

  template<typename X>
  Mat4T operator *(const X& t)
  {
    Mat4T ret;
    for(int i=0; i<16; i++)
      ret[i] = (*this)[i] * t;
    return ret;
  }

  template<typename X>
  Mat4T operator /(const X& t)
  {
    Mat4T ret;
    for(int i=0; i<16; i++)
      ret[i] = (*this)[i] / t;
    return ret;
  }

  /// Matrix multiplication
  Matrix4x4<T> operator *(const Matrix4x4<T>& mat){
    Matrix4x4<T> ret;
    for(int i=0; i < 16; i+=4){
      ret[i]  = m[i]*mat[0];
      ret[i+1]= m[i]*mat[1];
      ret[i+2]= m[i]*mat[2];
      ret[i+3]= m[i]*mat[3];

      for(int a=i+1,b=4; a< i+4 ; a++,b+=4){
        ret[i]  += m[a]*mat[b];
        ret[i+1]+= m[a]*mat[b+1];
        ret[i+2]+= m[a]*mat[b+2];
        ret[i+3]+= m[a]*mat[b+3];
      }
    }
    return ret;
  }
  Matrix4x4& operator *=(const Matrix4x4<T>& mat){
    Matrix4x4<T> ret;
    for(int i=0; i < 16; i+=4){
      ret[i]  = m[i]*mat[0];
      ret[i+1]= m[i]*mat[1];
      ret[i+2]= m[i]*mat[2];
      ret[i+3]= m[i]*mat[3];

      for(int a=i+1,b=4; a< i+4 ; a++,b+=4){
        ret[i]  += m[a]*mat[b];
        ret[i+1]+= m[a]*mat[b+1];
        ret[i+2]+= m[a]*mat[b+2];
        ret[i+3]+= m[a]*mat[b+3];
      }
    }
    (*this) = ret;
    return *this;
  }

  /// Assumes w=1
  template<typename X>
  Vector3<T> operator *(const Vector3<X>& vec){
    return Vector3<T>(vec.x*m[0]  + vec.y*m[1]  + vec.z*m[2]  + m[3],
        vec.x*m[4]  + vec.y*m[5]  + vec.z*m[6]  + m[7],
        vec.x*m[8]  + vec.y*m[9]  + vec.z*m[10] + m[11]);
  }

  template<typename X>
  Vector4<T> operator *(const Vector4<X>& vec){
    return Vector4<T>(vec.x*m[0]  + vec.y*m[1]  + vec.z*m[2]  + vec.w * m[3],
        vec.x*m[4]  + vec.y*m[5]  + vec.z*m[6]  + vec.w * m[7],
        vec.x*m[8]  + vec.y*m[9]  + vec.z*m[10] + vec.w * m[11],
        vec.x*m[12] + vec.y*m[13] + vec.z*m[14] + vec.w * m[15]);
  }

  Mat4T transpose(){
    Mat4T ret = *this;

    std::swap(ret[1], ret[4]);
    std::swap(ret[2], ret[8]);
    std::swap(ret[3], ret[12]);
    std::swap(ret[6], ret[9]);
    std::swap(ret[7], ret[13]);
    std::swap(ret[11], ret[14]);

    return ret;
  }

  /// Matrix inversion
  T det()
  {
    return + m[0]*MINOR<0,0>()
           - m[1]*MINOR<0,1>()
           + m[2]*MINOR<0,2>()
           - m[3]*MINOR<0,3>();
  }

  template<int ex_row, int ex_col>
  T MINOR()
  {
    static_assert(ex_row >= 0 && ex_row < 4, "Row must be in [0,4]");
    static_assert(ex_col >= 0 && ex_col < 4, "Column must be in [0,4]");

    Matrix3x3<T> minor;

    int i=0;
    for(int row=0;row<4;row++)
    {
      if(row != ex_row)
        for(int col=0;col<4;col++)
        {
          if(col != ex_col)
            minor[i++] = m[row*4+col];
        }
    }
    return minor.det();
  }

  Mat4T adjoint()
  {
    Mat4T ret;

    // Create matrix of minors -> cofactors -> transpose
    // aka, adjoint
    ret[0] = MINOR<0,0>();
    ret[1] = -MINOR<1,0>();
    ret[2] = MINOR<2,0>();
    ret[3] = -MINOR<3,0>();

    ret[4] = -MINOR<0,1>();
    ret[5] = MINOR<1,1>();
    ret[6] = -MINOR<2,1>();
    ret[7] = MINOR<3,1>();

    ret[8]  = MINOR<0,2>();
    ret[9]  = -MINOR<1,2>();
    ret[10] = MINOR<2,2>();
    ret[11] = -MINOR<3,2>();

    ret[12] = -MINOR<0,3>();
    ret[13] = MINOR<1,3>();
    ret[14] = -MINOR<2,3>();
    ret[15] = MINOR<3,3>();

    return ret;
  }

  Mat4T inverse()
  {
    // Inverses with cofactors.

    Mat4T ret = adjoint();

    T det = m[0]*ret[0] +
            m[1]*ret[4] +
            m[2]*ret[8] +
            m[3]*ret[12];

    if(det < 1e-07)
      throw std::runtime_error("Matrix doesn't have an inverse.");

    return ret / det;
  }

  const T* data() const { return m; }
  T*       data()       { return m; }

  const T& operator[](uint32_t index)const{
    return m[index];
  }
  T& operator[](uint32_t index){
    return m[index];
  }
private:
  T m[16];
};

template<typename T>
const Matrix4x4<T> Matrix4x4<T>::Zero = {0,0,0,0,
                                         0,0,0,0,
                                         0,0,0,0,
                                         0,0,0,0};

template<typename T>
const Matrix4x4<T> Matrix4x4<T>::Identity = {1,0,0,0,
                                             0,1,0,0,
                                             0,0,1,0,
                                             0,0,0,1};
#endif /* MATRIX4X4_H */
