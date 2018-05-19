namespace hou
{

template <typename T>
mesh_t<T>::mesh_t(
  mesh_draw_mode dm, mesh_fill_mode fm, const span<const T>& vertices)
  : mesh(dm, fm, vertices.size())
  , m_vbo(vertices)
{
  m_vao.set_vertex_data(m_vbo, 0u, T::get_vertex_format());
}



template <typename T>
typename mesh_t<T>::vertex_collection mesh_t<T>::get_vertices() const
{
  return m_vbo.get_data();
}



template <typename T>
bool operator==(const mesh_t<T>& lhs, const mesh_t<T>& rhs)
{
  return lhs.get_vertex_count() == rhs.get_vertex_count()
    && lhs.get_draw_mode() == rhs.get_draw_mode()
    && lhs.get_fill_mode() == rhs.get_fill_mode()
    && lhs.get_vertices() == rhs.get_vertices();
}



template <typename T>
bool operator!=(const mesh_t<T>& lhs, const mesh_t<T>& rhs)
{
  return !(lhs == rhs);
}



template <typename T>
bool close(const mesh_t<T>& lhs, const mesh_t<T>& rhs, float acc)
{
  return lhs.get_vertex_count() == rhs.get_vertex_count()
    && lhs.get_draw_mode() == rhs.get_draw_mode()
    && lhs.get_fill_mode() == rhs.get_fill_mode()
    && close(lhs.get_vertices(), rhs.get_vertices(), acc);
}



template <typename T>
std::ostream& operator<<(std::ostream& os, const mesh_t<T>& m)
{
  return os << "{draw_mode = " << m.get_draw_mode()
            << ", fill_mode = " << m.get_fill_mode()
            << ", vertices = " << m.get_vertices() << "}";
}

}  // namespace hou
