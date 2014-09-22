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
#ifndef MISC_H
#define MISC_H

#include <string>
#include <sstream>

/// Printing class for c++

namespace tvml
{

template<typename T, int cols, int rows = 1, int PRECISION = 3>
class Printable
{
public:
  static_assert(rows >=1, "Rows must be at least 1");
  static_assert(cols >=1, "Columns must be at least 1");

  std::string repr() const
  {
    std::stringstream ss;
    ss.precision(PRECISION);

    if(rows > 1)
      ss << "[";

    for(int row=0;row < rows;row++)
    {
      ss << "[";
      for(int col=0;col < cols;col++)
      {
        if(col != 0)
          ss << ", ";
        ss << ((const T&)*this)[row*cols + col];
      }
      ss << "]";
    }

    if(rows > 1)
      ss << "]";

    return ss.str();
  }

  operator std::string() const
  {
    return repr();
  }
};


} // namespace tvml

#include <iostream>
template<typename T, int R, int C, int P>
std::ostream& operator<<(std::ostream& stream, const tvml::Printable<T,R,C,P>& to_print){
  stream << to_print.repr();
  return stream;
}
#endif // MISC_H
