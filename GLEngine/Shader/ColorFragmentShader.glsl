#version 450 core

out vec3 color;

in vec3 fragmentColor;
in vec2 v_TexCoord;
in float v_TexIndex;

uniform sampler2D u_Textures[3];

void main()
{
    int index = int(v_TexIndex);
    color = texture(u_Textures[index],v_TexCoord).rgb;
    //color = vec3(v_TexIndex,v_TexIndex,v_TexIndex);
    //color = vec3(index,index,index);
}