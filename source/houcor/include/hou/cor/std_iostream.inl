// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

namespace hou
{

template <typename IosType>
ios_formatting_saver<IosType>::ios_formatting_saver(IosType& ios)
  : non_copyable()
  , m_ios(&ios)
  , m_flags(ios.flags())
  , m_precision(ios.precision())
  , m_width(ios.width())
  , m_fill(ios.fill())
{}



template <typename IosType>
ios_formatting_saver<IosType>::ios_formatting_saver(
  ios_formatting_saver&& other)
  : non_copyable(std::move(other))
  , m_ios(std::move(other.m_ios))
  , m_flags(std::move(other.m_flags))
  , m_precision(std::move(other.m_precision))
  , m_width(std::move(other.m_width))
  , m_fill(std::move(other.m_fill))
{
  m_ios = nullptr;
}



template <typename IosType>
ios_formatting_saver<IosType>::~ios_formatting_saver()
{
  if(m_ios != nullptr)
  {
    m_ios->flags(m_flags);
    m_ios->precision(m_precision);
    m_ios->width(m_width);
    m_ios->fill(m_fill);
  }
}

}  // namespace hou
