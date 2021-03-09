#pragma once

#include <string>

#include "../render/VertexArray.h"
#include "../render/VertexBuffer.h"
#include "../render/ShaderProgram.h"
#include "../render/IndexBuffer.h"

namespace renderEngine {
    class Renderer {
    public:
        static void draw(const VertexArray& vertexArray, const IndexBuffer& indexBuffer, const ShaderProgram& shader);
        static void setClearColor(float r, float g, float b, float a);
        static void clear();
        static void setViewport(unsigned int leftOffset, unsigned int bottomOffset, unsigned int width, unsigned int height);

        static std::string getRendererStr();
        static std::string getVersionStr();
    };
}