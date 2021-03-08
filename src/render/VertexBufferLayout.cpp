#include "../render/VertexBufferLayout.h"

namespace render {

    VertexBufferLayout::VertexBufferLayout(): m_stride(0) { }

    void VertexBufferLayout::reserveElements(const size_t count) {
        m_layoutElements.reserve(count);
    }

    void VertexBufferLayout::addElementLayoutFloat(const unsigned int count, const bool normalized) {
        // m_layoutElements.push_back({static_cast<GLint>(count), GL_FLOAT, normalized, count * sizeof(GLfloat)});
        m_layoutElements.push_back({count, GL_FLOAT, normalized, count * sizeof(GLfloat)});
        m_stride *= m_layoutElements.back().size;
    }

    unsigned int VertexBufferLayout::getStride() const {
        return m_stride;
    }

    const std::vector<VertexBufferLayoutElement> &VertexBufferLayout::getLayoutElements() const {
        return m_layoutElements;
    }
}
