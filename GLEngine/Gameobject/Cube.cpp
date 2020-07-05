//
// Created by erik on 19.10.2019.
//

#include "Cube.h"
Cube::Cube(glm::vec3 in, GameDataRef data)
{
    _data = data;
/*    g_vertex_buffer_data[0] = -in.x;
    g_vertex_buffer_data[1] = -in.y;
    g_vertex_buffer_data[2] = -in.z;
    g_vertex_buffer_data[3] = -in.x;
    g_vertex_buffer_data[4] = -in.y;
    g_vertex_buffer_data[5] = in.z;
    g_vertex_buffer_data[6] = -in.x;
    g_vertex_buffer_data[7] = in.y;
    g_vertex_buffer_data[8] = in.z;
    g_vertex_buffer_data[9] = in.x;
    g_vertex_buffer_data[10] = in.y;
    g_vertex_buffer_data[11] = -in.z;
    g_vertex_buffer_data[12] = -in.x;
    g_vertex_buffer_data[13] = -in.y;
    g_vertex_buffer_data[14] = -in.z;
    g_vertex_buffer_data[15] = -in.x;
    g_vertex_buffer_data[16] = in.y;
    g_vertex_buffer_data[17] = -in.z;
    g_vertex_buffer_data[18] = in.x;
    g_vertex_buffer_data[19] = -in.y;
    g_vertex_buffer_data[20] = in.z;
    g_vertex_buffer_data[21] = -in.x;
    g_vertex_buffer_data[22] = -in.y;
    g_vertex_buffer_data[23] = -in.z;
    g_vertex_buffer_data[24] = in.x;
    g_vertex_buffer_data[25] = -in.y;
    g_vertex_buffer_data[26] = -in.z;
    g_vertex_buffer_data[27] = in.x;
    g_vertex_buffer_data[28] = in.y;
    g_vertex_buffer_data[29] = -in.z;
    g_vertex_buffer_data[30] = in.x;
    g_vertex_buffer_data[31] = -in.y;
    g_vertex_buffer_data[32] = -in.z;
    g_vertex_buffer_data[33] = -in.x;
    g_vertex_buffer_data[34] = -in.y;
    g_vertex_buffer_data[35] = -in.z;
    g_vertex_buffer_data[36] = -in.x;
    g_vertex_buffer_data[37] = -in.y;
    g_vertex_buffer_data[38] = -in.z;
    g_vertex_buffer_data[39] = -in.x;
    g_vertex_buffer_data[40] = in.y;
    g_vertex_buffer_data[41] = in.z;
    g_vertex_buffer_data[42] = -in.x;
    g_vertex_buffer_data[43] = in.y;
    g_vertex_buffer_data[44] = -in.z;
    g_vertex_buffer_data[45] = in.x;
    g_vertex_buffer_data[46] = -in.y;
    g_vertex_buffer_data[47] = in.z;
    g_vertex_buffer_data[48] = -in.x;
    g_vertex_buffer_data[49] = -in.y;
    g_vertex_buffer_data[50] = in.z;
    g_vertex_buffer_data[51] = -in.x;
    g_vertex_buffer_data[52] = -in.y;
    g_vertex_buffer_data[53] = -in.z;
    g_vertex_buffer_data[54] = -in.x;
    g_vertex_buffer_data[55] = in.y;
    g_vertex_buffer_data[56] = in.z;
    g_vertex_buffer_data[57] = -in.x;
    g_vertex_buffer_data[58] = -in.y;
    g_vertex_buffer_data[59] = in.z;
    g_vertex_buffer_data[60] = in.x;
    g_vertex_buffer_data[61] = -in.y;
    g_vertex_buffer_data[62] = in.z;
    g_vertex_buffer_data[63] = in.x;
    g_vertex_buffer_data[64] = in.y;
    g_vertex_buffer_data[65] = in.z;
    g_vertex_buffer_data[66] = in.x;
    g_vertex_buffer_data[67] = -in.y;
    g_vertex_buffer_data[68] = -in.z;
    g_vertex_buffer_data[69] = in.x;
    g_vertex_buffer_data[70] = in.y;
    g_vertex_buffer_data[71] = -in.z;
    g_vertex_buffer_data[72] = in.x;
    g_vertex_buffer_data[73] = -in.y;
    g_vertex_buffer_data[74] = -in.z;
    g_vertex_buffer_data[75] = in.x;
    g_vertex_buffer_data[76] = in.y;
    g_vertex_buffer_data[77] = in.z;
    g_vertex_buffer_data[78] = in.x;
    g_vertex_buffer_data[79] = -in.y;
    g_vertex_buffer_data[80] = in.z;
    g_vertex_buffer_data[81] = in.x;
    g_vertex_buffer_data[82] = in.y;
    g_vertex_buffer_data[83] = in.z;
    g_vertex_buffer_data[84] = in.x;
    g_vertex_buffer_data[85] = in.y;
    g_vertex_buffer_data[86] = -in.z;
    g_vertex_buffer_data[87] = -in.x;
    g_vertex_buffer_data[88] = in.y;
    g_vertex_buffer_data[89] = -in.z;
    g_vertex_buffer_data[90] = in.x;
    g_vertex_buffer_data[91] = in.y;
    g_vertex_buffer_data[92] = in.z;
    g_vertex_buffer_data[93] = -in.x;
    g_vertex_buffer_data[94] = in.y;
    g_vertex_buffer_data[95] = -in.z;
    g_vertex_buffer_data[96] = -in.x;
    g_vertex_buffer_data[97] = in.y;
    g_vertex_buffer_data[98] = in.z;
    g_vertex_buffer_data[99] = in.x;
    g_vertex_buffer_data[100] = in.y;
    g_vertex_buffer_data[101] = in.z;
    g_vertex_buffer_data[102] = -in.x;
    g_vertex_buffer_data[103] = in.y;
    g_vertex_buffer_data[104] = in.z;
    g_vertex_buffer_data[105] = in.x;
    g_vertex_buffer_data[106] = -in.y;
    g_vertex_buffer_data[107] = in.z;

    g_color_buffer_data[0] = 0.583;
    g_color_buffer_data[1] = 0.771;
    g_color_buffer_data[2] = 0.014;
    g_color_buffer_data[3] = 0.609;
    g_color_buffer_data[4] = 0.115;
    g_color_buffer_data[5] = 0.436;
    g_color_buffer_data[6] = 0.327;
    g_color_buffer_data[7] = 0.483;
    g_color_buffer_data[8] = 0.844;
    g_color_buffer_data[9] = 0.822;
    g_color_buffer_data[10] = 0.569;
    g_color_buffer_data[11] = 0.201;
    g_color_buffer_data[12] = 0.435;
    g_color_buffer_data[13] = 0.602;
    g_color_buffer_data[14] = 0.223;
    g_color_buffer_data[15] = 0.31;
    g_color_buffer_data[16] = 0.747;
    g_color_buffer_data[17] = 0.185;
    g_color_buffer_data[18] = 0.597;
    g_color_buffer_data[19] = 0.77;
    g_color_buffer_data[20] = 0.761;
    g_color_buffer_data[21] = 0.559;
    g_color_buffer_data[22] = 0.436;
    g_color_buffer_data[23] = 0.73;
    g_color_buffer_data[24] = 0.359;
    g_color_buffer_data[25] = 0.583;
    g_color_buffer_data[26] = 0.152;
    g_color_buffer_data[27] = 0.483;
    g_color_buffer_data[28] = 0.596;
    g_color_buffer_data[29] = 0.789;
    g_color_buffer_data[30] = 0.559;
    g_color_buffer_data[31] = 0.861;
    g_color_buffer_data[32] = 0.639;
    g_color_buffer_data[33] = 0.195;
    g_color_buffer_data[34] = 0.548;
    g_color_buffer_data[35] = 0.859;
    g_color_buffer_data[36] = 0.014;
    g_color_buffer_data[37] = 0.184;
    g_color_buffer_data[38] = 0.576;
    g_color_buffer_data[39] = 0.771;
    g_color_buffer_data[40] = 0.328;
    g_color_buffer_data[41] = 0.97;
    g_color_buffer_data[42] = 0.406;
    g_color_buffer_data[43] = 0.615;
    g_color_buffer_data[44] = 0.116;
    g_color_buffer_data[45] = 0.676;
    g_color_buffer_data[46] = 0.977;
    g_color_buffer_data[47] = 0.133;
    g_color_buffer_data[48] = 0.971;
    g_color_buffer_data[49] = 0.572;
    g_color_buffer_data[50] = 0.833;
    g_color_buffer_data[51] = 0.14;
    g_color_buffer_data[52] = 0.616;
    g_color_buffer_data[53] = 0.489;
    g_color_buffer_data[54] = 0.997;
    g_color_buffer_data[55] = 0.513;
    g_color_buffer_data[56] = 0.064;
    g_color_buffer_data[57] = 0.945;
    g_color_buffer_data[58] = 0.719;
    g_color_buffer_data[59] = 0.592;
    g_color_buffer_data[60] = 0.543;
    g_color_buffer_data[61] = 0.021;
    g_color_buffer_data[62] = 0.978;
    g_color_buffer_data[63] = 0.279;
    g_color_buffer_data[64] = 0.317;
    g_color_buffer_data[65] = 0.505;
    g_color_buffer_data[66] = 0.167;
    g_color_buffer_data[67] = 0.62;
    g_color_buffer_data[68] = 0.077;
    g_color_buffer_data[69] = 0.347;
    g_color_buffer_data[70] = 0.857;
    g_color_buffer_data[71] = 0.137;
    g_color_buffer_data[72] = 0.055;
    g_color_buffer_data[73] = 0.953;
    g_color_buffer_data[74] = 0.042;
    g_color_buffer_data[75] = 0.714;
    g_color_buffer_data[76] = 0.505;
    g_color_buffer_data[77] = 0.345;
    g_color_buffer_data[78] = 0.783;
    g_color_buffer_data[79] = 0.29;
    g_color_buffer_data[80] = 0.734;
    g_color_buffer_data[81] = 0.722;
    g_color_buffer_data[82] = 0.645;
    g_color_buffer_data[83] = 0.174;
    g_color_buffer_data[84] = 0.302;
    g_color_buffer_data[85] = 0.455;
    g_color_buffer_data[86] = 0.848;
    g_color_buffer_data[87] = 0.225;
    g_color_buffer_data[88] = 0.587;
    g_color_buffer_data[89] = 0.04;
    g_color_buffer_data[90] = 0.517;
    g_color_buffer_data[91] = 0.713;
    g_color_buffer_data[92] = 0.338;
    g_color_buffer_data[93] = 0.053;
    g_color_buffer_data[94] = 0.959;
    g_color_buffer_data[95] = 0.12;
    g_color_buffer_data[96] = 0.393;
    g_color_buffer_data[97] = 0.621;
    g_color_buffer_data[98] = 0.362;
    g_color_buffer_data[99] = 0.673;
    g_color_buffer_data[100] = 0.211;
    g_color_buffer_data[101] = 0.457;
    g_color_buffer_data[102] = 0.82;
    g_color_buffer_data[103] = 0.883;
    g_color_buffer_data[104] = 0.371;
    g_color_buffer_data[105] = 0.982;
    g_color_buffer_data[106] = 0.099;
    g_color_buffer_data[107] = 0.879;

    g_uv_buffer_data[0] = 5.9e-05;
    g_uv_buffer_data[1] = 0.999996;
    g_uv_buffer_data[2] = 0.000103;
    g_uv_buffer_data[3] = 0.663952;
    g_uv_buffer_data[4] = 0.335973;
    g_uv_buffer_data[5] = 0.6640969999999999;
    g_uv_buffer_data[6] = 1.000023;
    g_uv_buffer_data[7] = 0.999987;
    g_uv_buffer_data[8] = 0.667979;
    g_uv_buffer_data[9] = 0.664149;
    g_uv_buffer_data[10] = 0.999958;
    g_uv_buffer_data[11] = 0.6639360000000001;
    g_uv_buffer_data[12] = 0.667979;
    g_uv_buffer_data[13] = 0.664149;
    g_uv_buffer_data[14] = 0.336024;
    g_uv_buffer_data[15] = 0.32812300000000005;
    g_uv_buffer_data[16] = 0.667969;
    g_uv_buffer_data[17] = 0.32811100000000004;
    g_uv_buffer_data[18] = 1.000023;
    g_uv_buffer_data[19] = 0.999987;
    g_uv_buffer_data[20] = 0.668104;
    g_uv_buffer_data[21] = 0.999987;
    g_uv_buffer_data[22] = 0.667979;
    g_uv_buffer_data[23] = 0.664149;
    g_uv_buffer_data[24] = 5.9e-05;
    g_uv_buffer_data[25] = 0.999996;
    g_uv_buffer_data[26] = 0.335973;
    g_uv_buffer_data[27] = 0.6640969999999999;
    g_uv_buffer_data[28] = 0.336098;
    g_uv_buffer_data[29] = 0.999929;
    g_uv_buffer_data[30] = 0.667979;
    g_uv_buffer_data[31] = 0.664149;
    g_uv_buffer_data[32] = 0.335973;
    g_uv_buffer_data[33] = 0.6640969999999999;
    g_uv_buffer_data[34] = 0.336024;
    g_uv_buffer_data[35] = 0.32812300000000005;
    g_uv_buffer_data[36] = 1.000004;
    g_uv_buffer_data[37] = 0.32815300000000003;
    g_uv_buffer_data[38] = 0.999958;
    g_uv_buffer_data[39] = 0.6639360000000001;
    g_uv_buffer_data[40] = 0.667979;
    g_uv_buffer_data[41] = 0.664149;
    g_uv_buffer_data[42] = 0.668104;
    g_uv_buffer_data[43] = 0.999987;
    g_uv_buffer_data[44] = 0.335973;
    g_uv_buffer_data[45] = 0.6640969999999999;
    g_uv_buffer_data[46] = 0.667979;
    g_uv_buffer_data[47] = 0.664149;
    g_uv_buffer_data[48] = 0.335973;
    g_uv_buffer_data[49] = 0.6640969999999999;
    g_uv_buffer_data[50] = 0.668104;
    g_uv_buffer_data[51] = 0.999987;
    g_uv_buffer_data[52] = 0.336098;
    g_uv_buffer_data[53] = 0.999929;
    g_uv_buffer_data[54] = 0.000103;
    g_uv_buffer_data[55] = 0.663952;
    g_uv_buffer_data[56] = 4e-06;
    g_uv_buffer_data[57] = 0.32813000000000003;
    g_uv_buffer_data[58] = 0.336024;
    g_uv_buffer_data[59] = 0.32812300000000005;
    g_uv_buffer_data[60] = 0.000103;
    g_uv_buffer_data[61] = 0.663952;
    g_uv_buffer_data[62] = 0.336024;
    g_uv_buffer_data[63] = 0.32812300000000005;
    g_uv_buffer_data[64] = 0.335973;
    g_uv_buffer_data[65] = 0.6640969999999999;
    g_uv_buffer_data[66] = 0.667969;
    g_uv_buffer_data[67] = 0.32811100000000004;
    g_uv_buffer_data[68] = 1.000004;
    g_uv_buffer_data[69] = 0.32815300000000003;
    g_uv_buffer_data[70] = 0.667979;
    g_uv_buffer_data[71] = 0.664149;*/

    //indexVBO(vertexbuffer,uvbuffer,indices,indexed_vertices,indexed_uvs);

    _data->textureLoader.loadDDS("noe","Data/uvtemplate.DDS");
    _data->textureLoader.loadBMPTexture("toe","Data/cobble3x3.bmp");
}

Cube::~Cube() {

}

void Cube::Draw(Camera &camera) {
    glGenBuffers(1, &vertexbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

    //glGenBuffers(1, &colorbuffer);
    //glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
    //glBufferData(GL_ARRAY_BUFFER, sizeof(g_color_buffer_data), g_color_buffer_data, GL_STATIC_DRAW);

    glGenBuffers(1,&uvbuffer);
    glBindBuffer(GL_ARRAY_BUFFER,uvbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_uv_buffer_data),g_uv_buffer_data,GL_STATIC_DRAW);

    glm::mat4 Projection = camera.getPerspectiveMatrix();
    glm::mat4 View       = camera.getViewMatrix();



    GLuint TextureID  = glGetUniformLocation(camera.getModelProgramId(), "myTextureSampler");
    GLuint Texture = _data->textureLoader.getTextureID("toe");

    // Bind our texture in Texture Unit 0
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, Texture);

    // Set our "myTextureSampler" sampler to use Texture Unit 0
    glUniform1i(TextureID, 0);

    // 1st attribute buffer : squareVertices
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glVertexAttribPointer(
            0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
            3,                  // size
            GL_FLOAT,           // type
            GL_FALSE,           // normalized?
            0,                  // stride
            (void*)0            // array buffer offset
    );


    // 2nd attribute buffer : UVs
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
    glVertexAttribPointer(
            1,                                // attribute. No particular reason for 1, but must match the layout in the shader.
            2,                                // size : U+V => 2
            GL_FLOAT,                         // type
            GL_FALSE,                         // normalized?
            0,                                // stride
            (void*)0                          // array buffer offset
    );
    // Draw the triangle !
    glDrawArrays(GL_TRIANGLES, 0, 12*3); // Starting from vertex 0; 3 squareVertices total -> 1 triangle

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDeleteBuffers(1,&vertexbuffer);
    glDeleteBuffers(1,&uvbuffer);
}