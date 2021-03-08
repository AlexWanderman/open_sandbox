#include "../game/Block.h"

Block::Block(std::shared_ptr<render::AnimatedSprite> pSprite, const glm::vec2 &position):
    m_pSprite(std::move(pSprite)),
    m_position(position)
{
    m_pSprite->setPosition(position);
}

void Block::render() const {
    m_pSprite->render();
}

void Block::update(const uint64_t delta) {
    m_pSprite->update(delta);
}
