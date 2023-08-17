#define _CRT_SECURE_NO_WARNINGS
#define STB_IMAGE_IMPLEMENTATION
#include <glad/glad.h> // must come before other headers because includes a bunch of stuff already(?)
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>
#include "stb_image.h"

#include <fstream>
#include <iostream>

#include "Engine.h"

using namespace std;

void framebufferSizeCallback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}

int main()
{
    const int winWidth = 1920;
    const int winHeight = 1080;

    // Engine* engine = new Engine(winWidth, winHeight);

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4); // glfwWindowHint(<valueToConfigure>, <valueOfThatOption>)
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(winWidth, winHeight, "Colosseum", NULL, NULL);
    if (window == NULL) {
        std::cout << "Failed to create GLFW window\n";
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) { // makes sure we're calling to correct addresses because OS specificity
        std::cout << "Failed to init GLAD\n";
        return -1;
    }

    glViewport(0, 0, winWidth, winHeight);

    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

    // Credit to - https://smallmak.itch.io/animated-sword-cursor 
    // Cursor is 24 x 31
    int cursorWidth, cursorHeight, nrChannels;
    unsigned char* pixels = stbi_load("Assets\\sCursor.png", &cursorWidth, &cursorHeight, &nrChannels, 0);

    GLFWimage cursorTexture;
    cursorTexture.width = 24;
    cursorTexture.height = 31;
    cursorTexture.pixels = pixels;
    
    GLFWcursor* cursor = glfwCreateCursor(&cursorTexture, 0, 0);
    if (cursor != NULL) {
		glfwSetCursor(window, cursor);
    }

    Engine engine;
    Engine::RollData result = engine.skillCheck(3, 0, 10);

    switch (result.result) {
    case Engine::R_CritFail:
        cout << "Critical failure\n";
        break;
    case Engine::R_CritSuccess:
        cout << "Critical success\n";
        break;
    case Engine::R_Fail:
        cout << "Standard failure\n";
        break;
    case Engine::R_Success:
        cout << "Standard success\n";
        break;
    default:
        cout << "unexpected issue\n";
        break;
    }

    while (!glfwWindowShouldClose(window)) {
        // handle inputs
        processInput(window); 

        // rendering commands go here
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

        // check and call events
        glfwPollEvents();

        // swap buffers
        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0;
}
