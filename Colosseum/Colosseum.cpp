#define _CRT_SECURE_NO_WARNINGS
#define STB_IMAGE_IMPLEMENTATION
#include <glad/glad.h> // must come before other headers because includes a bunch of stuff already(?)
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>
#include "stb_image.h"
#include "shader.h"

#include "glm.hpp"
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include <vec2.hpp>
#include <vec3.hpp>

#include <ft2build.h>
#include FT_FREETYPE_H

#include <fstream>
#include <iostream>
#include <map>

#include "Engine.h"

using namespace std;

struct Letter {
    unsigned int TextureID;
    glm::ivec2 Size;
    glm::ivec2 Bearing;
    unsigned int Advance;
};
map<GLchar, Letter> Letters;

unsigned int VAO, VBO;

void printString(Shader& s, string text, float x, float y, float scale, glm::vec3 color);

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

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    FT_Library ft;
    if (FT_Init_FreeType(&ft)) {
        cout << "ERROR:FREETYPE: Could not init Freetype library\n";
    }

    FT_Face face;
    if (FT_New_Face(ft, "Assets\\fonts\\arial.ttf", 0, &face)) {
        cout << "ERROR:FREETYPE: Failed to load font\n";
    }

    FT_Set_Pixel_Sizes(face, 0, 32);
    if (FT_Load_Char(face, 'X', FT_LOAD_RENDER)) {
        cout << "ERRORL:FREETYPE: Failed to load glyph\n";
    }

    for (unsigned char c = 0; c < 128; c++) {
        if (FT_Load_Char(face, c, FT_LOAD_RENDER)) {
            cout << "ERROR:FREETYPE: Failed to load Glyph\n";
            continue;
        }

        unsigned int texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(
            GL_TEXTURE_2D,
            0,
            GL_RED,
            face->glyph->bitmap.width,
            face->glyph->bitmap.rows,
            0,
            GL_RED,
            GL_UNSIGNED_BYTE,
            face->glyph->bitmap.buffer
        );
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		Letter letter = {
			texture,
			glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
			glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
			face->glyph->advance.x
		};
		Letters.insert(std::pair<char, Letter>(c, letter));
    };

    FT_Done_Face(face);
    FT_Done_FreeType(ft);

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    Shader shader("./text.vs", "./text.fs");
    glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(winWidth), 0.0f, static_cast<float>(winHeight));
    shader.use();
    glUniformMatrix4fv(glGetUniformLocation(shader.ID, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

    while (!glfwWindowShouldClose(window)) {
        // handle inputs
        processInput(window); 

        // rendering commands go here
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

        string introMessage = "Hello, World!";
        printString(shader, introMessage, (winWidth / 2), (winHeight / 2), 1.0f, glm::vec3(0.9f, 0.9f, 0.9f));

        // check and call events
        glfwPollEvents();

        // swap buffers
        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0;
}

void printString(Shader& s, string text, float x, float y, float scale, glm::vec3 color) {
    s.use();
    glUniform3f(glGetUniformLocation(s.ID, "textColour"), color.x, color.y, color.z);
    glActiveTexture(GL_TEXTURE);
    glBindVertexArray(VAO);

    string::const_iterator c;
    for (c = text.begin(); c != text.end(); c++) {
        Letter l = Letters[*c];

        float xpos = x + l.Bearing.x * scale;
        float ypos = y - (l.Size.y - l.Bearing.y) * scale;

        float w = l.Size.x * scale;
        float h = l.Size.y * scale;

        // update VBO for each character
        float vertices[6][4] = {
            {xpos,        ypos + h,    0.0f, 0.0f},
            {xpos,        ypos,        0.0f, 1.0f},
            {xpos + w,    ypos,        1.0f, 1.0f},

            {xpos,        ypos + h,    0.0f, 0.0f},
            {xpos + w,    ypos,        1.0f, 1.0f},
            {xpos + w,    ypos + h,    1.0f, 0.0f}
        };

        glBindTexture(GL_TEXTURE_2D, l.TextureID);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glDrawArrays(GL_TRIANGLES, 0, 6);

        x += (l.Advance >> 6) * scale;
    }
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}
