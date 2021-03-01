#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "render/ShaderProgram.h"
#include "resources/ResourceManager.h"

GLfloat point[] = {
     0.0f,  0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
    -0.5f, -0.5f, 0.0f
};

GLfloat color[] = {
    1.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 1.0f
};

int g_windowSizeX = 1280;
int g_windowSizeY = 720;

void glfwWindowSizeCallback(GLFWwindow* window, int w, int h) {
    // w - width, h - heigth
    g_windowSizeX = w;
    g_windowSizeY = h;
    glViewport(0, 0, g_windowSizeX, g_windowSizeY);
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
    window = glfwCreateWindow(g_windowSizeX, g_windowSizeY, "Open Sandbox", nullptr, nullptr);
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

        GLuint point_vbo = 0;
        glGenBuffers(1, &point_vbo);
        glBindBuffer(GL_ARRAY_BUFFER, point_vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(point), &point, GL_STATIC_DRAW);

        GLuint color_vbo = 0;
        glGenBuffers(1, &color_vbo);
        glBindBuffer(GL_ARRAY_BUFFER, color_vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(color), &color, GL_STATIC_DRAW);

        GLuint vao = 0;
        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);

        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, point_vbo);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

        glEnableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, color_vbo);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window)) {
            /* Render here */
            glClear(GL_COLOR_BUFFER_BIT);

            default_shader_program->use();
            glBindVertexArray(vao);
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
