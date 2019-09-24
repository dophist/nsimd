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

#ifndef NSIMD_MODULES_FIXED_POINT_FUNCTION_SIMD_MUL_HPP
#define NSIMD_MODULES_FIXED_POINT_FUNCTION_SIMD_MUL_HPP

#include <nsimd/nsimd.h>
#include "nsimd/modules/fixed_point/simd.hpp"

namespace nsimd {
namespace fixed_point {
template <uint8_t _lf, uint8_t _rt>
NSIMD_INLINE fpsimd_t<_lf, _rt> simd_mul(const fpsimd_t<_lf, _rt> &a,
                                         const fpsimd_t<_lf, _rt> &b) {
  typedef typename fp_t<_lf, _rt>::value_up up_t;
  typedef typename fp_t<_lf, _rt>::value_type val_t;
  typedef typename fp_t<_lf, _rt>::simd_up simd_up_t;
  const int n_bits = 8 * sizeof(val_t);
  const int shift = n_bits - _lf;

  simd_up_t a_big0 = nsimd::upcvt(a._raw, val_t(), up_t()).v0;
  simd_up_t a_big1 = nsimd::upcvt(a._raw, val_t(), up_t()).v1;
  simd_up_t b_big0 = nsimd::upcvt(b._raw, val_t(), up_t()).v0;
  simd_up_t b_big1 = nsimd::upcvt(b._raw, val_t(), up_t()).v1;

  a_big0 = nsimd::mul(a_big0, b_big0, up_t());
  a_big0 = nsimd::shr(a_big0, shift, up_t());
  a_big1 = nsimd::mul(a_big1, b_big1, up_t());
  a_big1 = nsimd::shr(a_big1, shift, up_t());

  fpsimd_t<_lf, _rt> res;
  res._raw = nsimd::downcvt(a_big0, a_big1, up_t(), val_t());

  return res;
}

// Operator overload with base type compatibility
template <uint8_t _lf, uint8_t _rt>
NSIMD_INLINE fpsimd_t<_lf, _rt> operator*(const fpsimd_t<_lf, _rt> &a,
                                          const fpsimd_t<_lf, _rt> &b) {
  return simd_mul(a, b);
}

} // namespace fixed_point
} // namespace nsimd

#endif
