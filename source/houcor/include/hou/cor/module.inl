// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

namespace hou
{

template <typename Impl>
bool module<Impl>::s_initialized(false);



template <typename Impl>
void module<Impl>::initialize()
{
  if(s_initialized)
  {
    return;
  }
  s_initialized = Impl::on_initialize();
  HOU_CHECK_N(s_initialized, module_initialization_error, Impl::get_name());
  register_terminate_callbacks();
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
void module<Impl>::register_terminate_callbacks() noexcept
{
  static bool already_called = false;
  if(!already_called)
  {
    already_called = true;
    std::atexit(&module<Impl>::terminate);
  }
}

}  // namespace hou
