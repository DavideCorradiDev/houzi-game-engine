// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license. See license.md for more details.

#ifndef HOU_COR_STD_CHRONO_HPP
#define HOU_COR_STD_CHRONO_HPP

#include "hou/cor/CorExport.hpp"

#include <chrono>
#include <ostream>



namespace hou
{

/** Outputs a duration in nanoseconds to the given stream.
 *
 *  \tparam Rep the internal representation of the duration.
 *  \param os the output stream.
 *  \param d the duration.
 *  \return a reference to os.
 */
template <typename Rep>
  std::ostream& operator<<(std::ostream& os
  , std::chrono::duration<Rep, std::nano> d);

/** Outputs a duration in microseconds to the given stream.
 *
 *  \tparam Rep the internal representation of the duration.
 *  \param os the output stream.
 *  \param d the duration.
 *  \return a reference to os.
 */
template <typename Rep>
  std::ostream& operator<<(std::ostream& os
  , std::chrono::duration<Rep, std::micro> d);

/** Outputs a duration in milliseconds to the given stream.
 *
 *  \tparam Rep the internal representation of the duration.
 *  \param os the output stream.
 *  \param d the duration.
 *  \return a reference to os.
 */
template <typename Rep>
  std::ostream& operator<<(std::ostream& os
  , std::chrono::duration<Rep, std::milli> d);

/** Outputs a duration in seconds to the given stream.
 *
 *  \tparam Rep the internal representation of the duration.
 *  \param os the output stream.
 *  \param d the duration.
 *  \return a reference to os.
 */
template <typename Rep>
  std::ostream& operator<<(std::ostream& os
  , std::chrono::duration<Rep, std::ratio<1>> d);

/** Outputs a duration in minutes to the given stream.
 *
 *  \tparam Rep the internal representation of the duration.
 *  \param os the output stream.
 *  \param d the duration.
 *  \return a reference to os.
 */
template <typename Rep>
  std::ostream& operator<<(std::ostream& os
  , std::chrono::duration<Rep, std::ratio<60>> d);

/** Outputs a duration in hours to the given stream.
 *
 *  \tparam Rep the internal representation of the duration.
 *  \param os the output stream.
 *  \param d the duration.
 *  \return a reference to os.
 */
template <typename Rep>
  std::ostream& operator<<(std::ostream& os
  , std::chrono::duration<Rep, std::ratio<3600>> d);
}



#include "hou/cor/StdChrono.inl"

#endif

