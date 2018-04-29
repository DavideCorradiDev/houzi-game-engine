namespace hou
{

template <typename T>
mesh_t<T>::mesh_t(
  mesh_draw_mode drawMode, mesh_fill_mode fillMode, const span<const T>& vertices)
  : mesh(drawMode, fillMode, vertices.size())
  , m_vbo(vertices)
{
  m_vao.set_vertex_data(m_vbo, 0u, T::get_vertex_format());
}



template <typename T>
mesh_t<T>::mesh_t(mesh_t&& other)
  : mesh(std::move(other))
  , m_vbo(std::move(other.m_vbo))
{}



template <typename T>
typename mesh_t<T>::vertex_collection mesh_t<T>::getVertices() const
{
  return m_vbo.get_data();
}



template <typename T>
bool operator==(const mesh_t<T>& lhs, const mesh_t<T>& rhs)
{
  return lhs.get_vertex_count() == rhs.get_vertex_count()
    && lhs.get_draw_mode() == rhs.get_draw_mode()
    && lhs.get_fill_mode() == rhs.get_fill_mode()
    && lhs.getVertices() == rhs.getVertices();
}



template <typename T>
bool operator!=(const mesh_t<T>& lhs, const mesh_t<T>& rhs)
{
  return !(lhs == rhs);
}



template <typename T>
bool close(
  const mesh_t<T>& lhs, const mesh_t<T>& rhs, typename T::comparison_type acc)
{
  return lhs.get_vertex_count() == rhs.get_vertex_count()
    && lhs.get_draw_mode() == rhs.get_draw_mode()
    && lhs.get_fill_mode() == rhs.get_fill_mode()
    && close(lhs.getVertices(), rhs.getVertices(), acc);
}



template <typename T>
std::ostream& operator<<(std::ostream& os, const mesh_t<T>& m)
{
  return os << "{DrawMode = " << m.get_draw_mode()
            << ", FillMode = " << m.get_fill_mode()
            << ", Vertices = " << m.getVertices() << "}";
}

}  // namespace hou
