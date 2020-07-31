#version 450

out vec3 color;

//in vec3 fragmentColor;
in vec2 v_TexCoord;
in float v_TexIndex;


layout (binding=0) uniform sampler2DArray u_Textures;
uniform vec3 lightColor;

void main()
{
    uint index = uint(v_TexIndex);

    //color = vec3(v_TexIndex/10,v_TexIndex/10,v_TexIndex/10);
    //color = vec3(v_TexCoord,0);
    color = lightColor*texture(u_Textures,vec3(v_TexCoord,index)).rgb;
    //color = vec3(1,0,1);
}