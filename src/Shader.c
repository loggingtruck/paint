#include "Shader.h"
#include <stdio.h>
#include <stdbool.h>

static unsigned int compile_shader(const char* source, GLenum type) {
    unsigned int shader = glCreateShader(type);
    glShaderSource(shader, 1, &source, NULL);
    glCompileShader(shader);

    // Check for errors
    int success;
    char infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        fprintf(stderr, "Shader compilation failed: %s\n", infoLog);
        return 0;
    }

    return shader;
}

// Create and compile a shader program
bool shader_create(Shader* shader, const char* vertexSource, const char* fragmentSource) {
    unsigned int vertexShader = compile_shader(vertexSource, GL_VERTEX_SHADER);
    if (!vertexShader) return false;
    
    unsigned int fragmentShader = compile_shader(fragmentSource, GL_FRAGMENT_SHADER);
    if (!fragmentShader) {
        glDeleteShader(vertexShader);
        return false;
    }

    shader->id = glCreateProgram();
    glAttachShader(shader->id, vertexShader);
    glAttachShader(shader->id, fragmentShader);
    glLinkProgram(shader->id);

    // Check for linking errors
    int success;
    char infoLog[512];
    glGetProgramiv(shader->id, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shader->id, 512, NULL, infoLog);
        fprintf(stderr, "Shader program linking failed: %s\n", infoLog);
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
        return false;
    }

    // Shaders are now linked to the program and no longer needed
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    
    return true;
}

// Use the shader program
void shader_use(Shader* shader) {
    glUseProgram(shader->id);
}

// Set uniform values
void shader_set_uniform_float(Shader* shader, const char* name, float value) {
    glUniform1f(glGetUniformLocation(shader->id, name), value);
}

void shader_set_uniform_vec2(Shader* shader, const char* name, float x, float y) {
    glUniform2f(glGetUniformLocation(shader->id, name), x, y);
}

void shader_set_uniform_vec3(Shader* shader, const char* name, float x, float y, float z) {
    glUniform3f(glGetUniformLocation(shader->id, name), x, y, z);
}

// Delete shader program
void shader_delete(Shader* shader) {
    glDeleteProgram(shader->id);
}