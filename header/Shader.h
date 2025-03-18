#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <stdbool.h>

typedef struct Shader {
    unsigned int id;
} Shader;

// Create and compile a shader program
bool shader_create(Shader* shader, const char* vertexSource, const char* fragmentSource);

// Use the shader program
void shader_use(Shader* shader);

// Set uniform values
void shader_set_uniform_float(Shader* shader, const char* name, float value);
void shader_set_uniform_vec2(Shader* shader, const char* name, float x, float y);
void shader_set_uniform_vec3(Shader* shader, const char* name, float x, float y, float z);

// Delete shader program
void shader_delete(Shader* shader);

#endif // SHADER_H