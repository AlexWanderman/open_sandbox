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
    auto pDefaultShaderProgram = ResourceManager::loadShaders("DefaultShader", "res/shaders/vertex.txt", "res/shaders/fragment.txt");
    if (!pDefaultShaderProgram) {
        std::cerr << "Can't create shader program: " << "DefaultShader" << std::endl;
        return false;
    }

    auto pSpriteShaderProgram = ResourceManager::loadShaders("SpriteShader", "res/shaders/vertex_sprite.txt", "res/shaders/fragment_sprite.txt");
    if (!pSpriteShaderProgram) {
        std::cerr << "Can't create shader program: " << "SpriteShader" << std::endl;
        return false;
    }

    pDefaultShaderProgram->use();
    pDefaultShaderProgram->setInt("tex", 0);

    glm::mat4 modelMatrix_1 = glm::mat4(1.f);
    modelMatrix_1 = glm::translate(modelMatrix_1, glm::vec3(100.f, 100.f, 0.f));

    glm::mat4 modelMatrix_2 = glm::mat4(1.f);
    modelMatrix_2 = glm::translate(modelMatrix_2, glm::vec3(150.f, 200.f, 0.f));

    glm::mat4 modelMatrix_3 = glm::mat4(1.f);
    modelMatrix_3 = glm::translate(modelMatrix_3, glm::vec3(200.f, 100.f, 0.f));

    glm::mat4 projectionMatrix = glm::ortho(0.f, static_cast<float>(m_windowSize.x), 0.f, static_cast<float>(m_windowSize.y), -100.f, 100.f);

    pDefaultShaderProgram->setMatrix4("projection_matrix", projectionMatrix);

    pSpriteShaderProgram->use();
    pSpriteShaderProgram->setInt("tex", 0);
    pSpriteShaderProgram->setMatrix4("projection_matrix", projectionMatrix);

    std::vector<std::string> subColorTexturesNames;

    for (int i = 0; i < 64; i++) {
        std::string n = "color_" + std::to_string(i+1);
        subColorTexturesNames.push_back(n);
    }

    auto pColorTextureAtlas = ResourceManager::loadTextureAtlas("ColorsTextureAtlas", "res/textures/basic_colors.png", std::move(subColorTexturesNames), 16, 16);

    auto pColorAnimatedSprite = ResourceManager::loadAnimatedSprite("ColorAnimatedSprite", "ColorsTextureAtlas", "SpriteShader", 100, 100, "color_1");
    pColorAnimatedSprite->setPosition(glm::vec2(500, 100));

    std::vector<std::pair<std::string, uint64_t>> colorAnimatedState{
            std::make_pair<std::string, uint64_t>("color_1", 1e9),
            std::make_pair<std::string, uint64_t>("color_16", 1e9),
            std::make_pair<std::string, uint64_t>("color_17", 1e9),
            std::make_pair<std::string, uint64_t>("color_32", 1e9),
            std::make_pair<std::string, uint64_t>("color_33", 1e9),
            std::make_pair<std::string, uint64_t>("color_48", 1e9),
            std::make_pair<std::string, uint64_t>("color_49", 1e9),
            std::make_pair<std::string, uint64_t>("color_64", 1e9),
    };
    pColorAnimatedSprite->insertState("colorAnimatedState", std::move(colorAnimatedState));
    pColorAnimatedSprite->setState("colorAnimatedState");

    m_pBlock = std::make_unique<Block>(pColorAnimatedSprite, glm::vec2(100.f, 100.f));

    return true;
}
