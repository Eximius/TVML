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

/*
 * Compile with g++ -O3 -Wall test.cpp -I ../include -o test
 */

#include <tvml/stdvec.h>
#include <tvml/stdmat.h>
#include <tvml/quart.h>

#include <iostream>

using namespace std;

template<typename Vec2T>
inline void testVec2(const char* name)
{
  Vec2T v1 = {2,3};
  Vec2T v2 = {3,2};

  cout << name << "s: " << v1 <<", "<< v2 << "\n";
  cout << "Dot: " << v1*v2 <<"\n";
  cout << "Normals: "<< v1.normal() << ", " << v2.normal() << "\n\n";
}

template<typename Vec3T>
inline void testVec3(const char* name)
{
  Vec3T v1 = {1,2,3};
  Vec3T v2 = {3,2,1};

  cout << name << "s: " << v1 <<", "<< v2 << "\n";
  cout << "Dot: " << v1*v2 <<"\n";
  cout << "Cross: "<< v1.cross(v2) << "\n";
  cout << "Normals: "<< v1.normal() << ", " << v2.normal() << "\n\n";
}

template<typename Vec4T>
inline void testVec4(const char* name)
{
  Vec4T v1 = {1,2,3,4};
  Vec4T v2 = {4,3,2,1};

  cout << name << "s: " << v1 <<", "<< v2 << "\n";
  cout << "Dot: " << v1*v2 <<"\n";
  cout << "Normals: "<< v1.normal() << ", " << v2.normal() << "\n\n";
}

int main()
{
  cout << "Testing Tiny Vector Math Library\n\n";

  testVec2<ivec2>("ivec2");
  testVec2<dvec2>("dvec2");

  testVec3<ivec3>("ivec3");
  testVec3<dvec3>("dvec3");

  testVec4<ivec4>("ivec4");
  testVec4<dvec4>("dvec4");

  {
    cout << "Matrix3x3:\n";

    cout << "Zero: "<< dmat3::Zero <<"\n";
    cout << "Identity: " << dmat3::Identity << "\n";

    dmat3 m = dmat3({9,3,5,-6,-9,7,-1,-8,1});
    dmat3 mi = m.inverse();

    cout << "Matrix "<< m << "\n det: "<< m.det() << "\n inverse: "<< mi << "\n";
    cout << "Product: "<< (m*mi) << "\n\n";
  }

  {
    cout << "Matrix4x4:\n";

    cout << "Zero: "<< dmat4::Zero <<"\n";
    cout << "Identity: " << dmat4::Identity << "\n";

    dmat4 m = dmat4({ 9, 3,  5, -6,
                      -9, 7, -1, -8,
                      1, 3,  6, 10,
                      67,54, 83, 30});
    dmat4 mi = m.inverse();

    cout << "Matrix "<< m << "\n det: "<< m.det() << "\n inverse: "<< mi << "\n";
    cout << "Product: "<< (m*mi) << "\n\n";
  }

  {
    cout << "Rotations:\n";
    quart rot = quart(rad(45), vec3(0,1,0));

    mat3 rotm = rot;

    cout << "45 deg around vertical rotation matrix:\n" << rotm << "\n\n";
    vec3 v = vec3(1,0,0);
    cout << "Rotate "<< v << " with "<< rotm << " :\n";
    cout << rotm*v << "\n\n";

    rotm = rotm*mat3(quart(rad(45), vec3(1,0,0)));
    cout << "Now rotate that matrix with 45 deg around horizontal (x)\n" << rotm << "\n\n";

    cout << "If it is still normalized inverse and transpose should be the same:\n";

    cout << rotm.inverse() << "\n == \n" << rotm.transpose() << "\n\n";

    cout << "Rotate "<< v << " with "<< rotm << " :\n";
    cout << rotm*v << "\n\n";
  }

  cout << "That's it, folks.\n" << endl;
  return 0;
}
