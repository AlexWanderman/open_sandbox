#pragma once

#include <glad/glad.h>
#include <string>

namespace Renderer {
    class Texture {
    public:
        Texture(const GLuint width, GLuint height,
            const unsigned char* data,
            const unsigned int channels = 4,
            const GLenum filter = GL_LINEAR,
            const GLenum wrapMode = GL_CLAMP_TO_EDGE);

        Texture() = delete;
        Texture(const Texture&) = delete;
        Texture& operator=(const Texture&) = delete;
        Texture& operator=(Texture&& texture2d) noexcept;
        Texture(Texture&& texture2d) noexcept;
        ~Texture();

        void bind() const;

    private:
        GLuint id;
        GLenum mode;
        unsigned int width;
        unsigned int height;
    };
}
