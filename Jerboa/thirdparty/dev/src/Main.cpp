#include <iostream>
#include <memory>

#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "GLFW/glfw3.h"

GLFWwindow *createWindow(int width, int height);
void framebuffer_size_callback(GLFWwindow *window, int width, int height);

int main(int argc, char **argv)
{
    // Testing spdlog
    spdlog::set_pattern("%^[%T] %n: %v%$");
    spdlog::set_pattern("%^[%T] %n: %v%$");

    auto logger = spdlog::stdout_color_mt("SANDBOX");
    logger->set_level(spdlog::level::trace);
    logger->trace("spdlog trace");
    logger->info("spdlog info");
    logger->warn("spdlog warn");
    logger->error("spdlog error");
    logger->critical("spdlog critical");

    GLFWwindow *window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        //glClear(GL_COLOR_BUFFER_BIT);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}