// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/sys/File.hpp"

#include "hou/sys/SysError.hpp"

#include "hou/cor/error.hpp"
#include "hou/cor/std_string.hpp"

#include <cstdio>
#include <vector>



namespace hou
{

File::File(const std::string& filename, FileOpenMode mode, FileType type)
  : non_copyable()
  , mHandle(filename, mode, type)
  , mEof(false)
  , mError(false)
{}




File::File(File&& other)
  : non_copyable()
  , mHandle(std::move(other.mHandle))
  , mEof(std::move(other.mEof))
  , mError(std::move(other.mError))
{}



bool File::eof() const
{
  return mEof;
}



bool File::error() const
{
  return mError;
}



size_t File::getByteCount() const
{
  return getFileByteSize(getFileDescriptor(mHandle));
}



long File::tell() const
{
  long pos = ftell(mHandle);
  HOU_RUNTIME_CHECK(pos != -1L, get_text(SysError::FileTell));
  return pos;
}



void File::seekSet(long pos)
{
  seek(pos, SEEK_SET);
  updateFlags();
}



void File::seekFromEnd(long pos)
{
  seek(pos, SEEK_END);
  updateFlags();
}



void File::seekOffset(long offset)
{
  seek(offset, SEEK_CUR);
  updateFlags();
}



void File::flush() const
{
  HOU_RUNTIME_CHECK(fflush(mHandle) != EOF, get_text(SysError::FileFlush));
}




bool File::getc(char& c)
{
  int retval = fgetc(mHandle);
  updateFlags();
  c = static_cast<char>(retval);
  if(retval == EOF)
  {
    HOU_RUNTIME_CHECK(!error(), get_text(SysError::FileRead));
    return false;
  }
  return true;
}



void File::putc(char c)
{
  int retval = fputc(c, mHandle);
  updateFlags();
  HOU_RUNTIME_CHECK(retval != EOF, get_text(SysError::FileWrite));
}



size_t File::gets(std::string& str)
{
  const char* retval = fgets(const_cast<char*>(str.data()), str.size()
    , mHandle);
  updateFlags();
  if(retval == nullptr)
  {
    HOU_RUNTIME_CHECK(!error(), get_text(SysError::FileRead));
    return 0u;
  }
  return std::char_traits<char>::length(retval);
}



void File::puts(const std::string& str)
{
  int retval = fputs(str.c_str(), mHandle);
  updateFlags();
  HOU_RUNTIME_CHECK(retval != EOF, get_text(SysError::FileWrite));
}



size_t File::read(void* buf, size_t elementSize, size_t bufSize)
{
  size_t count = fread(buf, elementSize, bufSize, mHandle);
  updateFlags();
  HOU_RUNTIME_CHECK(count == bufSize || !error(), get_text(SysError::FileRead));
  return count;
}



void File::write(const void* buf, size_t elementSize, size_t bufSize)
{
  size_t count = fwrite(buf, elementSize, bufSize, mHandle);
  updateFlags();
  HOU_RUNTIME_CHECK(count == bufSize, get_text(SysError::FileWrite));
}



void File::seek(long pos, int origin) const
{
  HOU_RUNTIME_CHECK(fseek(mHandle, pos, origin) == 0
    , get_text(SysError::FileSeek));
}



void File::updateFlags()
{
  mEof = (feof(mHandle) != 0);
  mError = (ferror(mHandle) != 0);
}

}

