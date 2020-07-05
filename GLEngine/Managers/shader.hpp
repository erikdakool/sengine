//
// Created by erik on 18.10.2019.
//

#ifndef GLENGINE_SHADER_HPP
#define GLENGINE_SHADER_HPP

#include <GL/glew.h>

GLuint LoadShaders(const char * vertex_file_path, const char * fragment_file_path);
GLuint LoadBlockShader(int textures);

#endif //GLENGINE_SHADER_HPP
