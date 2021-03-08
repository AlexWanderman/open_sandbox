#pragma once

#include <iostream>
#include <array>
#include <vector>

#include <glm/vec2.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "../game/Block.h"

#include "../render/AnimatedSprite.h"
#include "../render/ShaderProgram.h"
#include "../render/Sprite.h"
#include "../render/Texture.h"

#include "../resources/ResourceManager.h"

class Block;

class Game {
public:
    Game(const glm::ivec2& windowSize);
    ~Game();

    void render();
    void update(const uint64_t delta);
    void setKey(const int key, const int action);
    bool init();

private:
    glm::ivec2 m_windowSize;
    std::array<bool, 349> m_keys;
    std::unique_ptr<Block> m_pBlock;

    enum EGameState {
        Active,
        Pause
    };

    EGameState m_eCurrentGameState;
};