/**
  * @file   opengl.cpp
  * @author 0And1Story
  * @date   2025-02-27
  * @brief  The basic OpenGL support for SDL.
  */

#include "opengl.h"

#include <iostream>
#include <fstream>
#include <sstream>

#include "SDL.h"
#include "SDL_image.h"

namespace OpenGL {

// ---------- Global Functions ---------- //

GLuint CompileShader(const char* source, GLenum type) {
    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &source, nullptr);
    glCompileShader(shader);

    // Error Handling
    int success;
    char infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shader, sizeof(infoLog), nullptr, infoLog);
        if (type == GL_VERTEX_SHADER) std::cerr << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
        else if (type == GL_FRAGMENT_SHADER) std::cerr << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
        else std::cerr << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    return shader;
}

GLuint LoadShader(const char* shader_path, GLenum type) {
    std::string code;
    std::ifstream file;

    // Read file
    try {
        file.open(shader_path);
        std::stringstream shaderStream;
        shaderStream << file.rdbuf();
        file.close();
        code = shaderStream.str();
    } catch (std::ifstream::failure& e) {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ" << std::endl;
    }

    const char* vertexShaderSource = code.c_str();
    return CompileShader(vertexShaderSource, type);
}

GLuint LinkShader(GLuint vertexShader, GLuint fragmentShader) {
    // Create shader program
    GLuint shaderProgram;
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    // Error Handling
    int success;
    char infoLog[512];
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, sizeof(infoLog), nullptr, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINK_FAILED\n" << infoLog << std::endl;
    }

    return shaderProgram;
}

// ---------- Class: Texture ---------- //

Texture::Texture(const char* file_path) {
    // Load image
    SDL_Surface* surface = IMG_Load(file_path);

    // Convert pixel format
    surface = SDL_ConvertSurfaceFormat(surface, SDL_PIXELFORMAT_RGBA8888, 0);

    // Create texture
    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, surface->w, surface->h, 0, GL_RGBA, GL_UNSIGNED_INT_8_8_8_8, surface->pixels);

    // Set texture wrap and texture filter (these are default settings)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Release surface
    SDL_FreeSurface(surface);

    // Export
    this->id = texture;
}

Texture::Texture(void* pixels, int w, int h) {
    // Create texture
    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    // Pay attention! This constructor only accept pixels with RGBA8888 format!
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_INT_8_8_8_8, pixels);

    // Set texture wrap and texture filter (these are default settings)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Export
    this->id = texture;
}

Texture::Texture(SDL_Surface* surface) {
    // Convert pixel format
    surface = SDL_ConvertSurfaceFormat(surface, SDL_PIXELFORMAT_RGBA8888, 0);

    // Create texture
    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, surface->w, surface->h, 0, GL_RGBA, GL_UNSIGNED_INT_8_8_8_8, surface->pixels);

    // Set texture wrap and texture filter (these are default settings)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Export
    this->id = texture;
}

void Texture::Release() noexcept {
    glDeleteTextures(1, &id);
}

void Texture::TexParameteri(GLenum name, GLint value) {
    glBindTexture(GL_TEXTURE_2D, id);
    glTexParameteri(GL_TEXTURE_2D, name, value);
}

// ---------- Class: Shader ---------- //

Shader::Shader(const char* vertex_source, const char* fragment_source) {
    LoadFromSource(vertex_source, fragment_source);
}

void Shader::Release() noexcept {
    glDeleteProgram(program);
    program = 0;
}

void Shader::LoadFromSource(const char* vertex_source, const char* fragment_source) {
    GLuint vertexShader, fragmentShader;
    vertexShader = CompileShader(vertex_source, GL_VERTEX_SHADER);
    fragmentShader = CompileShader(fragment_source, GL_FRAGMENT_SHADER);

    // Create shader program
    GLuint shaderProgram = LinkShader(vertexShader, fragmentShader);

    // Clear shaders
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // Export
    program = shaderProgram;
}

void Shader::LoadFromFile(const char* vertex_path, const char* fragment_path) {
    GLuint vertexShader, fragmentShader;
    vertexShader = LoadShader(vertex_path, GL_VERTEX_SHADER);
    fragmentShader = LoadShader(fragment_path, GL_FRAGMENT_SHADER);

    // Create shader program
    GLuint shaderProgram = LinkShader(vertexShader, fragmentShader);

    // Clear shaders
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // Export
    program = shaderProgram;
}

void Shader::Use() const {
    glUseProgram(program);
}

void Shader::SetFloat(const char* name, GLfloat value) {
    glUniform1f(glGetUniformLocation(program, name), value);
}

void Shader::SetInt(const char* name, GLint value) {
    glUniform1i(glGetUniformLocation(program, name), value);
}

void Shader::SetSampler2D(const char* name, GLuint texture, GLint texture_unit) {
    glActiveTexture(GL_TEXTURE0 + texture_unit);
    glBindTexture(GL_TEXTURE_2D, texture);
    glUniform1i(glGetUniformLocation(program, name), texture_unit);
}

void Shader::SetSampler2D(const char* name, const Texture& texture, GLint texture_unit) {
    SetSampler2D(name, texture.id, texture_unit);
}

// ---------- Class: VertexObject ---------- //

void VertexObject::Release() noexcept {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}

void VertexObject::Render() {
    // Use shader program
    shader.Use();

    // Set the uniform variables
    SetUniformVariable(shader);

    // Draw elements
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indices_count, GL_UNSIGNED_INT, nullptr);
}

}