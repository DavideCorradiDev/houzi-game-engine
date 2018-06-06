// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

namespace hou
{

template <typename Impl>
bool module<Impl>::s_initialized(false);



template <typename Impl>
bool module<Impl>::initialize()
{
  if(s_initialized)
  {
    return true;
  }
  s_initialized = Impl::on_initialize();
  return s_initialized;
}



template <typename Impl>
void module<Impl>::terminate() noexcept
{
  if(!s_initialized)
  {
    return;
  }
  Impl::on_terminate();
  s_initialized = false;
}



template <typename Impl>
bool module<Impl>::is_initialized() noexcept
{
  return s_initialized;
}



template <typename Impl>
void module<Impl>::register_terminate_callbacks()
{
  static bool already_called = false;
  if(!already_called)
  {
    already_called = true;
    std::atexit(&module<Impl>::terminate);
    std::at_quick_exit(&module<Impl>::terminate);
  }
}

}  // namespace hou
