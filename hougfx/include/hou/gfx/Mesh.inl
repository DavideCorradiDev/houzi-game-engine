namespace hou
{

template <typename VertexType>
void Mesh<VertexType>::bind(const Mesh& mesh)
{
  VertexArray::bind(mesh.mVao);
}



template <typename VertexType>
void Mesh<VertexType>::draw(const Mesh& mesh)
{
  bind(mesh);
  gl::setPolygonMode(GL_FRONT_AND_BACK, static_cast<GLenum>(mesh.mFillMode));
  gl::drawArrays(static_cast<GLenum>(mesh.mDrawMode), 0, mesh.mVertexCount);
}



template <typename VertexType>
Mesh<VertexType>::Mesh(MeshDrawMode drawMode, MeshFillMode fillMode,
  const Span<const VertexType>& vertices)
  : NonCopyable()
  , mDrawMode(drawMode)
  , mFillMode(fillMode)
  , mVertexCount(vertices.size())
  , mVbo(vertices, VertexBufferAttributes::None)
  , mVao()
{
  mVao.setVertexData(mVbo, 0u, VertexType::getVertexFormat());
}



template <typename VertexType>
Mesh<VertexType>::Mesh(Mesh&& other)
  : NonCopyable()
  , mDrawMode(other.mDrawMode)
  , mFillMode(other.mFillMode)
  , mVertexCount(other.mVertexCount)
  , mVbo(std::move(other.mVbo))
  , mVao(std::move(other.mVao))
{}



template <typename VertexType>
MeshDrawMode Mesh<VertexType>::getDrawMode() const
{
  return mDrawMode;
}



template <typename VertexType>
MeshFillMode Mesh<VertexType>::getFillMode() const
{
  return mFillMode;
}



template <typename VertexType>
uint Mesh<VertexType>::getVertexCount() const
{
  return mVertexCount;
}



template <typename VertexType>
std::vector<VertexType> Mesh<VertexType>::getVertices() const
{
  return mVbo.getData<VertexType>();
}



template <typename VertexType>
bool Mesh<VertexType>::isBound() const
{
  return mVao.isBound();
}



template <typename VertexType>
bool operator==(const Mesh<VertexType>& lhs, const Mesh<VertexType>& rhs)
{
  return lhs.getVertexCount() == rhs.getVertexCount()
    && lhs.getDrawMode() == rhs.getDrawMode()
    && lhs.getFillMode() == rhs.getFillMode()
    && lhs.getVertices() == rhs.getVertices();
}



template <typename VertexType>
bool operator!=(const Mesh<VertexType>& lhs, const Mesh<VertexType>& rhs)
{
  return !(lhs == rhs);
}



template <typename VertexType>
bool close(const Mesh<VertexType>& lhs, const Mesh<VertexType>& rhs,
  typename VertexType::value_type acc)
{
  return lhs.getVertexCount() == rhs.getVertexCount()
    && lhs.getDrawMode() == rhs.getDrawMode()
    && lhs.getFillMode() == rhs.getFillMode()
    && close(lhs.getVertices(), rhs.getVertices(), acc);
}



template <typename VertexType>
std::ostream& operator<<(std::ostream& os, const Mesh<VertexType>& m)
{
  return os << "{DrawMode = " << m.getDrawMode()
            << ", FillMode = " << m.getFillMode()
            << ", Vertices = " << m.getVertices() << "}";
}

}  // namespace hou
