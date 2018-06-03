// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

namespace hou
{

template <typename Impl>
bool module<Impl>::s_initialized(false);



template <typename Impl>
bool module<Impl>::setup()
{
  if(s_initialized)
  {
    return true;
  }
  s_initialized = Impl::on_setup();
  return s_initialized;
}



template <typename Impl>
void module<Impl>::teardown() noexcept
{
  if(!s_initialized)
  {
    return;
  }
  Impl::on_teardown();
  s_initialized = false;
}



template <typename Impl>
bool module<Impl>::is_initialized() noexcept
{
  return s_initialized;
}



template <typename Module>
void do_teardown_on_exit()
{
  static bool already_called = false;
  if(!already_called)
  {
    already_called = true;
    std::atexit(&Module::teardown);
    std::at_quick_exit(&Module::teardown);
  }
}

}
