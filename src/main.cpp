#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/vec2.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>

#include "render/ShaderProgram.h"
#include "render/Texture.h"
#include "resources/ResourceManager.h"

GLfloat point[] = {
     0.0f,  50.f, 0.0f,
     50.f, -50.f, 0.0f,
    -50.f, -50.f, 0.0f
};

GLfloat color[] = {
    1.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 1.0f
};

GLfloat tex_coord[] = {
    0.5f, 1.0f,
    1.0f, 0.0f,
    0.0f, 0.0f
};

glm::ivec2 window_size(1280, 720);

void glfwWindowSizeCallback(GLFWwindow* window, int w, int h) {
    // w - width, h - heigth
    window_size.x = w;
    window_size.y = h;
    glViewport(0, 0, window_size.x, window_size.y);
}

void glfwKeyCallback(GLFWwindow* window, int k, int s, int a, int m) {
    // k - key, s - scancode, a - action, m - mode
    if (k == GLFW_KEY_ESCAPE && a == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
}

int main(int argc, char** argv) {
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit()) {
        std::cout << "ERROR: glfwInit failed!" << std::endl;
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(window_size.x, window_size.y, "Open Sandbox", nullptr, nullptr);
    if (!window) {
        glfwTerminate();
        std::cout << "ERROR: glfwCreateWindow failed!" << std::endl;
        return -1;
    }

    /* Callback registration */
    glfwSetWindowSizeCallback(window, glfwWindowSizeCallback);
    glfwSetKeyCallback(window, glfwKeyCallback);

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    if (!gladLoadGL()) {
        std::cout << "ERROR: glfwMakeContextCurrent or gladLoadGL failed!" << std::endl;
        return -1;
    }

    std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;
    std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;

    glClearColor(.5, .5, 1, 1);

    {
        ResourceManager resource_manager(argv[0]);
        auto default_shader_program = resource_manager.loadShaders("DefaultShader", "res/shaders/vertex.txt", "res/shaders/fragment.txt");

        if (!default_shader_program)
        {
            std::cerr << "Can't create shader program: " << "DefaultShader" << std::endl;
            return -1;
        }

        auto tex = resource_manager.load_texture("test_1", "res/textures/texture_test_1.png");

        GLuint point_vbo = 0;
        glGenBuffers(1, &point_vbo);
        glBindBuffer(GL_ARRAY_BUFFER, point_vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(point), &point, GL_STATIC_DRAW);

        GLuint color_vbo = 0;
        glGenBuffers(1, &color_vbo);
        glBindBuffer(GL_ARRAY_BUFFER, color_vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(color), &color, GL_STATIC_DRAW);

        GLuint tex_coord_vbo = 0;
        glGenBuffers(1, &tex_coord_vbo);
        glBindBuffer(GL_ARRAY_BUFFER, tex_coord_vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(tex_coord), &tex_coord, GL_STATIC_DRAW);

        GLuint vao = 0;
        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);

        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, point_vbo);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

        glEnableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, color_vbo);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

        glEnableVertexAttribArray(2);
        glBindBuffer(GL_ARRAY_BUFFER, tex_coord_vbo);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, nullptr);

        default_shader_program->use();
        default_shader_program->set_int("tex", 0);


        glm::mat4x4 model_matrix_1 = glm::mat4(1.f);
        model_matrix_1 = glm::translate(model_matrix_1, glm::vec3(100.f, 100.f, 0.f));

        glm::mat4x4 model_matrix_2 = glm::mat4(1.f);
        model_matrix_2 = glm::translate(model_matrix_2, glm::vec3(200.f, 100.f, 0.f));

        glm::mat4x4 model_matrix_3 = glm::mat4(1.f);
        model_matrix_3 = glm::translate(model_matrix_3, glm::vec3(150.f, 200.f, 0.f));

        glm::mat4 projection_matrix = glm::ortho(0.f, static_cast<float>(window_size.x), 0.f, static_cast<float>(window_size.y), -100.f, 100.f);

        default_shader_program->set_matrix4("projection_matrix", projection_matrix);

        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window)) {
            /* Render here */
            glClear(GL_COLOR_BUFFER_BIT);

            default_shader_program->use();
            glBindVertexArray(vao);
            tex->bind();

            default_shader_program->set_matrix4("model_matrix", model_matrix_1);
            glDrawArrays(GL_TRIANGLES, 0, 3);

            default_shader_program->set_matrix4("model_matrix", model_matrix_2);
            glDrawArrays(GL_TRIANGLES, 0, 3);

            default_shader_program->set_matrix4("model_matrix", model_matrix_3);
            glDrawArrays(GL_TRIANGLES, 0, 3);

            /* Swap front and back buffers */
            glfwSwapBuffers(window);

            /* Poll for and process events */
            glfwPollEvents();
        }
    }

    glfwTerminate();
    return 0;
}
