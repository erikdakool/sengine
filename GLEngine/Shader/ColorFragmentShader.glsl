#version 450 core

in vec4 fragmentColor;
in vec2 v_TexCoord;
in float v_TexIndex;

out vec4 color;

uniform sampler2D u_Textures[2];

void main()
{
    int index = int(v_TexIndex);
    color = texture(u_Textures[index],v_TexCoord);
    //color = vec4(v_TexCoord,0,1);
}