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
  /** Default mapping (red to red, green to green, blue to blue, alpha to alpha).
   */
  static const TextureChannelMapping Default;

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
  TextureChannel getR() const;

  /** Gets the channel mapped onto the green channel.
   *
   *  \return the channel mapped onto the green channel.
   */
  TextureChannel getG() const;

  /** Gets the channel mapped onto the blue channel.
   *
   *  \return the channel mapped onto the blue channel.
   */
  TextureChannel getB() const;

  /** Gets the channel mapped onto the alpha channel.
   *
   *  \return the channel mapped onto the alpha channel.
   */
  TextureChannel getA() const;

  /** Sets the channel mapped onto the red channel.
   *
   *  \param channel the channel mapped onto the red channel.
   */
  void setR(TextureChannel channel);

  /** Sets the channel mapped onto the green channel.
   *
   *  \param channel the channel mapped onto the green channel.
   */
  void setG(TextureChannel channel);

  /** Sets the channel mapped onto the blue channel.
   *
   *  \param channel the channel mapped onto the blue channel.
   */
  void setB(TextureChannel channel);

  /** Sets the channel mapped onto the alpha channel.
   *
   *  \param channel the channel mapped onto the alpha channel.
   */
  void setA(TextureChannel channel);

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

/** Outputs a TextureChannelMapping object into a stream.
 *
 *  \param os the output stream.
 *  \param tcm the TextureChannelMapping object.
 *  \return a reference to os.
 */
HOU_GFX_API std::ostream& operator<<(std::ostream& os
  , const TextureChannelMapping& tcm);

}

#endif

