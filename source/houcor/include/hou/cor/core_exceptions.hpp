// // Houzi Game Engine
// // Copyright (c) 2018 Davide Corradi
// // Licensed under the MIT license.
// 
// #ifndef HOU_COR_CORE_EXCEPTIONS_HPP
// #define HOU_COR_CORE_EXCEPTIONS_HPP
// 
// #include "hou/cor/cor_export.hpp"
// 
// #include "hou/cor/exception.hpp"
// 
// 
// 
// namespace hou
// {
// 
// class HOU_COR_API precondition_violated : public exception
// {
// public:
//   precondition_violated(const filename_type& filename, uint line) noexcept;
// 
//   const char* what() const noexcept override;
// 
// protected:
//   std::string message_extension() const override;
// 
// private:
//   static const std::string what_msg;
// };
// 
// 
// 
// class HOU_COR_API postcondition_violated : public exception
// {
// public:
//   postcondition_violated(const filename_type& filename, uint line) noexcept;
// 
//   const char* what() const noexcept override;
// 
// protected:
//   std::string message_extension() const override;
// 
// private:
//   static const std::string what_msg;
// };
// 
// 
// 
// class HOU_COR_API invariant_violated : public exception
// {
// public:
//   invariant_violated(const filename_type& filename, uint line) noexcept;
// 
//   const char* what() const noexcept override;
// 
// protected:
//   std::string message_extension() const override;
// 
// private:
//   static const std::string what_msg;
// };
// 
// }  // namespace hou
// 
// #endif
