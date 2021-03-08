#pragma once

#include <vector>
#include <glad/glad.h>

namespace render {
    struct VertexBufferLayoutElement {
        // GLint count;
        GLuint count;
        GLenum type;
        GLboolean normalized;
        unsigned int size;
    };

    class VertexBufferLayout {
    public:
        VertexBufferLayout();

        void reserveElements(const size_t count);
        void addElementLayoutFloat(const unsigned int count, const bool normalized);
        unsigned int getStride() const;
        const std::vector<VertexBufferLayoutElement>& getLayoutElements() const;
    private:
        std::vector<VertexBufferLayoutElement> m_layoutElements;
        unsigned int m_stride;
    };
}
