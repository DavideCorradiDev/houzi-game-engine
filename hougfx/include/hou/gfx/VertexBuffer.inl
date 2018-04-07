// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license. See license.md for more details.

namespace hou
{

template <typename Container, typename Enable>
VertexBuffer::VertexBuffer(
  const Container& data, VertexBufferAttributes attributes)
  : VertexBuffer(data.size() * sizeof(typename Container::value_type),
      reinterpret_cast<const void*>(data.data()), attributes)
{}



template <typename Container, typename Enable>
void VertexBuffer::setData(const Container& data)
{
  uint sizeBytes = data.size() * sizeof(typename Container::value_type);
  HOU_EXPECT(sizeBytes == mByteCount);
  setSubData(0u, data);
}



template <typename Container, typename Enable>
void VertexBuffer::setSubData(uint offset, const Container& data)
{
  uint offsetBytes = offset * sizeof(typename Container::value_type);
  uint sizeBytes = data.size() * sizeof(typename Container::value_type);
  HOU_EXPECT(offsetBytes + sizeBytes <= mByteCount);
  gl::setBufferSubData(mHandle, static_cast<GLintptr>(offsetBytes),
    static_cast<GLsizei>(sizeBytes),
    reinterpret_cast<const GLvoid*>(data.data()));
}



template <typename DataType>
std::vector<DataType> VertexBuffer::getData() const
{
  HOU_EXPECT(mByteCount % sizeof(DataType) == 0u);
  return getSubData<DataType>(0u, mByteCount / sizeof(DataType));
}



template <typename DataType>
std::vector<DataType> VertexBuffer::getSubData(uint offset, uint size) const
{
  uint offsetBytes = offset * sizeof(DataType);
  uint sizeBytes = size * sizeof(DataType);
  HOU_EXPECT(offsetBytes + sizeBytes <= mByteCount);
  std::vector<DataType> dataOut(size, DataType());
  gl::getBufferSubData(mHandle, static_cast<GLintptr>(offsetBytes),
    static_cast<uint>(sizeBytes), reinterpret_cast<GLvoid*>(dataOut.data()));
  return dataOut;
}

}  // namespace hou
