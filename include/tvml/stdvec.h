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
#ifndef STDVEC_H
#define STDVEC_H

#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"

/// Opencl/cuda naming

typedef Vector2<char>      char2;
typedef Vector2<uint8_t>   uchar2;

typedef Vector2<int16_t>   short2;
typedef Vector2<uint16_t>  ushort2;

typedef Vector2<int32_t>   int2;
typedef Vector2<uint32_t>  uint2;

typedef Vector2<int64_t>   long2;
typedef Vector2<uint64_t>  ulong2;

typedef Vector2<float>     float2;
typedef Vector2<double>    double2;


typedef Vector3<char>      char3;
typedef Vector3<uint8_t>   uchar3;

typedef Vector3<int16_t>   short3;
typedef Vector3<uint16_t>  ushort3;

typedef Vector3<int32_t>   int3;
typedef Vector3<uint32_t>  uint3;

typedef Vector3<int64_t>   long3;
typedef Vector3<uint64_t>  ulong3;

typedef Vector3<float>     float3;
typedef Vector3<double>    double3;


typedef Vector4<char>      char4;
typedef Vector4<uint8_t>   uchar4;

typedef Vector4<int16_t>   short4;
typedef Vector4<uint16_t>  ushort4;

typedef Vector4<int32_t>   int4;
typedef Vector4<uint32_t>  uint4;

typedef Vector4<int64_t>   long4;
typedef Vector4<uint64_t>  ulong4;

typedef Vector4<float>     float4;
typedef Vector4<double>    double4;

/// Opengl naming
typedef Vector2<int32_t> ivec2;
typedef Vector2<uint32_t> uvec2;

typedef Vector2<float> vec2;
typedef Vector2<double> dvec2;

typedef Vector3<int32_t> ivec3;
typedef Vector3<uint32_t> uvec3;

typedef Vector3<float> vec3;
typedef Vector3<double> dvec3;

typedef Vector4<int32_t> ivec4;
typedef Vector4<uint32_t> uvec4;

typedef Vector4<float> vec4;
typedef Vector4<double> dvec4;


#endif // STDVEC_H
