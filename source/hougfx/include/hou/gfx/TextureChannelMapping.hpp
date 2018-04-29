// Licensed under the MIT license.

#ifndef HOU_GFX_TEXTURE_CHANNEL_MAPPING_HPP
#define HOU_GFX_TEXTURE_CHANNEL_MAPPING_HPP

#include "hou/gfx/GfxExport.hpp"

#include "hou/gfx/TextureChannel.hpp"

#include "hou/cor/basic_types.hpp"



namespace hou
{

/** Defines a channel mapping for a texture.
 *
 *  A channel mapping allows to efficiently swap texture channel or to replace
 *  them with constant zero or one channels when the texture is passed to a
 *  shader.
 */
class HOU_GFX_API TextureChannelMapping
{
public:
  /** default mapping (red to red, green to green, blue to blue, alpha to alpha).
   */
  static const TextureChannelMapping standard;

  /** Luminosity mapping (red to red, red to green, red to blue, one to alpha).
   */
  static const TextureChannelMapping Luminosity;

  /** Alpha mapping (one to red, one to green, one to blue, red to alpha).
   */
  static const TextureChannelMapping Alpha;

public:
  /** Creates a TextureChannelMapping with the given mappings for the four
   *  channels.
   *
   *  \param r the channel mapped onto the red channel.
   *  \param g the channel mapped onto the green channel.
   *  \param b the channel mapped onto the blue channel.
   *  \param a the channel mapped onto the alpha channel.
   */
  TextureChannelMapping(TextureChannel r, TextureChannel g, TextureChannel b
    , TextureChannel a);

  /** Gets the channel mapped onto the red channel.
   *
   *  \return the channel mapped onto the red channel.
   */
  TextureChannel get_r() const;

  /** Gets the channel mapped onto the green channel.
   *
   *  \return the channel mapped onto the green channel.
   */
  TextureChannel get_g() const;

  /** Gets the channel mapped onto the blue channel.
   *
   *  \return the channel mapped onto the blue channel.
   */
  TextureChannel get_b() const;

  /** Gets the channel mapped onto the alpha channel.
   *
   *  \return the channel mapped onto the alpha channel.
   */
  TextureChannel get_a() const;

  /** Sets the channel mapped onto the red channel.
   *
   *  \param channel the channel mapped onto the red channel.
   */
  void set_r(TextureChannel channel);

  /** Sets the channel mapped onto the green channel.
   *
   *  \param channel the channel mapped onto the green channel.
   */
  void set_g(TextureChannel channel);

  /** Sets the channel mapped onto the blue channel.
   *
   *  \param channel the channel mapped onto the blue channel.
   */
  void set_b(TextureChannel channel);

  /** Sets the channel mapped onto the alpha channel.
   *
   *  \param channel the channel mapped onto the alpha channel.
   */
  void set_a(TextureChannel channel);

private:
  TextureChannel mR;
  TextureChannel mG;
  TextureChannel mB;
  TextureChannel mA;
};

/** Checks if two TextureChannelMapping objects are equal.
 *
 *  \param lhs the left operand.
 *  \param rhs the right operand.
 *  \return true if lhs and rhs are equal.
 */
HOU_GFX_API bool operator==(const TextureChannelMapping& lhs
  , const TextureChannelMapping& rhs);

/** Checks if two TextureChannelMapping objects are not equal.
 *
 *  \param lhs the left operand.
 *  \param rhs the right operand.
 *  \return true if lhs and rhs are not equal.
 */
HOU_GFX_API bool operator!=(const TextureChannelMapping& lhs
  , const TextureChannelMapping& rhs);

/** Outputs a TextureChannelMapping object into a ph_stream.
 *
 *  \param os the output ph_stream.
 *  \param tcm the TextureChannelMapping object.
 *  \return a reference to os.
 */
HOU_GFX_API std::ostream& operator<<(std::ostream& os
  , const TextureChannelMapping& tcm);

}

#endif

