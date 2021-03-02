#include "ResourceManager.h"
#include "../render/ShaderProgram.h"
#include "../render/Texture.h"

#include <sstream>
#include <fstream>
#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#define STBI_ONLY_PNG
#include "stb_image.h"

ResourceManager::ResourceManager(const std::string& executable_path) {
    size_t found = executable_path.find_last_of("/\\");
    path = executable_path.substr(0, found);
}

std::string ResourceManager::getFileString(const std::string& relative_file_path) const {
    std::ifstream f;
    f.open(path + "/" + relative_file_path.c_str(), std::ios::in | std::ios::binary);
    if (!f.is_open()) {
        std::cerr << "Failed to open file: " << relative_file_path << std::endl;
        return std::string{};
    }

    std::stringstream buffer;
    buffer << f.rdbuf();
    return buffer.str();
}

std::shared_ptr<Renderer::ShaderProgram> ResourceManager::loadShaders(const std::string& shader_name, const std::string& vertex_path, const std::string& fragment_path) {
    std::string vertex_string = getFileString(vertex_path);
    if (vertex_string.empty()) {
        std::cerr << "No vertex shader!" << std::endl;
        return nullptr;
    }

    std::string fragmentx_string = getFileString(fragment_path);
    if (fragmentx_string.empty()) {
        std::cerr << "No fragment shader!" << std::endl;
        return nullptr;
    }

    std::shared_ptr<Renderer::ShaderProgram>& new_shader = shader_programs.emplace(shader_name, std::make_shared<Renderer::ShaderProgram>(vertex_string, fragmentx_string)).first->second;
    if (new_shader->is_compiled()) {
        return new_shader;
    }

    std::cerr << "Can't load shader program:\n" << "Vertex: " << vertex_path << "\n" << "Fragment: " << fragment_path << std::endl;

    return nullptr;
}


std::shared_ptr<Renderer::ShaderProgram> ResourceManager::getShaderProgram(const std::string& shader_name) {
    ShaderProgramsMap::const_iterator it = shader_programs.find(shader_name);
    if (it != shader_programs.end()) {
        return it->second;
    }
    std::cerr << "Can't find the shader program: " << shader_name << std::endl;
    return nullptr;
}


std::shared_ptr<Renderer::Texture> ResourceManager::load_texture(const std::string& texture_name, const std::string& texture_path) {
    int channels = 0;
    int width = 0;
    int height = 0;

    stbi_set_flip_vertically_on_load(true);

    unsigned char* pixels = stbi_load(std::string(path + "/" + texture_path).c_str(), &width, &height, &channels, 0);

    if (!pixels) {
        std::cerr << "Can't load image: " << texture_path << std::endl;
        return nullptr;
    }

    std::shared_ptr<Renderer::Texture> new_texture = textures.emplace(
        texture_name,
        std::make_shared<Renderer::Texture>(
            width,
            height,
            pixels,
            channels,
            GL_NEAREST,
            GL_CLAMP_TO_EDGE
        )
    ).first->second;

    stbi_image_free(pixels);
    return new_texture;
}

std::shared_ptr<Renderer::Texture> ResourceManager::get_texture(const std::string& texture_name)
{
    TexturesMap::const_iterator it = textures.find(texture_name);
    if (it != textures.end())
    {
        return it->second;
    }
    std::cerr << "Can't find the texture: " << texture_name << std::endl;
    return nullptr;
}
