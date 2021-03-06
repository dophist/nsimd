/*

Copyright (c) 2019 Agenium Scale

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

*/

#include <nsimd/nsimd-all.hpp>
#include <cstdlib>

// ----------------------------------------------------------------------------

int main() {
  using namespace nsimd;
  const int unroll = 3;
  typedef pack<unsigned int, unroll> upack;

  const int n_max = unroll * NSIMD_MAX_LEN(f32);
  const int n = len(upack());
  unsigned int buf[n_max];

  for(int i = 0; i < n; i++) {
    buf[i] = (unsigned int)i;
  }
  upack v = loadu<upack>(buf);

  if (any(((v << 4) >> 4) != v)) {
    exit(EXIT_FAILURE);
  }

  return 0;
}
