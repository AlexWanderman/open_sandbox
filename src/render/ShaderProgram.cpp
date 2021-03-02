#include "ShaderProgram.h"

#include <glm/gtc/type_ptr.hpp>

#include <iostream>

namespace Renderer {
    ShaderProgram::ShaderProgram(const std::string& vertex_shader, const std::string& fragment_shader) {
        GLuint vertex_shader_id;
        if (!create_shader(vertex_shader, GL_VERTEX_SHADER, vertex_shader_id)) {
            std::cerr << "VERTEX SHADER compile-time error" << std::endl;
            return;
        }

        GLuint fragment_shader_id;
        if (!create_shader(fragment_shader, GL_FRAGMENT_SHADER, fragment_shader_id)) {
            std::cerr << "FRAGMENT SHADER compile-time error" << std::endl;
            glDeleteShader(vertex_shader_id);
            return;
        }

        id = glCreateProgram();
        glAttachShader(id, vertex_shader_id);
        glAttachShader(id, fragment_shader_id);
        glLinkProgram(id);

        GLint success;
        glGetProgramiv(id, GL_LINK_STATUS, &success);
        if (!success) {
            GLchar info_log[1024];
            glGetShaderInfoLog(id, 1024, nullptr, info_log);
            std::cerr << "ERROR::SHADER: Link-time error:\n" << info_log << std::endl;
        }
        else {
            is_cmp = true;
        }

        glDeleteShader(vertex_shader_id);
        glDeleteShader(fragment_shader_id);
    }


    bool ShaderProgram::create_shader(const std::string& source, const GLenum shader_type, GLuint& shader_id) {
        shader_id = glCreateShader(shader_type);
        const char* code = source.c_str();
        glShaderSource(shader_id, 1, &code, nullptr);
        glCompileShader(shader_id);

        GLint success;
        glGetShaderiv(shader_id, GL_COMPILE_STATUS, &success);
        if (!success) {
            GLchar info_log[1024];
            glGetShaderInfoLog(shader_id, 1024, nullptr, info_log);
            std::cerr << "ERROR::SHADER: Compile-time error:\n" << info_log << std::endl;
            return false;
        }
        return true;
    }

    ShaderProgram::~ShaderProgram() {
        glDeleteProgram(id);
    }

    void ShaderProgram::use() const {
        glUseProgram(id);
    }

    void ShaderProgram::set_int(const std::string& name, const GLint value)
    {
        glUniform1i(glGetUniformLocation(id, name.c_str()), value);
    }

    void ShaderProgram::set_matrix4(const std::string& name, const glm::mat4& matrix)
    {
        glUniformMatrix4fv(glGetUniformLocation(id, name.c_str()), 1, GL_FALSE, glm::value_ptr(matrix));
    }

    ShaderProgram& ShaderProgram::operator=(ShaderProgram&& shader_program) noexcept {
        glDeleteProgram(id);
        id = shader_program.id;
        is_cmp = shader_program.is_cmp;

        shader_program.id = 0;
        shader_program.is_cmp = false;
        return *this;
    }

    ShaderProgram::ShaderProgram(ShaderProgram&& shader_program) noexcept {
        id = shader_program.id;
        is_cmp = shader_program.is_cmp;

        shader_program.id = 0;
        shader_program.is_cmp = false;
    }
}
