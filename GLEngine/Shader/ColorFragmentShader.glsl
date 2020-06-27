#version 450 core

out vec3 color;

in vec3 fragmentColor;
in vec2 v_TexCoord;
in float v_TexIndex;

uniform sampler2D u_Textures[4];

void main()
{
    int index = int(v_TexIndex);

    switch(index){
        case 0:
        color = texture(u_Textures[0],v_TexCoord).rgb;
        break;
        case 1:
        color = texture(u_Textures[1],v_TexCoord).rgb;
        break;
        case 2:
        color = texture(u_Textures[2],v_TexCoord).rgb;
        break;
        case 3:
        color = texture(u_Textures[3],v_TexCoord).rgb;
    }

    //color = texture(u_Textures[index],v_TexCoord).rgb;

    //color = vec3(v_TexIndex,v_TexIndex,v_TexIndex);
    //color = vec3(index,index,index);
}