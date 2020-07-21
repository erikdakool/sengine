#version 450

out vec3 color;

in vec3 fragmentColor;
in vec2 v_TexCoord;
in float v_TexIndex;

uniform sampler2D u_Textures[8];
void main()
{
    //color = vec3(v_TexCoord,0);
    //color = mix(texture(texture0, v_TexCoord), texture(texture1, v_TexCoord), 0.2);
    int index = int(v_TexIndex);
    //color = texture(u_Textures[index],v_TexCoord).rgb;

    switch(index){
        case 0:
        color = texture(u_Textures[0], v_TexCoord).rgb;
        break;
        case 1:
        color = texture(u_Textures[1], v_TexCoord).rgb;
        break;
        case 2:
        color = texture(u_Textures[2], v_TexCoord).rgb;
        break;
        case 3:
        color = texture(u_Textures[3], v_TexCoord).rgb;
        break;
        case 4:
        color = texture(u_Textures[4], v_TexCoord).rgb;
        break;
        case 5:
        color = texture(u_Textures[5], v_TexCoord).rgb;
        break;
        case 6:
        color = texture(u_Textures[6], v_TexCoord).rgb;
        break;
        case 7:
        color = texture(u_Textures[7], v_TexCoord).rgb;
        break;
    }
    
    //color = vec3(v_TexIndex/10,v_TexIndex/10,v_TexIndex/10);
    //color = vec3(v_TexCoord,0);
}