#pragma once

#include <glad/glad.h>

namespace renderEngine {
    class IndexBuffer {
    public:
        IndexBuffer();
        ~IndexBuffer();

        IndexBuffer(const IndexBuffer&) = delete;
        IndexBuffer& operator=(const IndexBuffer&) = delete;

        IndexBuffer& operator=(IndexBuffer&& indexBuffer) noexcept;
        IndexBuffer(IndexBuffer&& indexBuffer) noexcept;

        void init(const void* data, const unsigned int count);
        // void update(const void* data, const unsigned int size) const;
        void bind() const;
        void unbind() const;
        unsigned int getCount() const;

    private:
        GLuint m_id;
        unsigned int m_count;
    };
}
