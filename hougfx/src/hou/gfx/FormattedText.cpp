#include "hou/gfx/FormattedText.hpp"



namespace hou
{

FormattedText::FormattedText(const std::u32string& text, const Font& font)
  : NonCopyable()
  , mAtlas(nullptr)
  , mMesh(nullptr)
{}



FormattedText::FormattedText(FormattedText&& other)
  : NonCopyable()
  , mAtlas(std::move(other.mAtlas))
  , mMesh(std::move(other.mMesh))
{}



const Texture2Array& FormattedText::getAtlas() const
{
  HOU_EXPECT_DEV(mAtlas != nullptr);
  return *mAtlas;
}



const TextMesh& FormattedText::getMesh() const
{
  HOU_EXPECT_DEV(mMesh != nullptr);
  return *mMesh;
}

}
