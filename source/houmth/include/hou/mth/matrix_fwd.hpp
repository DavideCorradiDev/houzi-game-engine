// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_MTH_MATRIX_FWD_HPP
#define HOU_MTH_MATRIX_FWD_HPP

#include "hou/mth/mth_config.hpp"

#include "hou/cor/checked_variable_fwd.hpp"



namespace hou
{

template <typename T, size_t Rows, size_t Cols>
class matrix;

/** 1x1 matrix */
template <typename T>
using mat1x1 = matrix<T, 1u, 1u>;
/** 1x2 matrix */
template <typename T>
using mat1x2 = matrix<T, 1u, 2u>;
/** 1x3 matrix */
template <typename T>
using mat1x3 = matrix<T, 1u, 3u>;
/** 1x4 matrix */
template <typename T>
using mat1x4 = matrix<T, 1u, 4u>;
/** 2x1 matrix */
template <typename T>
using mat2x1 = matrix<T, 2u, 1u>;
/** 2x2 matrix */
template <typename T>
using mat2x2 = matrix<T, 2u, 2u>;
/** 2x3 matrix */
template <typename T>
using mat2x3 = matrix<T, 2u, 3u>;
/** 2x4 matrix */
template <typename T>
using mat2x4 = matrix<T, 2u, 4u>;
/** 3x1 matrix */
template <typename T>
using mat3x1 = matrix<T, 3u, 1u>;
/** 3x2 matrix */
template <typename T>
using mat3x2 = matrix<T, 3u, 2u>;
/** 3x3 matrix */
template <typename T>
using mat3x3 = matrix<T, 3u, 3u>;
/** 3x4 matrix */
template <typename T>
using mat3x4 = matrix<T, 3u, 4u>;
/** 4x1 matrix */
template <typename T>
using mat4x1 = matrix<T, 4u, 1u>;
/** 4x2 matrix */
template <typename T>
using mat4x2 = matrix<T, 4u, 2u>;
/** 4x3 matrix */
template <typename T>
using mat4x3 = matrix<T, 4u, 3u>;
/** 4x4 matrix */
template <typename T>
using mat4x4 = matrix<T, 4u, 4u>;

/** int 1x1 matrix */
using mat1x1i = mat1x1<int>;
/** int 1x2 matrix */
using mat1x2i = mat1x2<int>;
/** int 1x3 matrix */
using mat1x3i = mat1x3<int>;
/** int 1x4 matrix */
using mat1x4i = mat1x4<int>;
/** int 2x1 matrix */
using mat2x1i = mat2x1<int>;
/** int 2x2 matrix */
using mat2x2i = mat2x2<int>;
/** int 2x3 matrix */
using mat2x3i = mat2x3<int>;
/** int 2x4 matrix */
using mat2x4i = mat2x4<int>;
/** int 3x1 matrix */
using mat3x1i = mat3x1<int>;
/** int 3x2 matrix */
using mat3x2i = mat3x2<int>;
/** int 3x3 matrix */
using mat3x3i = mat3x3<int>;
/** int 3x4 matrix */
using mat3x4i = mat3x4<int>;
/** int 4x1 matrix */
using mat4x1i = mat4x1<int>;
/** int 4x2 matrix */
using mat4x2i = mat4x2<int>;
/** int 4x3 matrix */
using mat4x3i = mat4x3<int>;
/** int 4x4 matrix */
using mat4x4i = mat4x4<int>;

/** Unsigned int 1x1 matrix */
using mat1x1u = mat1x1<uint>;
/** Unsigned int 1x2 matrix */
using mat1x2u = mat1x2<uint>;
/** Unsigned int 1x3 matrix */
using mat1x3u = mat1x3<uint>;
/** Unsigned int 1x4 matrix */
using mat1x4u = mat1x4<uint>;
/** Unsigned int 2x1 matrix */
using mat2x1u = mat2x1<uint>;
/** Unsigned int 2x2 matrix */
using mat2x2u = mat2x2<uint>;
/** Unsigned int 2x3 matrix */
using mat2x3u = mat2x3<uint>;
/** Unsigned int 2x4 matrix */
using mat2x4u = mat2x4<uint>;
/** Unsigned int 3x1 matrix */
using mat3x1u = mat3x1<uint>;
/** Unsigned int 3x2 matrix */
using mat3x2u = mat3x2<uint>;
/** Unsigned int 3x3 matrix */
using mat3x3u = mat3x3<uint>;
/** Unsigned int 3x4 matrix */
using mat3x4u = mat3x4<uint>;
/** Unsigned int 4x1 matrix */
using mat4x1u = mat4x1<uint>;
/** Unsigned int 4x2 matrix */
using mat4x2u = mat4x2<uint>;
/** Unsigned int 4x3 matrix */
using mat4x3u = mat4x3<uint>;
/** Unsigned int 4x4 matrix */
using mat4x4u = mat4x4<uint>;

/** float 1x1 matrix */
using mat1x1f = mat1x1<float>;
/** float 1x2 matrix */
using mat1x2f = mat1x2<float>;
/** float 1x3 matrix */
using mat1x3f = mat1x3<float>;
/** float 1x4 matrix */
using mat1x4f = mat1x4<float>;
/** float 2x1 matrix */
using mat2x1f = mat2x1<float>;
/** float 2x2 matrix */
using mat2x2f = mat2x2<float>;
/** float 2x3 matrix */
using mat2x3f = mat2x3<float>;
/** float 2x4 matrix */
using mat2x4f = mat2x4<float>;
/** float 3x1 matrix */
using mat3x1f = mat3x1<float>;
/** float 3x2 matrix */
using mat3x2f = mat3x2<float>;
/** float 3x3 matrix */
using mat3x3f = mat3x3<float>;
/** float 3x4 matrix */
using mat3x4f = mat3x4<float>;
/** float 4x1 matrix */
using mat4x1f = mat4x1<float>;
/** float 4x2 matrix */
using mat4x2f = mat4x2<float>;
/** float 4x3 matrix */
using mat4x3f = mat4x3<float>;
/** float 4x4 matrix */
using mat4x4f = mat4x4<float>;

/** double 1x1 matrix */
using mat1x1d = mat1x1<double>;
/** double 1x2 matrix */
using mat1x2d = mat1x2<double>;
/** double 1x3 matrix */
using mat1x3d = mat1x3<double>;
/** double 1x4 matrix */
using mat1x4d = mat1x4<double>;
/** double 2x1 matrix */
using mat2x1d = mat2x1<double>;
/** double 2x2 matrix */
using mat2x2d = mat2x2<double>;
/** double 2x3 matrix */
using mat2x3d = mat2x3<double>;
/** double 2x4 matrix */
using mat2x4d = mat2x4<double>;
/** double 3x1 matrix */
using mat3x1d = mat3x1<double>;
/** double 3x2 matrix */
using mat3x2d = mat3x2<double>;
/** double 3x3 matrix */
using mat3x3d = mat3x3<double>;
/** double 3x4 matrix */
using mat3x4d = mat3x4<double>;
/** double 4x1 matrix */
using mat4x1d = mat4x1<double>;
/** double 4x2 matrix */
using mat4x2d = mat4x2<double>;
/** double 4x3 matrix */
using mat4x3d = mat4x3<double>;
/** double 4x4 matrix */
using mat4x4d = mat4x4<double>;

/** vector */
template <typename T, size_t dimension>
using vec = matrix<T, dimension, 1u>;

/** 1d vector */
template <typename T>
using vec1 = vec<T, 1u>;
/** int 1d vector */
using vec1i = vec1<int>;
/** Unsigned int 1d vector */
using vec1u = vec1<uint>;
/** float 1d vector */
using vec1f = vec1<float>;
/** double 1d vector */
using vec1d = vec1<double>;

/** 2d vector */
template <typename T>
using vec2 = vec<T, 2u>;
/** int 2d vector */
using vec2i = vec2<int>;
/** Unsigned int 2d vector */
using vec2u = vec2<uint>;
/** float 2d vector */
using vec2f = vec2<float>;
/** double 2d vector */
using vec2d = vec2<double>;

/** 3d vector */
template <typename T>
using vec3 = vec<T, 3u>;
/** int 3d vector */
using vec3i = vec3<int>;
/** Unsigned int 3d vector */
using vec3u = vec3<uint>;
/** float 3d vector */
using vec3f = vec3<float>;
/** double 3d vector */
using vec3d = vec3<double>;

/** int 1d non-negative vector */
using vec1ipz = vec1<non_negative<int>>;
/** float 1d non-negative vector */
using vec1fpz = vec1<non_negative<float>>;
/** double 1d non-negative vector */
using vec1dpz = vec1<non_negative<double>>;

/** int 2d non-negative vector */
using vec2ipz = vec2<non_negative<int>>;
/** float 2d non-negative vector */
using vec2fpz = vec2<non_negative<float>>;
/** double 2d non-negative vector */
using vec2dpz = vec2<non_negative<double>>;

/** int 3d non-negative vector */
using vec3ipz = vec3<non_negative<int>>;
/** float 3d non-negative vector */
using vec3fpz = vec3<non_negative<float>>;
/** double 3d non-negative vector */
using vec3dpz = vec3<non_negative<double>>;

}  // namespace hou

#endif
