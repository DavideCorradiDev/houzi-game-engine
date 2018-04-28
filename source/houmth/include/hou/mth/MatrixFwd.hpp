// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_MTH_MATRIX_FWD_HPP
#define HOU_MTH_MATRIX_FWD_HPP

#include "hou/cor/basic_types.hpp"



namespace hou
{

template <typename T, size_t rows, size_t cols> class Matrix;

/** 1x1 matrix */
template <typename T>
  using Mat1x1 = Matrix<T, 1u, 1u>;
/** 1x2 matrix */
template <typename T>
  using Mat1x2 = Matrix<T, 1u, 2u>;
/** 1x3 matrix */
template <typename T>
  using Mat1x3 = Matrix<T, 1u, 3u>;
/** 1x4 matrix */
template <typename T>
  using Mat1x4 = Matrix<T, 1u, 4u>;
/** 2x1 matrix */
template <typename T>
  using Mat2x1 = Matrix<T, 2u, 1u>;
/** 2x2 matrix */
template <typename T>
  using Mat2x2 = Matrix<T, 2u, 2u>;
/** 2x3 matrix */
template <typename T>
  using Mat2x3 = Matrix<T, 2u, 3u>;
/** 2x4 matrix */
template <typename T>
  using Mat2x4 = Matrix<T, 2u, 4u>;
/** 3x1 matrix */
template <typename T>
  using Mat3x1 = Matrix<T, 3u, 1u>;
/** 3x2 matrix */
template <typename T>
  using Mat3x2 = Matrix<T, 3u, 2u>;
/** 3x3 matrix */
template <typename T>
  using Mat3x3 = Matrix<T, 3u, 3u>;
/** 3x4 matrix */
template <typename T>
  using Mat3x4 = Matrix<T, 3u, 4u>;
/** 4x1 matrix */
template <typename T>
  using Mat4x1 = Matrix<T, 4u, 1u>;
/** 4x2 matrix */
template <typename T>
  using Mat4x2 = Matrix<T, 4u, 2u>;
/** 4x3 matrix */
template <typename T>
  using Mat4x3 = Matrix<T, 4u, 3u>;
/** 4x4 matrix */
template <typename T>
  using Mat4x4 = Matrix<T, 4u, 4u>;

/** int 1x1 matrix */
using Mat1x1i = Mat1x1<int>;
/** int 1x2 matrix */
using Mat1x2i = Mat1x2<int>;
/** int 1x3 matrix */
using Mat1x3i = Mat1x3<int>;
/** int 1x4 matrix */
using Mat1x4i = Mat1x4<int>;
/** int 2x1 matrix */
using Mat2x1i = Mat2x1<int>;
/** int 2x2 matrix */
using Mat2x2i = Mat2x2<int>;
/** int 2x3 matrix */
using Mat2x3i = Mat2x3<int>;
/** int 2x4 matrix */
using Mat2x4i = Mat2x4<int>;
/** int 3x1 matrix */
using Mat3x1i = Mat3x1<int>;
/** int 3x2 matrix */
using Mat3x2i = Mat3x2<int>;
/** int 3x3 matrix */
using Mat3x3i = Mat3x3<int>;
/** int 3x4 matrix */
using Mat3x4i = Mat3x4<int>;
/** int 4x1 matrix */
using Mat4x1i = Mat4x1<int>;
/** int 4x2 matrix */
using Mat4x2i = Mat4x2<int>;
/** int 4x3 matrix */
using Mat4x3i = Mat4x3<int>;
/** int 4x4 matrix */
using Mat4x4i = Mat4x4<int>;

/** Unsigned int 1x1 matrix */
using Mat1x1u = Mat1x1<uint>;
/** Unsigned int 1x2 matrix */
using Mat1x2u = Mat1x2<uint>;
/** Unsigned int 1x3 matrix */
using Mat1x3u = Mat1x3<uint>;
/** Unsigned int 1x4 matrix */
using Mat1x4u = Mat1x4<uint>;
/** Unsigned int 2x1 matrix */
using Mat2x1u = Mat2x1<uint>;
/** Unsigned int 2x2 matrix */
using Mat2x2u = Mat2x2<uint>;
/** Unsigned int 2x3 matrix */
using Mat2x3u = Mat2x3<uint>;
/** Unsigned int 2x4 matrix */
using Mat2x4u = Mat2x4<uint>;
/** Unsigned int 3x1 matrix */
using Mat3x1u = Mat3x1<uint>;
/** Unsigned int 3x2 matrix */
using Mat3x2u = Mat3x2<uint>;
/** Unsigned int 3x3 matrix */
using Mat3x3u = Mat3x3<uint>;
/** Unsigned int 3x4 matrix */
using Mat3x4u = Mat3x4<uint>;
/** Unsigned int 4x1 matrix */
using Mat4x1u = Mat4x1<uint>;
/** Unsigned int 4x2 matrix */
using Mat4x2u = Mat4x2<uint>;
/** Unsigned int 4x3 matrix */
using Mat4x3u = Mat4x3<uint>;
/** Unsigned int 4x4 matrix */
using Mat4x4u = Mat4x4<uint>;

/** Size 1x1 matrix */
using Mat1x1s = Mat1x1<size_t>;
/** Size 1x2 matrix */
using Mat1x2s = Mat1x2<size_t>;
/** Size 1x3 matrix */
using Mat1x3s = Mat1x3<size_t>;
/** Size 1x4 matrix */
using Mat1x4s = Mat1x4<size_t>;
/** Size 2x1 matrix */
using Mat2x1s = Mat2x1<size_t>;
/** Size 2x2 matrix */
using Mat2x2s = Mat2x2<size_t>;
/** Size 2x3 matrix */
using Mat2x3s = Mat2x3<size_t>;
/** Size 2x4 matrix */
using Mat2x4s = Mat2x4<size_t>;
/** Size 3x1 matrix */
using Mat3x1s = Mat3x1<size_t>;
/** Size 3x2 matrix */
using Mat3x2s = Mat3x2<size_t>;
/** Size 3x3 matrix */
using Mat3x3s = Mat3x3<size_t>;
/** Size 3x4 matrix */
using Mat3x4s = Mat3x4<size_t>;
/** Size 4x1 matrix */
using Mat4x1s = Mat4x1<size_t>;
/** Size 4x2 matrix */
using Mat4x2s = Mat4x2<size_t>;
/** Size 4x3 matrix */
using Mat4x3s = Mat4x3<size_t>;
/** Size 4x4 matrix */
using Mat4x4s = Mat4x4<size_t>;

/** float 1x1 matrix */
using Mat1x1f = Mat1x1<float>;
/** float 1x2 matrix */
using Mat1x2f = Mat1x2<float>;
/** float 1x3 matrix */
using Mat1x3f = Mat1x3<float>;
/** float 1x4 matrix */
using Mat1x4f = Mat1x4<float>;
/** float 2x1 matrix */
using Mat2x1f = Mat2x1<float>;
/** float 2x2 matrix */
using Mat2x2f = Mat2x2<float>;
/** float 2x3 matrix */
using Mat2x3f = Mat2x3<float>;
/** float 2x4 matrix */
using Mat2x4f = Mat2x4<float>;
/** float 3x1 matrix */
using Mat3x1f = Mat3x1<float>;
/** float 3x2 matrix */
using Mat3x2f = Mat3x2<float>;
/** float 3x3 matrix */
using Mat3x3f = Mat3x3<float>;
/** float 3x4 matrix */
using Mat3x4f = Mat3x4<float>;
/** float 4x1 matrix */
using Mat4x1f = Mat4x1<float>;
/** float 4x2 matrix */
using Mat4x2f = Mat4x2<float>;
/** float 4x3 matrix */
using Mat4x3f = Mat4x3<float>;
/** float 4x4 matrix */
using Mat4x4f = Mat4x4<float>;

/** double 1x1 matrix */
using Mat1x1d = Mat1x1<double>;
/** double 1x2 matrix */
using Mat1x2d = Mat1x2<double>;
/** double 1x3 matrix */
using Mat1x3d = Mat1x3<double>;
/** double 1x4 matrix */
using Mat1x4d = Mat1x4<double>;
/** double 2x1 matrix */
using Mat2x1d = Mat2x1<double>;
/** double 2x2 matrix */
using Mat2x2d = Mat2x2<double>;
/** double 2x3 matrix */
using Mat2x3d = Mat2x3<double>;
/** double 2x4 matrix */
using Mat2x4d = Mat2x4<double>;
/** double 3x1 matrix */
using Mat3x1d = Mat3x1<double>;
/** double 3x2 matrix */
using Mat3x2d = Mat3x2<double>;
/** double 3x3 matrix */
using Mat3x3d = Mat3x3<double>;
/** double 3x4 matrix */
using Mat3x4d = Mat3x4<double>;
/** double 4x1 matrix */
using Mat4x1d = Mat4x1<double>;
/** double 4x2 matrix */
using Mat4x2d = Mat4x2<double>;
/** double 4x3 matrix */
using Mat4x3d = Mat4x3<double>;
/** double 4x4 matrix */
using Mat4x4d = Mat4x4<double>;

/** Vector */
template <typename T, size_t dimension>
  using Vec = Matrix<T, dimension, 1u>;

/** 1d vector */
template <typename T>
  using Vec1 = Vec<T, 1u>;
/** int 2d vector */
using Vec1i = Vec1<int>;
/** Unsigned int 2d vector */
using Vec1u = Vec1<uint>;
/** Size 2d vector */
using Vec1s = Vec1<size_t>;
/** float 2d vector */
using Vec1f = Vec1<float>;
/** double 2d vector */
using Vec1d = Vec1<double>;

/** 2d vector */
template <typename T>
  using Vec2 = Vec<T, 2u>;
/** int 2d vector */
using Vec2i = Vec2<int>;
/** Unsigned int 2d vector */
using Vec2u = Vec2<uint>;
/** Size 2d vector */
using Vec2s = Vec2<size_t>;
/** float 2d vector */
using Vec2f = Vec2<float>;
/** double 2d vector */
using Vec2d = Vec2<double>;

/** 3d vector */
template <typename T>
  using Vec3 = Vec<T, 3u>;
/** int 3d vector */
using Vec3i = Vec3<int>;
/** Unsigned int 3d vector */
using Vec3u = Vec3<uint>;
/** Size 3d vector */
using Vec3s = Vec3<size_t>;
/** float 3d vector */
using Vec3f = Vec3<float>;
/** double 3d vector */
using Vec3d = Vec3<double>;

}

#endif

