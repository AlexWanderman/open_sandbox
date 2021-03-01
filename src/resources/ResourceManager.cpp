#include "ResourceManager.h"
#include "../render/ShaderProgram.h"

#include <sstream>
#include <fstream>
#include <iostream>

ResourceManager::ResourceManager(const std::string& executable_path)
{
    size_t found = executable_path.find_last_of("/\\");
    path = executable_path.substr(0, found);
}

std::string ResourceManager::getFileString(const std::string& relative_file_path) const
{
    std::ifstream f;
    f.open(path + "/" + relative_file_path.c_str(), std::ios::in | std::ios::binary);
    if (!f.is_open())
    {
        std::cerr << "Failed to open file: " << relative_file_path << std::endl;
        return std::string{};
    }

    std::stringstream buffer;
    buffer << f.rdbuf();
    return buffer.str();
}

std::shared_ptr<Renderer::ShaderProgram> ResourceManager::loadShaders(const std::string& shader_name, const std::string& vertex_path, const std::string& fragment_path)
{
    std::string vertex_string = getFileString(vertex_path);
    if (vertex_string.empty())
    {
        std::cerr << "No vertex shader!" << std::endl;
        return nullptr;
    }

    std::string fragmentx_string = getFileString(fragment_path);
    if (fragmentx_string.empty())
    {
        std::cerr << "No fragment shader!" << std::endl;
        return nullptr;
    }

    std::shared_ptr<Renderer::ShaderProgram>& new_shader = shader_programs.emplace(shader_name, std::make_shared<Renderer::ShaderProgram>(vertex_string, fragmentx_string)).first->second;
    if (new_shader->is_compiled())
    {
        return new_shader;
    }

    std::cerr << "Can't load shader program:\n" << "Vertex: " << vertex_path << "\n" << "Fragment: " << fragment_path << std::endl;

    return nullptr;
}


std::shared_ptr<Renderer::ShaderProgram> ResourceManager::getShaderProgram(const std::string& shader_name)
{
    ShaderProgramsMap::const_iterator it = shader_programs.find(shader_name);
    if (it != shader_programs.end())
    {
        return it->second;
    }
    std::cerr << "Can't find the shader program: " << shader_name << std::endl;
    return nullptr;
}
