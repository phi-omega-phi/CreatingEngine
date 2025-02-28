/**
  * @file   opengl.h
  * @author 0And1Story
  * @date   2025-02-27
  * @brief  The basic OpenGL support for SDL.
  */

#ifndef _CS_OPENGL_H_
#define _CS_OPENGL_H_

#include "glad/glad.h"

#include <vector>
#include <functional>
#include <algorithm>
#include <numeric>

#ifndef SDL_surface_h_
struct SDL_Surface;
#endif
#ifndef SDL_rect_h_
struct SDL_Rect;
#endif

namespace OpenGL {

GLuint CompileShader(const char* source, GLenum type);
GLuint LoadShader(const char* shader_path, GLenum type);
GLuint LinkShader(GLuint vertexShader, GLuint fragmentShader);

using Rect = SDL_Rect;

class Texture {
public:
    GLuint id;

public:
    Texture() = default;
    explicit Texture(const char* file_path);
    Texture(void* pixels, int w, int h);
    explicit Texture(SDL_Surface* surface);

    void Release() noexcept;

    void TexParameteri(GLenum name, GLint value);
};

class Shader {
public:
    GLuint program;

public:
    Shader() = default;
    Shader(const char* vertex_source, const char* fragment_source);

    void Release() noexcept;

    void LoadFromSource(const char* vertex_source, const char* fragment_source);
    void LoadFromFile(const char* vertex_path, const char* fragment_path);

    void Use() const;

    void SetFloat(const char* name, GLfloat value);
    void SetInt(const char* name, GLint value);
    void SetSampler2D(const char* name, GLuint texture, GLint texture_unit);
    void SetSampler2D(const char* name, const Texture& texture, GLint texture_unit);
};

class VertexObject {
public:
    Shader shader;
    GLuint VAO, VBO, EBO;
    GLsizei indices_count;
    std::function<void(Shader&)> SetUniformVariable = [](Shader&){};

public:
    VertexObject() = default;
    template<size_t VERTICES_COUNT, size_t INDICES_COUNT>
    VertexObject(const Shader& shader, GLfloat (&vertices)[VERTICES_COUNT], GLuint (&indices)[INDICES_COUNT], const std::vector<GLsizei>& attr_size);
    template<size_t VERTICES_COUNT, size_t INDICES_COUNT>
    VertexObject(const Shader& shader, GLfloat (&vertices)[VERTICES_COUNT], GLuint (&indices)[INDICES_COUNT], const std::function<void()>& SetVertexAttr);

    void Release() noexcept;

    void Render();
};

}


/**
  * @file   opengl.impl.h
  * @author 0And1Story
  * @date   2025-02-28
  * @brief  The implementation of OpenGL Library related to templates.
  */
#ifndef _CS_OPENGL_IMPL_H_
#define _CS_OPENGL_IMPL_H_

namespace OpenGL {

// ---------- Class: VertexObject ---------- //

template<size_t VERTICES_COUNT, size_t INDICES_COUNT>
VertexObject::VertexObject(const Shader& shader, GLfloat (&vertices)[VERTICES_COUNT], GLuint (&indices)[INDICES_COUNT], const std::vector<GLsizei>& attr_size) : shader(shader), indices_count() {
    // Create Vertex Array Object, Vertex Buffer Object, Element Buffer Object
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    // Bind VAO, VBO, EBO
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Calculate the stride of the attributes of each vertex
    GLsizei stride = std::reduce(attr_size.begin(), attr_size.end());
    GLuint location = 0;
    GLsizei ptr = 0;

    // Set the attribute pointer for each location
    // The attributes are placed end to end by default, started at the index 0
    // To customize the placement of attributes, please use SetVertexAttr function
    for (auto&& size : attr_size) {
        glVertexAttribPointer(location, size, GL_FLOAT, GL_FALSE, stride * sizeof(GLfloat), (void*)(ptr * sizeof(GLfloat)));
        glEnableVertexAttribArray(location);
        ++location, ptr += size;
    }

    // Export
    indices_count = INDICES_COUNT;
}

template<size_t VERTICES_COUNT, size_t INDICES_COUNT>
VertexObject::VertexObject(const Shader& shader, GLfloat (&vertices)[VERTICES_COUNT], GLuint (&indices)[INDICES_COUNT], const std::function<void()>& SetVertexAttr) {
    // Create Vertex Array Object, Vertex Buffer Object, Element Buffer Object
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    // Bind VAO, VBO, EBO
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Do some works such as glVertexAttribPointer and glEnableVertexAttribArray
    SetVertexAttr();

    // Export
    indices_count = INDICES_COUNT;
}

}

#endif //_CS_OPENGL_IMPL_H_

#endif //_CS_OPENGL_H_
