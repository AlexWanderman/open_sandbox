#pragma once

#include <glad/glad.h>
#include <string>
#include <glm/mat4x4.hpp>

namespace Renderer {
    class ShaderProgram {
    public:
        ShaderProgram(const std::string& vertex_shader, const std::string& fragment_shader);
        ~ShaderProgram();
        bool is_compiled() const { return is_cmp; }
        void use() const;
        void set_int(const std::string& name, const GLint value);
        void set_matrix4(const std::string& name, const glm::mat4& matrix);

        ShaderProgram() = delete;
        ShaderProgram(const ShaderProgram&) = delete;
        ShaderProgram& operator=(const ShaderProgram&) = delete;
        ShaderProgram& operator=(ShaderProgram&& shaderProgram) noexcept;
        ShaderProgram(ShaderProgram&& shaderProgram) noexcept;

    private:
        bool create_shader(const std::string& source, const GLenum shaderType, GLuint& shaderID);

        bool is_cmp = false;
        GLuint id = 0;
    };
}
