// Licensed under the MIT license.

#ifndef HOU_GFX_TEXTURE_CHANNEL_MAPPING_HPP
#define HOU_GFX_TEXTURE_CHANNEL_MAPPING_HPP

#include "hou/gfx/gfx_export.hpp"

#include "hou/gfx/texture_channel.hpp"

#include "hou/cor/basic_types.hpp"



namespace hou
{

/** Defines a channel mapping for a texture.
 *
 * A channel mapping allows to efficiently swap texture channel or to replace
 * them with constant zero or one channels when the texture is passed to a
 * shader.
 */
class HOU_GFX_API texture_channel_mapping
{
public:
  /** Default mapping (red to red, green to green, blue to blue, alpha to
   * alpha).
   */
  static const texture_channel_mapping standard;

  /** Luminosity mapping (red to red, red to green, red to blue, one to alpha).
   */
  static const texture_channel_mapping luminosity;

  /** Alpha mapping (one to red, one to green, one to blue, red to alpha).
   */
  static const texture_channel_mapping alpha;

public:
  /** Creates a texture_channel_mapping with the given mappings for the four
   * channels.
   *
   * \param r the channel mapped onto the red channel.
   *
   * \param g the channel mapped onto the green channel.
   *
   * \param b the channel mapped onto the blue channel.
   *
   * \param a the channel mapped onto the alpha channel.
   */
  texture_channel_mapping(
    texture_channel r, texture_channel g, texture_channel b, texture_channel a);

  /** Gets the channel mapped onto the red channel.
   *
   * \return the channel mapped onto the red channel.
   */
  texture_channel get_r() const;

  /** Gets the channel mapped onto the green channel.
   *
   * \return the channel mapped onto the green channel.
   */
  texture_channel get_g() const;

  /** Gets the channel mapped onto the blue channel.
   *
   * \return the channel mapped onto the blue channel.
   */
  texture_channel get_b() const;

  /** Gets the channel mapped onto the alpha channel.
   *
   * \return the channel mapped onto the alpha channel.
   */
  texture_channel get_a() const;

  /** Sets the channel mapped onto the red channel.
   *
   * \param channel the channel mapped onto the red channel.
   */
  void set_r(texture_channel channel);

  /** Sets the channel mapped onto the green channel.
   *
   * \param channel the channel mapped onto the green channel.
   */
  void set_g(texture_channel channel);

  /** Sets the channel mapped onto the blue channel.
   *
   * \param channel the channel mapped onto the blue channel.
   */
  void set_b(texture_channel channel);

  /** Sets the channel mapped onto the alpha channel.
   *
   * \param channel the channel mapped onto the alpha channel.
   */
  void set_a(texture_channel channel);

private:
  texture_channel m_r;
  texture_channel m_g;
  texture_channel m_b;
  texture_channel m_a;
};

/** Checks if two texture_channel_mapping objects are equal.
 *
 * \param lhs the left operand.
 *
 * \param rhs the right operand.
 *
 * \return true if lhs and rhs are equal.
 */
HOU_GFX_API bool operator==(
  const texture_channel_mapping& lhs, const texture_channel_mapping& rhs);

/** Checks if two texture_channel_mapping objects are not equal.
 *
 * \param lhs the left operand.
 *
 * \param rhs the right operand.
 *
 * \return true if lhs and rhs are not equal.
 */
HOU_GFX_API bool operator!=(
  const texture_channel_mapping& lhs, const texture_channel_mapping& rhs);

/** Outputs a texture_channel_mapping object into a stream.
 *
 * \param os the output stream.
 *
 * \param tcm the texture_channel_mapping object.
 *
 * \return a reference to os.
 */
HOU_GFX_API std::ostream& operator<<(
  std::ostream& os, const texture_channel_mapping& tcm);

}  // namespace hou

#endif
