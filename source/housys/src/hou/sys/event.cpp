// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/sys/event.hpp"

#include "hou/sys/sys_exceptions.hpp"
#include "hou/sys/window.hpp"

#include "hou/sys/sdl/sdl_utils.hpp"

#include "SDL2/SDL_events.h"
#include "SDL2/SDL_timer.h"



namespace hou
{

namespace event
{

namespace
{

window& get_window_from_id(Uint32 id);

void process(const SDL_Event& event);

quit_callback& get_quit_callback();



window& get_window_from_id(Uint32 id)
{
  SDL_Window* w = SDL_GetWindowFromID(id);
  HOU_SDL_CHECK(w != nullptr);
  return window::get_impl_window(w);
}



void process(const SDL_Event& event)
{
  switch(event.type)
  {
    case SDL_QUIT:
    {
      auto callback = get_quit_callback();
      if(callback != nullptr)
      {
        callback(timestamp(event.quit.timestamp));
      }
    }
  }
}



quit_callback& get_quit_callback()
{
  static quit_callback callback = nullptr;
  return callback;
}

}



bool queue_empty()
{
  return SDL_HasEvents(SDL_FIRSTEVENT, SDL_LASTEVENT) == SDL_FALSE;
}



void wait_next()
{
  SDL_Event event;
  HOU_SDL_CHECK(SDL_WaitEvent(&event) != 0);
  process(event);
}



bool process_next()
{
  SDL_Event event;
  if(SDL_PollEvent(&event))
  {
    process(event);
    return true;
  }
  return false;
}



void process_all()
{
  while(process_next()) {}
}



void flush_all()
{
  SDL_FlushEvents(SDL_FIRSTEVENT, SDL_LASTEVENT);
}



void set_quit_callback(quit_callback f)
{
  get_quit_callback() = f;
}



void generate_quit()
{
  SDL_Event event;
  event.type = SDL_QUIT;
  event.quit.timestamp = SDL_GetTicks();
  HOU_SDL_CHECK(SDL_PushEvent(&event) >= 0);
}

}  // namespace event

}  // namespace hou
