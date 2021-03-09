#pragma once

#include <memory>
#include <glm/vec2.hpp>
#include "../render/AnimatedSprite.h"

namespace renderEngine {
    class AnimatedSprite;
}

class Block {
public:
    Block(std::shared_ptr<renderEngine::AnimatedSprite> pSprite, const glm::vec2& position);

    void render() const;
    void update(const uint64_t delta);

private:
    std::shared_ptr<renderEngine::AnimatedSprite> m_pSprite;
    glm::vec2 m_position;
};
