// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_COR_MEMBER_DETECTOR_HPP
#define HOU_COR_MEMBER_DETECTOR_HPP

#include "hou/cor/cor_config.hpp"


/**
 * Generate a member detector helper to be used in template conditions.
 *
 * This macro creates a detector of member X called has_member_X.
 * If class T has a member called X, has_member_X<T>::value will be true,
 * otherwise it will be false.
 */
#define HOU_CREATE_MEMBER_DETECTOR(X)                                          \
  template <typename T,                                                        \
    bool IsFundamental                                                         \
    = std::is_fundamental<T>::value || std::is_enum<T>::value>                 \
  class has_member_##X;                                                        \
                                                                               \
  template <typename T>                                                        \
  class has_member_##X<T, true>                                                \
  {                                                                            \
  public:                                                                      \
    enum                                                                       \
    {                                                                          \
      value = false                                                            \
    };                                                                         \
  };                                                                           \
                                                                               \
  template <typename T>                                                        \
  class has_member_##X<T, false>                                               \
  {                                                                            \
  private:                                                                     \
    struct fallback                                                            \
    {                                                                          \
      int X;                                                                   \
    };                                                                         \
                                                                               \
    struct derived                                                             \
      : public T                                                               \
      , public fallback                                                        \
    {};                                                                        \
                                                                               \
    template <typename U, U>                                                   \
    struct check_helper                                                        \
    {};                                                                        \
                                                                               \
    using yes = char[1];                                                       \
    using no = char[2];                                                        \
                                                                               \
    template <typename U>                                                      \
    static no& check(check_helper<int fallback::*, &U::X>*);                   \
                                                                               \
    template <typename U>                                                      \
    static yes& check(...);                                                    \
                                                                               \
  public:                                                                      \
    enum                                                                       \
    {                                                                          \
      value = (sizeof(check<derived>(nullptr)) == sizeof(yes))                 \
    };                                                                         \
  }



/**
 * Generate a type detector helper to be used in template conditions.
 *
 * This macro created a detector of type X called has_member_type_X.
 * If class T has a nested class or typedef called X,
 * has_member_type_X<T>::value will be true, otherwise it will be false.
 */
#define HOU_CREATE_MEMBER_TYPE_DETECTOR(X)                                     \
  template <typename T>                                                        \
  class has_member_type_##X                                                    \
  {                                                                            \
  private:                                                                     \
    using yes = uint8_t[1];                                                    \
    using no = uint8_t[2];                                                     \
                                                                               \
    template <typename U>                                                      \
    static yes& test(typename U::X*);                                          \
                                                                               \
    template <typename U>                                                      \
    static no& test(...);                                                      \
                                                                               \
  public:                                                                      \
    enum                                                                       \
    {                                                                          \
      value = (sizeof(test<T>(nullptr)) == sizeof(yes))                        \
    };                                                                         \
  }

#endif
