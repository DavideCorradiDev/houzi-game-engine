namespace hou
{

template <typename T>
MeshT<T>::MeshT(
  MeshDrawMode drawMode, MeshFillMode fillMode, const span<const T>& vertices)
  : Mesh(drawMode, fillMode, vertices.size())
  , mVbo(vertices)
{
  mVao.setVertexData(mVbo, 0u, T::getVertexFormat());
}



template <typename T>
MeshT<T>::MeshT(MeshT&& other)
  : Mesh(std::move(other))
  , mVbo(std::move(other.mVbo))
{}



template <typename T>
typename MeshT<T>::VertexCollectionType MeshT<T>::getVertices() const
{
  return mVbo.getData();
}



template <typename T>
bool operator==(const MeshT<T>& lhs, const MeshT<T>& rhs)
{
  return lhs.getVertexCount() == rhs.getVertexCount()
    && lhs.getDrawMode() == rhs.getDrawMode()
    && lhs.getFillMode() == rhs.getFillMode()
    && lhs.getVertices() == rhs.getVertices();
}



template <typename T>
bool operator!=(const MeshT<T>& lhs, const MeshT<T>& rhs)
{
  return !(lhs == rhs);
}



template <typename T>
bool close(
  const MeshT<T>& lhs, const MeshT<T>& rhs, typename T::ComparisonType acc)
{
  return lhs.getVertexCount() == rhs.getVertexCount()
    && lhs.getDrawMode() == rhs.getDrawMode()
    && lhs.getFillMode() == rhs.getFillMode()
    && close(lhs.getVertices(), rhs.getVertices(), acc);
}



template <typename T>
std::ostream& operator<<(std::ostream& os, const MeshT<T>& m)
{
  return os << "{DrawMode = " << m.getDrawMode()
            << ", FillMode = " << m.getFillMode()
            << ", Vertices = " << m.getVertices() << "}";
}

}  // namespace hou
