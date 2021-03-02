#pragma once

#include <string>
#include <memory>
#include <map>

namespace Renderer {
    class ShaderProgram;
    class Texture;
}


class ResourceManager {
public:
    ResourceManager(const std::string& executable_path);
    ~ResourceManager() = default;

    ResourceManager(const ResourceManager&) = delete;
    ResourceManager& operator=(const ResourceManager&) = delete;
    ResourceManager& operator=(ResourceManager&&) = delete;
    ResourceManager(ResourceManager&&) = delete;

    std::shared_ptr<Renderer::ShaderProgram> loadShaders(const std::string& shader_name, const std::string& vertex_path, const std::string& fragment_path);
    std::shared_ptr<Renderer::ShaderProgram> getShaderProgram(const std::string& shader_name);
    std::shared_ptr<Renderer::Texture> load_texture(const std::string& texture_name, const std::string& texture_path);
    std::shared_ptr<Renderer::Texture> get_texture(const std::string& texture_name);


private:
    std::string getFileString(const std::string& relative_file_path) const;

    typedef std::map<const std::string, std::shared_ptr<Renderer::ShaderProgram>> ShaderProgramsMap;
    ShaderProgramsMap shader_programs;

    typedef std::map<const std::string, std::shared_ptr<Renderer::Texture>> TexturesMap;
    TexturesMap textures;

    std::string path;
};
