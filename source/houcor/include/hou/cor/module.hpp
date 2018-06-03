// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_COR_MODULE_HPP
#define HOU_COR_MODULE_HPP

#include "hou/cor/non_instantiable.hpp"

#include "hou/cor/cor_config.hpp"

#include <cstdlib>
#include <exception>



namespace hou
{

/** Module initialization and termination manager.
 *
 * This class is used as the base to create static classes responsible for
 * the initialization and termination of global state connected to a library
 * module.
 *
 * Operative systems are normally capable of freeing resources after a simple
 * program termination, but some modules might change global system settings
 * that would not be restored automatically.
 *
 * The class must be given an implementation Impl as template parameter.
 * Impl must define two static methods with the following signature:
 * ```
 * bool on_setup();
 * void on_teardown() noexcept;
 * ```
 *
 * on_setup will be called when calling initialize, on_teardown will be called
 * when calling terminate.
 *
 * on_setup should return true in case of a successful initialization, or false
 * in case if error. In both cases, on_setup must leave the program in a
 * consistent state.
 *
 * on_teardown is not allowed to fail.
 * It must always correctly restore the state as it was before the call to
 * on_setup.
 *
 * \tparam Impl implementation for a specific module.
 */
template <typename Impl>
class module : public non_instantiable
{
public:
  /* Sets up the module.
   *
   * If the module is not initialized, it internally calls Impl::on_setup() and
   * returns its return value.
   *
   * If the module is already initialized, it immediately returns true.
   *
   * This function is not thread-safe.
   * It should be called only by the main thread (and should normally be
   * sufficient to just call it once).
   *
   * \return true if the module is initialized after the call, false otherwise.
   */
  static bool initialize();

  /** Tears down the module.
   *
   * If the module is not initialized or was alredy torn down, this function
   * does nothing.
   *
   * This function is not thread-safe.
   * It should be called only by the main thread (and should normally be
   * sufficient to just call it once at program exit).
   *
   * If the module is initialized, it internally calls Impl::on_teardown();
   */
  static void terminate() noexcept;

  /** Checks if the module has already been initialized.
   *
   * \true if the module is initialized, false otherwise.
   */
  static bool is_initialized() noexcept;

private:
  static bool s_initialized;
};

/** Registers callbacks for std::exit and std::quick_exit to terminate Module.
 *
 * This function is just an utility to automatically register callbacks to
 * terminate the module at the program exit.
 * If you prefer, you can do it manually and register your own callbacks.
 *
 * It is suggested to always register the callbacks after initializing a module,
 * in order to make sure that proper clean up will be performed if std::exit or
 * std::quick_exit are called somewhere.
 *
 * Only the first call to this function will register the callback.
 *
 * \note signal handlers will normally not call the exit callbacks by default.
 * This means that if the application terminates as a consequence to a call to a
 * signal handler, proper termination will not be performed.
 * You may provide custom callbacks with std::signal, but there are strong
 * constraints on what can be done in such function.
 * As a general rule module termination functions can't be safely called from
 * inside a signal callback, therefore there is no way to ensure proper cleanup
 * when responding to a signal.
 *
 * \note std::abort kills the application by rasing the SIGABRT signal.
 * This means that calling std::abort will not ensure proper module cleanup.
 * For this reason, avoid calling std::abort and prefer std::exit or
 * std::quick_exit instead.
 * Note that if exceptions are disabled, they are disabled also in the STL.
 * STL classes will then call std::abort instead of throwing exceptions,
 * meaning that error generating from STL classes might result in missing
 * cleanup.
 *
 * \note calls to std::terminate will by default call std::abort, and will
 * therefore bypass these callbacks.
 * It is advised to wrap the whole main function in a try-catch block in order
 * to ensure a normal exit when an exception is not handled.
 * If this is not possible, it is advised to set the std::terminate callback
 * with std::set_terminate so that it calls std::exit instead of std::abort in
 * order to ensure proper cleanup on termination.
 *
 * \tparam Module the module object.
 * It should be an instance of the template class hou::module<Impl>.
 */
template <typename Module>
void call_terminate_on_exit();

}  // namespace hou



#include "hou/cor/module.inl"

#endif
