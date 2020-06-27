//
// Created by erikdesk on 6/27/20.
//

#ifndef GLENGINE_BLOCKINFO_H
#define GLENGINE_BLOCKINFO_H

#include <string>

struct BlockInfo{
    int id = 0;
    std::string name = "";
    int left = 0;
    int right = 0;
    int top = 0;
    int bottom = 0;
    int back = 0;
    int front = 0;
};

#endif //GLENGINE_BLOCKINFO_H
