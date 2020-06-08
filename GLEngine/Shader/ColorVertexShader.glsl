#version 450 core
layout (location = 0) in vec3 aPos; // the position variable has attribute position 0
layout (location = 1) in vec3 vertexColor;
layout (location = 2) in vec2 texCoord;
layout (location = 3) in float a_TexIndex;

out vec3 fragmentColor;
out vec2 v_TexCoord;
out float v_TexIndex;

uniform mat4 MVP;

void main()
{
    gl_Position = MVP *vec4(aPos, 1.0); // see how we directly give a vec3 to vec4's constructor
    fragmentColor = vertexColor;
    v_TexIndex = a_TexIndex;
    v_TexCoord = texCoord;
}