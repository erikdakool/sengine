//
// Created by erik on 20.10.2019.
//

#include <cstring>
#include <array>
#include <fstream>
#include "TextureLoader.h"

TextureLoader::TextureLoader() {

}

TextureLoader::~TextureLoader() {

}

GLuint TextureLoader::loadBMPTexture(const std::string& name, const std::string& url){
    for (int i = 0; i < Textures.size(); ++i) {
        if(Textures.at(i).name == name){
            return 0;
        }
    }

    std::cout << "Reading image " << name << " at " << url << std::endl;
    char imagepath[url.length()+1];
    strncpy(imagepath,url.c_str(), sizeof(imagepath));


    static constexpr size_t HEADER_SIZE = 54;

    std::ifstream bmp(url, std::ios::binary);

    std::array<char, HEADER_SIZE> header;
    bmp.read(header.data(), header.size());

    auto fileSize = *reinterpret_cast<uint32_t *>(&header[2]);
    auto dataOffset = *reinterpret_cast<uint32_t *>(&header[10]);
    auto width = *reinterpret_cast<uint32_t *>(&header[18]);
    auto height = *reinterpret_cast<uint32_t *>(&header[22]);
    auto depth = *reinterpret_cast<uint16_t *>(&header[28]);

    std::cout << "fileSize: " << fileSize << std::endl;
    std::cout << "dataOffset: " << dataOffset << std::endl;
    std::cout << "width: " << width << std::endl;
    std::cout << "height: " << height << std::endl;
    std::cout << "depth: " << depth << "-bit" << std::endl;

    std::vector<char> img(dataOffset - HEADER_SIZE);
    bmp.read(img.data(), img.size());

    auto dataSize = ((width * 3 + 3) & (~3)) * height;
    img.resize(dataSize);
    bmp.read(img.data(), img.size());


    int tileX = 1;
    int tileY = 0;

    int tileW = 32;
    int tileH = 32;
    int tileSize = tileW*tileH*3;
    unsigned char* tileData = new unsigned char [tileSize];

    tileY = height/tileH-tileY-1;
    std::cout << tileY << std::endl;

    for (int j = 0; j < tileH; ++j) {
        for (int i = 0; i < tileW; ++i) {
            tileData[3*(i*tileW+j)]   = img[3*(i*width+j+(tileY*tileH*width)+(tileX*tileW))];
            tileData[3*(i*tileW+j)+1] = img[3*(i*width+j+(tileY*tileH*width)+(tileX*tileW))+1];
            tileData[3*(i*tileW+j)+2] = img[3*(i*width+j+(tileY*tileH*width)+(tileX*tileW))+2];
        }
    }

    //for(int i = 0; i < tileSize; i += 3)
    //{
    //    // flip the order of every 3 bytes
    //    unsigned char tmp = img[i];
    //    img[i] = img[i+2];
    //    img[i+2] = tmp;
    //}
//
    //for (int i = 0; i < width; ++i) {
    //    for (int j = 0; j < height; ++j) {
    //        std::cout << "Px: " << i << " " << j << std::endl;
    //        std::cout << "R: " << int(img[3*(i*width+j)] & 0xff) << " G: " << int(img[3*(i*height+j)+1] & 0xff) << " B: " << int(img[3*(i*height+j)+2] & 0xff) << std::endl;
    //    }
    //}

    // Create one OpenGL texture
    GLuint textureID;
    glGenTextures(1, &textureID);

    // "Bind" the newly created texture : all future texture functions will modify this texture
    glBindTexture(GL_TEXTURE_2D, textureID);

    // Give the image to OpenGL
    //glTexImage2D(GL_TEXTURE_2D, 0,GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, data);
    glTexImage2D(GL_TEXTURE_2D, 0,GL_RGB, tileW, tileH, 0, GL_BGR, GL_UNSIGNED_BYTE, tileData);
    delete [] tileData;

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    // When MAGnifying the image (no bigger mipmap available), use LINEAR filtering
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // When MINifying the image, use a LINEAR blend of two mipmaps, each filtered LINEARLY too
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    // Generate mipmaps, by the way.
    glGenerateMipmap(GL_TEXTURE_2D);

    Texture texture(name,textureID);
    Textures.push_back(texture);
    return textureID;
}

#define FOURCC_DXT1 0x31545844 // Equivalent to "DXT1" in ASCII
#define FOURCC_DXT3 0x33545844 // Equivalent to "DXT3" in ASCII
#define FOURCC_DXT5 0x35545844 // Equivalent to "DXT5" in ASCII

GLuint TextureLoader::loadDDS(std::string name, std::string url) {
    for (int i = 0; i < Textures.size(); ++i) {
        if(Textures.at(i).name == name){
            return 0;
        }
    }
    std::cout << "Reading image " << name << " at " << url << std::endl;

    char imagepath[url.length()+1];
    strncpy(imagepath,url.c_str(), sizeof(imagepath));

    unsigned char header[124];
    FILE*fp;
    fp = fopen(imagepath,"rb");
    if(fp==NULL){
        printf("File empty\n");
        return 0;
    }

    /* verify the type of file */
    char filecode[4];
    fread(filecode, 1, 4, fp);
    if (strncmp(filecode, "DDS ", 4) != 0) {
        fclose(fp);
        return 0;
    }

    /* get the surface desc */
    fread(&header, 124, 1, fp);

    unsigned int height      = *(unsigned int*)&(header[8 ]);
    unsigned int width         = *(unsigned int*)&(header[12]);
    unsigned int linearSize     = *(unsigned int*)&(header[16]);
    unsigned int mipMapCount = *(unsigned int*)&(header[24]);
    unsigned int fourCC      = *(unsigned int*)&(header[80]);

    unsigned char * buffer;
    unsigned int bufsize;
    /* how big is it going to be including all mipmaps? */
    bufsize = mipMapCount > 1 ? linearSize * 2 : linearSize;
    buffer = (unsigned char*)malloc(bufsize * sizeof(unsigned char));
    fread(buffer, 1, bufsize, fp);
    /* close the file pointer */
    fclose(fp);

    unsigned int components  = (fourCC == FOURCC_DXT1) ? 3 : 4;
    unsigned int format;
    switch(fourCC)
    {
        case FOURCC_DXT1:
            format = GL_COMPRESSED_RGBA_S3TC_DXT1_EXT;
            break;
        case FOURCC_DXT3:
            format = GL_COMPRESSED_RGBA_S3TC_DXT3_EXT;
            break;
        case FOURCC_DXT5:
            format = GL_COMPRESSED_RGBA_S3TC_DXT5_EXT;
            break;
        default:
            free(buffer);
            return 0;
    }

    // Create one OpenGL texture
    GLuint textureID;
    glGenTextures(1, &textureID);

    // "Bind" the newly created texture : all future texture functions will modify this texture
    glBindTexture(GL_TEXTURE_2D, textureID);
    glPixelStorei(GL_UNPACK_ALIGNMENT,1);

    unsigned int blockSize = (format == GL_COMPRESSED_RGBA_S3TC_DXT1_EXT) ? 8 : 16;
    unsigned int offset = 0;

    /* load the mipmaps */
    for (unsigned int level = 0; level < mipMapCount && (width || height); ++level)
    {
        unsigned int size = ((width+3)/4)*((height+3)/4)*blockSize;
        glCompressedTexImage2D(GL_TEXTURE_2D, level, format, width, height,
                               0, size, buffer + offset);

        offset += size;
        width  /= 2;
        height /= 2;

        // Deal with Non-Power-Of-Two textures. This code is not included in the webpage to reduce clutter.
        if(width < 1) width = 1;
        if(height < 1) height = 1;
    }
    free(buffer);

    Texture texture(name,textureID);
    Textures.push_back(texture);
    return textureID;
}

GLuint TextureLoader::getTextureID(const std::string& name) {
    for (int i = 0; i < Textures.size(); ++i) {
        if(Textures.at(i).name == name){
            return Textures.at(i).TextureId;
        }
    }
    return 0;
}