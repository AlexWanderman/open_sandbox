#include "Texture.h"

namespace Renderer {

    Texture::Texture(const GLuint width, GLuint height,
        const unsigned char* data,
        const unsigned int channels,
        const GLenum filter,
        const GLenum wrap_mode)
        : width(width)
        , height(height)

    {
        mode = channels == 4 ? GL_RGBA : GL_RGB;

        glGenTextures(1, &id);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, id);
        glTexImage2D(GL_TEXTURE_2D, 0, mode, width, height, 0, mode, GL_UNSIGNED_BYTE, data);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap_mode);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap_mode);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter);
        glGenerateMipmap(GL_TEXTURE_2D);

        glBindTexture(GL_TEXTURE_2D, 0);
    }

    Texture& Texture::operator=(Texture&& texture) noexcept {
        glDeleteTextures(1, &id);
        id = texture.id;
        texture.id = 0;
        mode = texture.mode;
        width = texture.width;
        height = texture.height;
        return *this;
    }

    Texture::Texture(Texture&& texture) noexcept {
        id = texture.id;
        texture.id = 0;
        mode = texture.mode;
        width = texture.width;
        height = texture.height;
    }

    Texture::~Texture() {
        glDeleteTextures(1, &id);
    }

    void Texture::bind() const {
        glBindTexture(GL_TEXTURE_2D, id);
    }
}
