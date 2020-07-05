//
// Created by erikdesk on 6/28/20.
//

#include <string>
static std::string getBlockShader(int textureCount){
    std::string ret;

    ret = "#version 450 core\n"
          "out vec3 color;\n"
          "in vec3 fragmentColor;\n"
          "in vec2 v_TexCoord;\n"
          "in float v_TexIndex;\n"
          "uniform sampler2D u_Textures["+std::to_string(textureCount)+"];\n"
          "void main()\n"
          "{\n"
          "int index = int(v_TexIndex);\n"
          "switch(index){\n";

    for (int i = 0; i < textureCount; ++i) {
        ret.append("case " + std::to_string(i) +":\n"
                        "color = texture(u_Textures[" + std::to_string(i) + "],v_TexCoord).rgb;\n"
                   "break;\n");
    }

    ret.append("}\n}");

    return ret;
}
