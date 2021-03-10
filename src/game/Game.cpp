#include "../game/Game.h"

Game::Game(const glm::ivec2& windowSize): m_eCurrentGameState(EGameState::Active), m_windowSize(windowSize) {
    m_keys.fill(false);
}

Game::~Game() { }

void Game::render() {
    m_pBlock->render();
}

void Game::update(const uint64_t delta) {
    m_pBlock->update(delta);
}

void Game::setKey(const int key, const int action) {
    m_keys[key] = action;
}

bool Game::init() {
    ResourceManager::loadResources("res/resources.json");

    auto pSpriteShaderProgram = ResourceManager::getShaderProgram("SpriteShader");
    if (!pSpriteShaderProgram) {
        std::cerr << "Can't find shader program: " << "SpriteShader" << std::endl;
        return false;
    }

    auto pColorTextureAtlas = ResourceManager::getTexture("ColorsTextureAtlas");
    if (!pSpriteShaderProgram) {
        std::cerr << "Can't find texture atlas: " << "ColorsTextureAtlas" << std::endl;
        return false;
    }

    auto pColorAnimatedSprite = ResourceManager::getAnimatedSprite("ColorAnimatedSprite");
    if (!pColorAnimatedSprite) {
        std::cerr << "Can't find animated sprite: " << "ColorAnimatedSprite" << std::endl;
        return false;
    }
    pColorAnimatedSprite->setState("ColorAnimatedState");

    m_pBlock = std::make_unique<Block>(pColorAnimatedSprite, glm::vec2(100.f, 100.f));

    glm::mat4 modelMatrix_1 = glm::mat4(1.f);
    modelMatrix_1 = glm::translate(modelMatrix_1, glm::vec3(100.f, 100.f, 0.f));

    glm::mat4 modelMatrix_2 = glm::mat4(1.f);
    modelMatrix_2 = glm::translate(modelMatrix_2, glm::vec3(150.f, 200.f, 0.f));

    glm::mat4 modelMatrix_3 = glm::mat4(1.f);
    modelMatrix_3 = glm::translate(modelMatrix_3, glm::vec3(200.f, 100.f, 0.f));

    glm::mat4 projectionMatrix = glm::ortho(0.f, static_cast<float>(m_windowSize.x), 0.f, static_cast<float>(m_windowSize.y), -100.f, 100.f);

    pSpriteShaderProgram->use();
    pSpriteShaderProgram->setInt("tex", 0);
    pSpriteShaderProgram->setMatrix4("projection_matrix", projectionMatrix);

    return true;
}
