// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_GL_GL_CONTEXT_HPP
#define HOU_GL_GL_CONTEXT_HPP

#include "hou/cor/non_copyable.hpp"
#include "hou/gl/GlExport.hpp"

#include "hou/gl/GlContextImpl.hpp"
#include "hou/gl/OpenGl.hpp"

#include "hou/mth/rectangle.hpp"

#include <vector>



namespace hou
{

namespace gl
{

class BufferHandle;
class FramebufferHandle;
class ProgramHandle;
class TextureHandle;
class VertexArrayHandle;

class HOU_GL_API Context : public non_copyable
{
private:
  class TrackingData
  {
  public:
    TrackingData();

    uint32_t getBoundBuffer(GLenum target) const;
    void setBoundBuffer(uint32_t uid, GLenum target);

    uint32_t getBoundFramebuffer(GLenum target) const;
    void setBoundFramebuffer(uint32_t uid, GLenum target);

    uint32_t getBoundProgram() const;
    void setBoundProgram(uint32_t uid);

    void resizeTextureVectors(size_t size);

    GLuint getActiveTexture() const;
    void setActiveTexture(GLuint unit);

    uint32_t getBoundTexture() const;
    uint32_t getBoundTexture(GLuint unit) const;
    GLenum getBoundTextureTarget() const;
    GLenum getBoundTextureTarget(GLuint unit) const;
    void setBoundTexture(uint32_t uid, GLenum target);
    void setBoundTexture(uint32_t uid, GLuint unit, GLenum target);

    uint32_t getBoundVertexArray() const;
    void setBoundVertexArray(uint32_t uid);

    const recti& getCurrentViewport() const;
    void setCurrentViewport(const recti& viewport);

  private:
    uint32_t mBoundArrayBuffer;
    uint32_t mBoundElementArrayBuffer;
    uint32_t mBoundDrawFramebuffer;
    uint32_t mBoundReadFramebuffer;
    uint32_t mBoundProgram;
    uint32_t mBoundVertexArray;
    GLuint mActiveTexture;
    std::vector<uint32_t> mBoundTextures;
    std::vector<GLenum> mBoundTextureTargets;
    recti mCurrentViewport;
  };

public:
  static void setCurrent(Context& context, Window& window);
  static void unsetCurrent();
  static Context* getCurrent();

  Context(const ContextSettings& settings, const Window& window);
  Context(const ContextSettings& settings, const Window& window,
    const Context& sharedContext);
  Context(Context&& other);
  ~Context();

  uint32_t getUid() const;
  uint32_t getSharingGroupUid() const;
  bool isCurrent() const;

private:
  Context(const ContextSettings& settings, const Window& window,
    const Context* sharedContext);

private:
  thread_local static Context* sCurrentContext;
  thread_local static uint32_t sCurrentWindowUid;

  prv::ContextImpl mImpl;
  uint32_t mUid;
  uint32_t mSharingGroupUid;
  TrackingData mTrackingData;

public:
  friend HOU_GL_API void bindBuffer(const BufferHandle& buffer, GLenum target);
  friend HOU_GL_API void unbindBuffer(GLenum target);
  friend HOU_GL_API bool isBufferBound(
    const BufferHandle& buffer, GLenum target);
  friend HOU_GL_API bool isBufferBound(GLenum target);

  friend HOU_GL_API void bindFramebuffer(const FramebufferHandle& framebuffer);
  friend HOU_GL_API void bindFramebuffer(
    const FramebufferHandle& framebuffer, GLenum target);
  friend HOU_GL_API void unbindFramebuffer();
  friend HOU_GL_API void unbindFramebuffer(GLenum target);
  friend HOU_GL_API bool isFramebufferBound(
    const FramebufferHandle& framebuffer, GLenum target);
  friend HOU_GL_API bool isFramebufferBound(GLenum target);

  friend HOU_GL_API void bindProgram(const ProgramHandle& program);
  friend HOU_GL_API void unbindProgram();
  friend HOU_GL_API bool isProgramBound(const ProgramHandle& program);
  friend HOU_GL_API bool isProgramBound();

  friend HOU_GL_API void bindTexture(const TextureHandle& texture);
  friend HOU_GL_API void unbindTexture();
  friend HOU_GL_API bool isTextureBound(const TextureHandle& texture);
  friend HOU_GL_API bool isTextureBound();

  friend HOU_GL_API void bindTexture(const TextureHandle& texture, GLuint unit);
  friend HOU_GL_API void unbindTexture(GLuint unit);
  friend HOU_GL_API bool isTextureBound(
    const TextureHandle& texture, GLuint unit);
  friend HOU_GL_API bool isTextureBound(GLuint unit);

  friend HOU_GL_API void setActiveTexture(GLuint unit);
  friend HOU_GL_API GLuint getBoundTextureName();

  friend HOU_GL_API void bindVertexArray(const VertexArrayHandle& vertexArray);
  friend HOU_GL_API void unbindVertexArray();
  friend HOU_GL_API bool isVertexArrayBound(
    const VertexArrayHandle& vertexArray);
  friend HOU_GL_API bool isVertexArrayBound();

  friend HOU_GL_API void setViewport(GLint x, GLint y, GLsizei w, GLsizei h);
};

}  // namespace gl

}  // namespace hou

#endif
