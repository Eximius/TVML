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
#ifndef MATRIX33_H
#define MATRIX33_H

#include <cassert>
#include <algorithm>
#include <stdexcept>

#include "misc.h"
#include "Vector3.h"

/**
  Matrix is row major.
**/

template<typename T>
class Matrix3x3 : public tvml::Printable<Matrix3x3<T>, 3, 3>
{
  typedef Matrix3x3<T> Mat3T;
public:
  Matrix3x3(){}

  Matrix3x3(std::initializer_list<T> l)
  {
    assert(l.size() == 9 && "Matrix3x3 initializer list must have 9 elements.");
    for(int i=0; i<9; i++)
      m[i] = l.begin()[i];
  }

  explicit Matrix3x3(const T* mat){
    std::copy(mat, mat+9, m);
  }

  template<typename X>
  Matrix3x3(const Matrix3x3<X>& mat){
    std::copy(mat.data(),mat.data()+9,m);
  }

  static const
  Mat3T Zero;

  static const
  Mat3T Identity;

  /// Math operators
  Mat3T operator -()
  {
    Mat3T ret;
    for(int i=0; i<9; i++)
      ret[i] = -(*this)[i];
    return ret;
  }

  template<typename X>
  Mat3T operator +(Matrix3x3<X>& mat)
  {
    Mat3T ret;
    for(int i=0; i<9; i++)
      ret[i] = (*this)[i] + mat[i];
    return ret;
  }

  template<typename X>
  Mat3T operator -(Matrix3x3<X>& mat)
  {
    Mat3T ret;
    for(int i=0; i<9; i++)
      ret[i] = (*this)[i] - mat[i];
    return ret;
  }

  template<typename X>
  Mat3T operator *(const X& t)
  {
    Mat3T ret;
    for(int i=0; i<9; i++)
      ret[i] = (*this)[i] * t;
    return ret;
  }

  template<typename X>
  Mat3T operator /(const X& t)
  {
    Mat3T ret;
    for(int i=0; i<9; i++)
      ret[i] = (*this)[i] / t;
    return ret;
  }

  /// Matrix multiplication
  Matrix3x3<T> operator *(const Matrix3x3<T>& mat){
    Matrix3x3<T> ret;
    for(int a=0,b; a < 9; a+=3){
      b=0;
      ret[a] = m[a]*mat[b] + m[a+1]*mat[b+3] + m[a+2]*mat[b+6];
      b++;
      ret[a+1]= m[a]*mat[b] + m[a+1]*mat[b+3] + m[a+2]*mat[b+6];
      b++;
      ret[a+2]= m[a]*mat[b] + m[a+1]*mat[b+3] + m[a+2]*mat[b+6];
    }
    return ret;
  }
  template<typename X>
  Vector3<T> operator *(const Vector3<X>& vec){
    return Vector3<T>(vec.x*m[0] + vec.y*m[1] + vec.z*m[2],
        vec.x*m[3] + vec.y*m[4] + vec.z*m[5],
        vec.x*m[6] + vec.y*m[7] + vec.z*m[8]);
  }

  Mat3T transpose(){
    Mat3T ret = *this;

    std::swap(ret[1], ret[3]);
    std::swap(ret[2], ret[6]);
    std::swap(ret[5], ret[7]);

    return ret;
  }

  /// Matrix inversion
  T det()
  {
    return m[0]*(m[4]*m[8] - m[5]*m[7])
         - m[1]*(m[3]*m[8] - m[5]*m[6])
         + m[2]*(m[3]*m[7] - m[4]*m[6]);
  }

  template<int ex_row, int ex_col>
  T MINOR()
  {
    static_assert(ex_row >= 0 && ex_row < 3, "Row must be in [0,3]");
    static_assert(ex_col >= 0 && ex_col < 3, "Column must be in [0,3]");

    T minor[4];

    int i=0;
    for(int row=0;row<3;row++)
    {
      if(row != ex_row)
        for(int col=0;col<3;col++)
        {
          if(col != ex_col)
            minor[i++] = m[row*3+col];
        }
    }
    return minor[0]*minor[3] - minor[1]*minor[2];
  }

  Mat3T inverse()
  {
    // Inverse with cofactors.

    Mat3T ret;

    // Create matrix of minors -> cofactors -> transpose
    // aka, adjoint
    ret[0] = MINOR<0,0>();
    ret[1] = -MINOR<1,0>();
    ret[2] = MINOR<2,0>();
    ret[3] = -MINOR<0,1>();
    ret[4] = MINOR<1,1>();
    ret[5] = -MINOR<2,1>();
    ret[6] = MINOR<0,2>();
    ret[7] = -MINOR<1,2>();
    ret[8] = MINOR<2,2>();

    T det = m[0]*ret[0] +
            m[1]*ret[3] +
            m[2]*ret[6];

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
  T m[9];
};

template<typename T>
const Matrix3x3<T> Matrix3x3<T>::Zero = {0,0,0, 0,0,0, 0,0,0};

template<typename T>
const Matrix3x3<T> Matrix3x3<T>::Identity = {1,0,0, 0,1,0, 0,0,1};

#endif // MATRIX33_H
