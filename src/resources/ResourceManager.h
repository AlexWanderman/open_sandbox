#pragma once

#include <string>
#include <memory>
#include <map>
#include <vector>

namespace render {
    class ShaderProgram;
    class Texture2D;
    class Sprite;
    class AnimatedSprite;
}


class ResourceManager {
public:
    ResourceManager(const std::string& executablePath);
    ~ResourceManager() = default;

    ResourceManager(const ResourceManager&) = delete;
    ResourceManager& operator=(const ResourceManager&) = delete;
    ResourceManager& operator=(ResourceManager&&) = delete;
    ResourceManager(ResourceManager&&) = delete;

    std::shared_ptr<render::ShaderProgram> loadShaders(const std::string& shaderName, const std::string& vertexPath, const std::string& fragmentPath);
    std::shared_ptr<render::ShaderProgram> getShaderProgram(const std::string& shaderName);
    std::shared_ptr<render::Texture2D> loadTexture(const std::string& textureName, const std::string& texturePath);
    std::shared_ptr<render::Texture2D> getTexture(const std::string& textureName);

    std::shared_ptr<render::Sprite> loadSprite(const std::string& spriteName,
        const std::string& textureName,
        const std::string& shaderName,
        const unsigned int spriteWidth,
        const unsigned int spriteHeight,
        const std::string& subTextureName = "default");
    std::shared_ptr<render::Sprite> getSprite(const std::string& spriteName);

    std::shared_ptr<render::AnimatedSprite> loadAnimatedSprite(const std::string& spriteName,
        const std::string& textureName,
        const std::string& shaderName,
        const unsigned int spriteWidth,
        const unsigned int spriteHeight,
        const std::string& subTextureName = "default");
    std::shared_ptr<render::AnimatedSprite> getAnimatedSprite(const std::string& spriteName);

    std::shared_ptr<render::Texture2D> loadTextureAtlas(std::string textureName,
        std::string texturePath,
        std::vector<std::string> subTextures,
        const unsigned int subTextureWidth,
        const unsigned int subTextureHeight);

private:
    std::string getFileString(const std::string& relativeFilePath) const;

    typedef std::map<const std::string, std::shared_ptr<render::ShaderProgram>> ShaderProgramsMap;
    ShaderProgramsMap m_shaderPrograms;

    typedef std::map<const std::string, std::shared_ptr<render::Texture2D>> TexturesMap;
    TexturesMap m_textures;

    typedef std::map<const std::string, std::shared_ptr<render::Sprite>> SpritesMap;
    SpritesMap m_sprites;

    typedef std::map<const std::string, std::shared_ptr<render::AnimatedSprite>> AnimatedSpritesMap;
    AnimatedSpritesMap m_animatedSprites;

    std::string m_path;
};
