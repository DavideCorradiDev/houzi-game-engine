// // Houzi Game Engine
// // Copyright (c) 2018 Davide Corradi
// // Licensed under the MIT license.
// 
// #include "hou/cor/core_exceptions.hpp"
// 
// 
// 
// namespace hou
// {
// 
// const std::string precondition_violated::what_msg
//   = u8"A precondition has been violated.";
// 
// 
// 
// precondition_violated::precondition_violated(
//   const filename_type& filename, uint line) noexcept
//   : exception(filename, line)
// {}
// 
// 
// 
// const char* precondition_violated::what() const noexcept
// {
//   return what_msg.c_str();
// }
// 
// 
// 
// std::string precondition_violated::message_extension() const
// {
//   return what_msg;
// }
// 
// 
// 
// const std::string postcondition_violated::what_msg
//   = u8"A postcondition has been violated.";
// 
// 
// 
// postcondition_violated::postcondition_violated(
//   const filename_type& filename, uint line) noexcept
//   : exception(filename, line)
// {}
// 
// 
// 
// const char* postcondition_violated::what() const noexcept
// {
//   return what_msg.c_str();
// }
// 
// 
// 
// std::string postcondition_violated::message_extension() const
// {
//   return what_msg;
// }
// 
// 
// 
// const std::string invariant_violated::what_msg
//   = u8"An invariant has been violated.";
// 
// 
// 
// invariant_violated::invariant_violated(
//   const filename_type& filename, uint line) noexcept
//   : exception(filename, line)
// {}
// 
// 
// 
// const char* invariant_violated::what() const noexcept
// {
//   return what_msg.c_str();
// }
// 
// 
// 
// std::string invariant_violated::message_extension() const
// {
//   return what_msg;
// }
// 
// }  // namespace hou
